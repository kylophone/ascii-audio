# ascii-audio
Generates PCM audio from an ASCII string. Text re-emerges when viewing spectrogram image. 
<img src = "spectrogram.png">
##USAGE
`asciiaudio <input_string> <base_freq> <output_file>`

This will generate a 48k/32-bit floating point raw PCM file. You can listen to it with SoX like this:

`play -c 1 -r 48000 -b 32 -e float -t raw out.raw`

Generating a spectrogram with SoX looks like this:

`sox -c 1 -r 48000 -b 32 -e float -t raw out.raw -n spectrogram`
