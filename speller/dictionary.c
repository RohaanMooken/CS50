// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;
unsigned int c = 0;
unsigned int num[N];

// Hash table
node *table[N];

bool searchWord(node *node, const char *word)
{
    // printf("%s : %s\n", node->word, word);
    if (strcmp(node->word, word) == 0)
    {
        return true;
    }
    else if (node->next == NULL)
    {
        return false;
    }
    else
    {
        return searchWord(node->next, word);
    }

    return false;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);

    // printf("%i\n", index);

    if (table[index] == NULL)
    {
        return false;
    }

    char lowercaseWord[LENGTH + 1]; // Assuming LENGTH is defined
    int i;

    // Convert word to lowercase
    for (i = 0; word[i] != '\0'; i++)
    {
        lowercaseWord[i] = tolower(word[i]);
    }

    lowercaseWord[i] = '\0'; // Null-terminate the lowercase word

    if (searchWord(table[index], lowercaseWord))
    {
        return true;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    if (strlen(word) < 2)
    {
        // Word is too short, return a default value
        return ((toupper(word[0]) - 'A') * 26);
    }

    unsigned int index = (((toupper(word[0]) - 'A') * 26) + (toupper(word[1]) - 'A'));
    return index;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict_pointer = fopen(dictionary, "r");
    // Check if null
    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
    // Initialise word array
    char next_word[LENGTH + 1];
    // Read strings from file one at a time
    while (fscanf(dict_pointer, "%s", next_word) != EOF)
    {
        // Create new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        // copy word into node using strcopy
        strcpy(n->word, next_word);
        // Hash word to obtain hash value
        int hash_value = hash(next_word);
        // Insert node into hash table at that location
        n->next = table[hash_value];
        table[hash_value] = n;
        c++;
    }
    // Close file
    fclose(dict_pointer);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (c > 0)
    {
        return c;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate over hash table and free nodes in each linked list
    for (int i = 0; i < N; i++)
    {
        // Assign cursor
        node *n = table[i];
        // Loop through linked list
        while (n != NULL)
        {
            // Make temp equal cursor;
            node *tmp = n;
            // Point cursor to next element
            n = n->next;
            // free temp
            free(tmp);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
