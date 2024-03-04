// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#define  _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 306;

// Hash table
node *table[N];

//Declare variables
unsigned int word_count=0;
unsigned int hash_value=0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // TODO
    //Hash the word to obtain a hash value
    hash_value = hash(word);

    //Point cursor to the node
    node *cursor = table[hash_value-1];

    //Go through the linked list
    while (cursor != NULL)
    {
        if(strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //return toupper(word[0]) - 'A';
    unsigned int fin_hash=0;
    int prim=31;
    for(int i=0; i<strlen(word); i++)
    {
        fin_hash=fin_hash + (word[i] * (int)pow(prim,i));
    }
    return fin_hash % N;
    // return strlen(word);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH+1];
    size_t len=0;
    int hash_plm ;
    bool check = false;

    // // TODO
    //Open dictionary and read words line by line
    FILE *dick_file=fopen(dictionary, "r");

    while (fscanf(dick_file, "%45s/n", word) == 1)
    {
        hash_plm=hash(word);
        // printf("%d\n", hash_plm);

        //Create linked list of size 0
        node *first = NULL;

        //Add word to the node
        node *n = malloc(sizeof(node));
        node *p = table[hash_plm-1];
        if (n==NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next=NULL;
        word_count++;

        while(p!=NULL && p->next!=NULL)
        {
            p=p->next;
        }

        if (p==NULL)
        {
            table[hash_plm-1]=n;
            check = true;
        }
        else
        {
            p->next = n;
            check = true;
        }

    }

    if(check==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if(word_count >0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    //Iterate through buckets
    for(int i = 0; i<N; i++)
    {
        //Set cursor to the start of the linked list
        node *cursor = table[i];

        //If cursor is not NULL, free memory

        while(cursor!=NULL)
        {
            //Create temp
            node *temp = cursor;
            //Move cursor to next node
            cursor=cursor->next;
            //Free up temp
            free(temp);
        }
        if (cursor == NULL)
        {
           return true;
        }
    }
    return false;
}
