asciiaudio: src/asciiaudio.c src/ti83font.c
	gcc -o ascii-audio src/asciiaudio.c src/ti83font.c -I ./include -Wall -lm
