# WAV Volume Scaler

## About
A command-line audio processing program written in C that adjusts the volume of WAV audio files by multiplying each audio sample by a user-specified factor. It preserves the original file's header and saves the modified audio as a new WAV file.

## How It Works
- Accepts three command-line arguments: an input WAV file, an output WAV file, and a volume factor.
- Reads and copies the 44-byte WAV header from the input file to the output file.
- Reads the audio data as signed 16-bit integer samples.
- Multiplies each sample by the specified factor to increase or decrease the volume.
- Writes the modified samples into the output file.

## Usage
Compile the program:

```bash
make volume
```

Run it with an input file, an output file, and a volume factor:

```bash
./volume input.wav output.wav 2.0
```

A factor of `2.0` doubles the sample values, while a factor of `0.5` halves them.

## What I Practiced
- File handling in C using `fopen`, `fread`, `fwrite`, and `fclose`
- Command-line arguments with `argc` and `argv`
- Working with binary files and WAV headers
- Using fixed-width integer types such as `uint8_t` and `int16_t`
- Processing data with loops and applying arithmetic operations

## Technologies
- C
- Standard C libraries
- WAV audio file format

## Course
Developed as part of Harvard University's CS50 course.
