#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if(argc==2)
    {
        printf("\n");
    }
    else
    {
        printf("Please specify the key\n");
        return 1;
    }
    int digitsize=strlen(argv[1]);
    for(int i=0; i<digitsize; i++)
    {
        if(strcmp(argv[i],"9")<0 && strcmp(argv[i],"0")>0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int k=atoi(argv[1]);

    string plaintext=get_string("plaintext:  ");
    int n = strlen(plaintext);
    char ciphertext[n];
    printf("ciphertext:  ");
    for(int c=0, p=0; c<n; c++, p++)
    {
        if(plaintext[p]>=65 && plaintext[p]<=90)
        {
            ciphertext[c]=65+(plaintext[p]-65+k)%26;
        }
        else if(plaintext[p]>=97 && plaintext[p]<=122)
        {
            ciphertext[c]=97+(plaintext[p]-97+k)%26;
        }

        if(ciphertext[c]>90 && ciphertext[c]<97)
        {
            ciphertext[c]=65+ciphertext[c]-90;
        }
        else if (ciphertext[c]>122)
        {
            ciphertext[c]=97+ciphertext[c]-122;
        }
        printf("%c", ciphertext[c]);
    }
    printf("\n");
    //printf("ciphertext: %s\n", ciphertext);
}