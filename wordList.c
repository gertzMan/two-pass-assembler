#include "header.h"
/*
---------------------------------------- wordList ---------------------------------------

 The wordList is a linked list that contains the commands to be encoded.
 This file contains the functions needed for managing and manipulating this list.
-----------------------------------------------------------------------------------------
*/

static WordLine * head = NULL;

/*
 * A function that adds a new wordLine node to the list.
 */
void addWordLine(WordLine * node)
{
    if (!head)
    {
        head = node;
    }
    else
    {
        WordLine *p = head;
        while (p->next)
            p = p->next;
        p->next = node;
    }
}

/*
 * A function that updates the words throughout the list with their
 * correct respective addresses
 */
void updateAddresses()
{
    int address = STARTING_ADDRESS;
    WordLine * ptr = getHeadWord();
    if (!ptr)
        return;

    while (ptr)
    {
        ptr->address = address;
        address++;
        ptr = ptr->next;
    }
}

/*
 * A function the returns the number of words currently in the list
 */
int countWords()
{
    int counter = 0;
    WordLine * ptr = head;
    if (!ptr)
        return counter;

    while (ptr)
    {
        counter++;
        ptr = ptr->next;
    }
    return counter;
}

/*
 * A function that frees the memory allocated to the the words throughout the list
 */
void freeWords()
{
    WordLine * ptr = head;
    if (!ptr)
        return;

    while (ptr)
    {
        WordLine * tmp = ptr;
        ptr = ptr->next;

        free(tmp->missingLabel);
        free(tmp);
    }
    head = NULL;
}

/* A function that frees up only one word */
void freeWord(WordLine * ptr)
{
    if (!ptr)
        return;
        free(ptr->missingLabel);
        free(ptr);
}

/*
 * A function that iterates over list in search of a word with a missing label.
 * if such a word is found it is returned. else null is returned.
 */
WordLine * getMissingLabel()
{
    WordLine * p = head;

    while (p)
    {
        if (p->missingLabel)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

/*
 * A function that returns the first current head of the list.
 */
WordLine * getHeadWord()
{
    WordLine * tmp;
    tmp = head;
    return tmp;
}
