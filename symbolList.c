#include "header.h"
/*
---------------------------------------- symbolList ----------------------------------------

The symbol list is a linked list that contains information about all the labels in the program.
This file contains the functions needed for managing and manipulating this list.
--------------------------------------------------------------------------------------------
*/

static Label * head = NULL;

/* A function that adds a symbol node to the list */
void addSymbol(char * label, int address, int external, int operation, int line)
{
    Label * tmp = NULL;
    /* Check for any identical symbols */
    checkSymbol(label, line);

    tmp = malloc(sizeof(Label));
    checkAllocation(tmp);

    tmp->label = malloc(sizeof(char)*MAX_LINE);
    checkAllocation(tmp->label);

    /*Copy the label from the input to this symbol*/
    strcpy(tmp->label, label);
    /*Copy value of DC*/
    tmp->address = address;
    /*Copy external flag*/
    tmp->external = external;
    /*Copy operation tab*/
    tmp->operation = operation;
    tmp->next = NULL;

    if (!head)
    {
            head = tmp;
    }

    else
    {
        Label * p = head;
        while (p->next)
            p = p->next;
        p->next = tmp;
    }
}

/*
 * A function that is used after the first stage in order to update (when the final IC is known)
 * the addresses of the symbols that represents data in the list.
 */
void updateSymbols(int IC)
{
    Label * ptr = head;
    while (ptr)
    {
        if ((ptr->external == FALSE) && (ptr->operation == FALSE))
        {
            ptr->address += IC;
        }
        ptr = ptr->next;
    }
}


/* A function that frees the list*/
void freeSymbols()
{
    Label * ptr = head;
    if (!ptr)
        return;

    while (ptr)
    {
        Label * tmp = ptr;
        ptr = ptr->next;
        free(tmp->label);
        free(tmp);
    }
    head = NULL;
}

/* A function that looks for identical symbols and adds
 * an error to the error list if a duplicate is indeed found*/
void checkSymbol(char * label, int line)
{
    Label * ptr = head;
    while (ptr)
    {
        if (!strcmp(ptr->label, label))
        {
            addError("Multiple symbols with label", line, label);
            return;
        }
        ptr = ptr->next;
    }
}

/*
 * A function That will return a symbol with the same label as the string
 * passed to it .if no such symbol is found, it will return NULL
 */
Label * searchSymbol(char * label)
{
    Label *ptr = head;
    while (ptr)
    {
        if (!strcmp(ptr->label, label))
        {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

