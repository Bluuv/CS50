#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string message=get_string("Secret message: ");
    int wordsize=strlen(message);
    int nr=0;
    int inversebinary[8];
    int binary[8];

    for(int i=0; i<wordsize; i++)
    {
       nr=message[i];
       for (int j=0;j<8;j++)
       {
        inversebinary[j]=nr % 2;
        nr=(nr-nr % 2)/2;
       }
       for(int z=7, x=0; z>=0 && x<8; z--, x++)
       {
        binary[x]=inversebinary[z];
        print_bulb(binary[x]);
       }
       printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
