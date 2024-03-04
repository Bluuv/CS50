#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startsize = get_int ("Population start size: ");
    while (startsize<9)
    {
        startsize = get_int ("Population start size must be bigger than 9: ");
    }
    // TODO: Prompt for end size
    int endsize = get_int ("Population end size: ");
    while (endsize<startsize)
    {
        endsize = get_int ( `"Population end size must not be less than start size: ");
    }
    // TODO: Calculate number of years until we reach threshold
        int i = 0;
        while (startsize < endsize)
        {
            startsize  = startsize+(int)(startsize/3)-(int)(startsize/4);
            i++;
        }
        // TODO: Print number of years
    printf("Required number of years: %i\n", i);
}
