#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        h= get_int ("Height: ");
    } while (h<1 || h>8);
    for (int i=0; i<h; i++)
    {
        for (int j=1; j<=(2*(h+1)); j++)
        {
            if (j<h-i)
            {
                printf(" ");
            }
            else if (j>=h-i && j<h+1)
            {
                printf("#");
            }
            else if (j==h+1 || j==h+2 )
            {
                printf(" ");
            }
            else if (j>h+2 && j<=h+3+i )
            {
                printf("#");
            }
            else
            {
              printf(" ");
            }
        }
    printf("\n");
    }
}