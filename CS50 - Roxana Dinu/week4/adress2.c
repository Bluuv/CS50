#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //string s="HI!";
    //printf("%s\n", s);
    char *s = "HI!";
    printf("%s\n", s);
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));

}