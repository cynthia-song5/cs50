// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int Wsize = 0;
// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //case insensitive
    //get hash value of word to compare
    int hash_value = hash(word);

    //access linked list at position hash_value
    node *n = table[hash_value];
    //find word in linked list
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    long sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        sum += tolower(word[i]);
    }

    //return the remainder to get the values for the letter in the alphabet array
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //read file
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    char words[LENGTH + 1];
    //scan through the file
    //file to read from, format, where to be stored
    //will read until the end
    while (fscanf(file, "%s", words) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (!n)
        {
            return false;
        }
        //copy word into node
        strcpy(n -> word, words);
        //hash word to obtain hash value
        int hash_value = hash(words);
        //insert node into hash table at location
        n-> next = table[hash_value];
        table[hash_value] = n;
        Wsize++;
    }
    //close file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return Wsize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //free nodes from every linked list
    for (int i = 0; i < N; i++)
    {
        //assign cursor
        node *n = table[i];
        while (n)
        {
            //make temporary variable equal cursor;
            node *tmp = n;
            //point cursor to next element
            n = n->next;
            //free temporary variabl
            free(tmp);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
