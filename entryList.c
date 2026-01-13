#include "header.h"

/*
---------------------------------------- entryList ----------------------------------------

 The entry list is a linked list that contains information about ".entry" labels.
 This file contains the functions needed for managing and manipulating this list.
------------------------------------------------------------------------------------------
*/

static Entry * head = NULL;

/* A function that adds a node to the entry list*/
void addEntry(char * label, int line)
{
    Entry * tmp = NULL;
    if (!(checkEntry(label)))
    {
        addError("Multiple entries with same label", line, label);
        return;
    }
    tmp = malloc(sizeof(Entry));
    checkAllocation(tmp);
    tmp->label = malloc(sizeof(char)*MAX_LINE);
    strcpy(tmp->label, label);

    tmp->address = 0;
    tmp->line = line;
    tmp->hasAddress = FALSE;
    tmp->next = NULL;

    if (!head)
    {
        head = tmp;
    }

    else
    {
        Entry * p = head;
        while (p->next)
            p = p->next;
        p->next = tmp;
    }
}

/*
 * A function that checks for duplicity(identical label)
 */
int checkEntry(char * label)
{
    Entry * ptr = head;
    while (ptr)
    {
        if (!strcmp(ptr->label, label))
        {
            return FALSE;
        }
        ptr = ptr->next;
    }
    return TRUE;
}

/* A function the frees the list */
void freeEntries()
{
    Entry * ptr = head;
    if (!ptr)
        return;
    while (ptr)
    {
        Entry * tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    head = NULL;
}

/*
 * A function that returns an entry node that does not have an address.
 */
Entry * getEntry()
{
    Entry *ptr = head;
    while (ptr)
    {
        if (!ptr->hasAddress)
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

Entry * getHeadEntry()
{
    Entry * tmp = head;
    return tmp;
}