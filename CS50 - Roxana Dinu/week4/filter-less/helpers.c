#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            int grey_value=round((image[i][j].rgbtBlue+image[i][j].rgbtGreen+image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue=grey_value;
            image[i][j].rgbtGreen=grey_value;
            image[i][j].rgbtRed=grey_value;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
        for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            int originalRed = (int)image[i][j].rgbtRed;
            int originalGreen = (int)image[i][j].rgbtGreen;
            int originalBlue = (int)image[i][j].rgbtBlue;

            image[i][j].rgbtBlue= round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            image[i][j].rgbtGreen= round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            image[i][j].rgbtRed= round (.393 * originalRed + .769 * originalGreen + .189 * originalBlue);


            if (image[i][j].rgbtGreen > 255)
            {
                image[i][j].rgbtGreen=255;
            }
            if (image[i][j].rgbtBlue > 255)
            {
                image[i][j].rgbtBlue=255;
            }
            if (image[i][j].rgbtRed > 255)
            {
                image[i][j].rgbtRed=255;
            }
        //printf("\n");

        }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height/2; i++)
    {
        for(int j=0; j<width; j++)
        {
            int tempRed=image[i][j].rgbtRed;
            int tempBlue=image[i][j].rgbtBlue;
            int tempGreen=image[i][j].rgbtGreen;

            image[i][j].rgbtRed = image[height-1-i][j].rgbtRed;
            image[i][j].rgbtGreen = image[height-1-i][j].rgbtGreen;
            image[i][j].rgbtBlue = image[height-1-i][j].rgbtBlue;

            image[height-1-i][j].rgbtRed = tempRed;
            image[height-1-i][j].rgbtGreen = tempGreen;
            image[height-1-i][j].rgbtBlue = tempBlue;

        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int a=0; a<height; a++)
    {
        for(int b=0; b<width; b++)
        {
            copy[a][b]=image[a][b];
        }
    }

    for(int i=1; i<height-1; i++)
    {
        for(int j=1; j<width-1; j++)
        {
            image[i][j].rgbtRed= (copy[i][j].rgbtRed+copy[i-1][j].rgbtRed+copy[i+1][j].rgbtRed+
                                    copy[i][j-1].rgbtRed+copy[i][j+1].rgbtRed+copy[i-1][j-1].rgbtRed+copy[i-1][j+1].rgbtRed+copy[i+1][j-1].rgbtRed+copy[i+1][j+1].rgbtRed)/9;
            image[i][j].rgbtGreen= (copy[i][j].rgbtGreen+copy[i-1][j].rgbtGreen+copy[i+1][j].rgbtGreen+
                                    copy[i][j-1].rgbtGreen+copy[i][j+1].rgbtGreen+copy[i-1][j-1].rgbtGreen+copy[i-1][j+1].rgbtGreen+copy[i+1][j-1].rgbtGreen+copy[i+1][j+1].rgbtGreen)/9;
            image[i][j].rgbtBlue= (copy[i][j].rgbtBlue+copy[i-1][j].rgbtBlue+copy[i+1][j].rgbtBlue+
                                    copy[i][j-1].rgbtBlue+copy[i][j+1].rgbtBlue+copy[i-1][j-1].rgbtBlue+copy[i-1][j+1].rgbtBlue+copy[i+1][j-1].rgbtBlue+copy[i+1][j+1].rgbtBlue)/9;
        }
    }

           return;
}
