#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //int x;
    //printf("x: ");
    //scanf("%i", &x);
    //printf("x: %i\n", x);
    char *s = malloc(4);
    printf("s: ");
    scanf("%s", s);
    printf("s: %s\n", s);
}