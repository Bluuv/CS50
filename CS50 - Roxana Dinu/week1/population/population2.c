#include <cs50.h>
#include <stdio.h>

int growing (int s, int e);
int main(void)
{
    // TODO: Prompt for start size
    int startsize;
    do
    {
        startsize = get_int ("Population start size: ");
    } while (startsize<9);
    // TODO: Prompt for end size
    int endsize;
    do
    {
        endsize = get_int ("Population end size: ");
    } while (endsize<startsize);
    // TODO: Calculate number of years until we reach threshold
    int years  = growing(startsize, endsize);
    // TODO: Print number of years
    printf("Required number of years: %i\n", years);
}

int growing (int s, int e)
{
    int i;
    for (i=0; s < e; i++)
    {
        s = s+(int)(s/3)-(int)(s/4);
    }

    return i;
}