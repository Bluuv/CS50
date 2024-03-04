#include <stdio.h>
#include <cs50.h>

    int main(void)
    {
        //Prompt user to agree
        char c = get_char("Do you agree? ");

        //Check whether user agreed
        if (c =='y')
        {
            printf("Agreed\n");
        }
        else if (c =='n')
        {
            printf("Disagreed\n");
        }
    }