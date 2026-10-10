// volume.c - corrected version
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>    // for roundf
#include <limits.h>  // for INT16_MIN / INT16_MAX

#define HEADER_SIZE 44

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Parse factor
    float factor = atof(argv[3]);

    // Open input file (binary) for reading
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Open output file (binary) for writing
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        fclose(input);
        return 1;
    }

    // Read header
    uint8_t header[HEADER_SIZE];
    size_t header_read = fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    if (header_read != HEADER_SIZE)
    {
        // header couldn't be read completely
        printf("Failed to read WAV header.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // Write header to output
    size_t header_written = fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);
    if (header_written != HEADER_SIZE)
    {
        printf("Failed to write WAV header.\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // Buffer for a single sample (16-bit signed)
    int16_t sample_in;
    // Read samples until none left
    while (fread(&sample_in, sizeof(int16_t), 1, input) == 1)
    {
        // Convert to float, scale, round, and clip to int16 range
        float scaled = sample_in * factor;

        if (scaled > (float)INT16_MAX)
        {
            scaled = (float)INT16_MAX;
        }
        else if (scaled < (float)INT16_MIN)
        {
            scaled = (float)INT16_MIN;
        }

        // Round to nearest integer before casting
        int16_t sample_out = (int16_t) roundf(scaled);

        // Write updated sample
        if (fwrite(&sample_out, sizeof(int16_t), 1, output) != 1)
        {
            printf("Failed to write sample to output.\n");
            fclose(input);
            fclose(output);
            return 1;
        }
    }

    // Close files
    fclose(input);
    fclose(output);

    return 0;
}
