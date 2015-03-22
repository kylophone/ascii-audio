#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "ti83font.h"

void displayMem_to_PCM(FILE *sound_out, char *display_mem, int base_freq, int sample_rate) {
	int freq[7] = {base_freq, base_freq + 200, base_freq + 400, base_freq + 600, base_freq + 800, base_freq + 1000, base_freq + 1200};
	
	for (int i = 0; i <= 4; i++) {
		int letter_length = (sample_rate / 5) / 4;
		for (int j = 0; j < letter_length; j++) {
			
			float envelope_multiplier = sin(M_PI * ((float) j / (float) letter_length));

			float sample = 0;
			if (display_mem[i] & (1 << 0)) sample += (sin(2 * M_PI * freq[0] * (float) j / (float) sample_rate) * envelope_multiplier) / 7;
			if (display_mem[i] & (1 << 1)) sample += (sin(2 * M_PI * freq[1] * (float) j / (float) sample_rate) * envelope_multiplier) / 7;
			if (display_mem[i] & (1 << 2)) sample += (sin(2 * M_PI * freq[2] * (float) j / (float) sample_rate) * envelope_multiplier) / 7;
			if (display_mem[i] & (1 << 3)) sample += (sin(2 * M_PI * freq[3] * (float) j / (float) sample_rate) * envelope_multiplier) / 7;
			if (display_mem[i] & (1 << 4)) sample += (sin(2 * M_PI * freq[4] * (float) j / (float) sample_rate) * envelope_multiplier) / 7;
			if (display_mem[i] & (1 << 5)) sample += (sin(2 * M_PI * freq[5] * (float) j / (float) sample_rate) * envelope_multiplier) / 7;
			if (display_mem[i] & (1 << 6)) sample += (sin(2 * M_PI * freq[6] * (float) j / (float) sample_rate) * envelope_multiplier) / 7;
			fwrite(&sample, sizeof(float), 1, sound_out);
		}
		for (int k = 0; k < ((sample_rate / 5) / 2); k++) {
			float zero = 0;
			fwrite(&zero, sizeof(float), 1, sound_out);
		}	
	}
}


int main (int argc, char* argv[]) {
	const char *input_string = argv[1];
	const int base_freq = atoi(argv[2]);
	const char *outputFile = argv[3];
	FILE *file = fopen(outputFile, "wb");


	for (int i = 0; i < strlen(input_string); i++) {
		char display_mem[5];
		ti83font(input_string[i], display_mem);
		displayMem_to_PCM(file, &display_mem[0], base_freq, 48000);
	}

	fclose(file);
	return 0;
}