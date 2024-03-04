#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
         printf("Pls write smth uwu <3\n");
         return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if(input_file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    //Store blocks of 512 bytes into an array
    unsigned char buffer[512];

    //Track number of images generated
    int count_img=0;

    //File pointer for recovered images
    FILE *out_file = NULL;

    //Allocate memory for the filename
    char *filename = malloc(8 * sizeof(char));
    //Read 512 Bytes and Store on buffer
    while(fread(buffer, sizeof(char), 512, input_file))
    {
        if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3] & 0xf0)==0xe0)
        {
            count_img++;
            sprintf(filename, "./recovered/a%i.jpg", count_img);
            out_file=fopen(filename, "w");
        }
        if(out_file!=NULL)
        {
            fwrite(buffer, sizeof(char), 512, out_file);

        }
    }

    free(filename);
    fclose(out_file);
    fclose(input_file);


}