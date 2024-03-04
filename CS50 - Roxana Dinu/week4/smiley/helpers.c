#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<width; i++)
    {
        for (int j=0; j<height; j++)
        {
            if(image[j][i].rgbtRed==0x00 && image[j][i].rgbtGreen==0x00 && image[j][i].rgbtBlue==0x00)
            {
                image[j][i].rgbtRed=0xd1;
                image[j][i].rgbtGreen=0xb1;
                image[j][i].rgbtBlue=0xcb;
            }
            // else
            // {
            //     image[j][i].rgbtRed=0x5d;
            //     image[j][i].rgbtGreen=0x57;
            //     image[j][i].rgbtBlue=0x6b;
            // }
        }
    }
    // Change all black pixels to a color of your choosing
}
