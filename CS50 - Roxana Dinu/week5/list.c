#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Dynamically allocate an array of size 3
    int *list = malloc(3 * sizeof(int));
    if (list==NULL)
    {
        return 1;
    }
    // Assign 3 numbers to the array

    list[0]=1;
    list[1]=2;
    list[2]=3;

    // *list=1;
    // *(list+1)=2;
    // *(list+2)=3;

    //TIME PASSES

    // Allocate new array of size 4
    // int *tmp = malloc(4 * sizeof(int));

    // if (tmp==NULL)
    // {
    //     free(list);
    //     return 1;
    // }

    // Resize old array to be of size 4
    int *tmp = realloc(list, 4 * sizeof(int));

    if (tmp==NULL)
    {
        free(list);
        return 1;
    }

    // Copy numbers from old array to new array, Unnecesarry for REALLOC
    // for (int i =0; i<3; i++)
    // {
    //     tmp[i] = list[i];
    // }

    // Add 4th number to new array
    tmp[3]=4;

    // Free old array, Unnecesarry for REALLOC
    //free(list);

    // Remember new array
    list=tmp;

    // Print new array
    for (int i =0; i<4; i++)
    {
        printf("%i\n", list[i]);
    }
    return 0;

    // Free mew array
    free(list);
}