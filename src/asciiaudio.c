#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "ti83font.h"

void displayMem_to_PCM(FILE *sound_out, char *display_mem, int base_freq, int bandwidth, int sample_rate) {
	float y_slice = (float) bandwidth / 6;
	int freq[7] = {base_freq, base_freq + y_slice, base_freq + (2 * y_slice), base_freq + (3 * y_slice), base_freq + (4 * y_slice), base_freq + (5 * y_slice), base_freq + bandwidth};
	
	for (int i = 0; i <= 4; i++) {
		int column_length = (sample_rate / 5) / 5;
		for (int j = 0; j < column_length; j++) {
			float envelope_multiplier = sin(M_PI * ((float) j / (float) column_length));

			float sample = 0;
			for (int k = 0; k < 7; k++) {
				if (display_mem[i] & (1 << k)) sample += (sin(2 * M_PI * freq[k] *  j / sample_rate) * envelope_multiplier) / 7;
				fwrite(&sample, sizeof(float), 1, sound_out);
			}
		}
		for (int k = 0; k < column_length; k++) {
			float zero = 0;
			fwrite(&zero, sizeof(float), 1, sound_out);
		}	
	}
}

void error() {
	fprintf(stderr, "Example usage: $ ascii-audio -i input\\ string -f 440 -b 1000 -o audio_out.raw\n");
	fprintf(stderr, "-i [input string]   (required)\n");
	fprintf(stderr, "-f [base frequency] (default: 1000)\n");
	fprintf(stderr, "-b [bandwidth]      (default: 1200)\n");
	fprintf(stderr, "-o [output file]    (default: out.raw)\n");
	exit(-1);	
}

int main (int argc, char* argv[]) {

	char *input_string;
	char *outputFile = strdup("out.raw");
	int base_freq = 1200;
	int bandwidth = 1000;
	int input_flag = 0;
	int opt;

	while ((opt = getopt(argc, argv, "i:f:b:o:")) != -1) {
		switch(opt) {
			case 'i':
				input_string = strdup(optarg);
				input_flag = 1;
				break;
			case 'f':
				base_freq = atoi(optarg);
				break;
			case 'b':
				bandwidth = atoi(optarg);
				break;
			case 'o':
				outputFile = strdup(optarg);
				break;
			default:
				error();
		}
	}

	if (input_flag == 0) error();

	FILE *file = fopen(outputFile, "wb");

	for (int i = 0; i < strlen(input_string); i++) {
		char display_mem[5];
		ti83font(input_string[i], display_mem);
		displayMem_to_PCM(file, &display_mem[0], base_freq, bandwidth, 48000);
	}

	fclose(file);
}
