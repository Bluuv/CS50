#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if(argc!=3)
    {
        printf("Pls provide input and output 🖤\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input_file=fopen(argv[1], "r");
    if(input_file==NULL)
    {
        printf("File could not be opened 🖤\n");
    }


    // Read header
    // TODO #3
    const int HEADER_SIZE = 44;
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, input_file);
    long header_end = ftell(input_file);

    // Use check_format to ensure WAV format
    // TODO #4
    if(check_format(header)!=1)
    {
        printf("Incorect Format\n");
        return 1;
    }


    // Open output file for writing
    // TODO #5

    FILE *output_file=fopen(argv[2], "w");

    // Write header to file
    // TODO #6
    fwrite(&header, HEADER_SIZE, 1, output_file);



    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);



    // Write reversed audio to file
    // TODO #8
    char *buffer = malloc(block_size * sizeof(char));
    //int file_end= fseek(input_file, 0, SEEK_END);
    if (fseek(input_file, block_size, SEEK_END))
    {
        return 1;
    }

    //while (ftell(input_file) - block_size > sizeof(header))
    while (ftell(input_file) - block_size > header_end)
    //while(ftell(input_file)>header_end)
    {
        if (fseek(input_file, -2*block_size, SEEK_CUR))
        {
            return 1;
        }
        fread(buffer, block_size, 1, input_file);
        fwrite(buffer, block_size, 1, output_file);



    }

    free(buffer);
    fclose(input_file);
    fclose(output_file);

}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0]=='W' && header.format[1]=='A' && header.format[2]=='V' && header.format[3]=='E')
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels*(header.bitsPerSample/8);

}