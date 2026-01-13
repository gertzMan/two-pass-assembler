#include "header.h"
/*
---------------------------------------- dataList ----------------------------------------

 The dataList is a linked list that contains the data that is to be encoded.
 This file contains the functions needed for managing and manipulating this list.
------------------------------------------------------------------------------------------
*/

static Data * head = NULL;

/*
 * A function that adds a number to the list.
 */
void addNumber(char * number, int line, int * DC)
{
  char * ptr = NULL;
  Data * tmp = NULL;
  long int tmpNum;

  /* convert to decimal number */
  tmpNum = strtol(number, &ptr, DECIMAL_BASE);
    
  /* if conversion failed an error is added to the error list */
  if (*ptr != '\0')
  {
  addError("Invalid number", line, number);
  return;
  }

  /* creation of a new pointer to work with */
  tmp = malloc(sizeof(Data));
  checkAllocation(tmp);

  tmp->word = (short int)tmpNum;
  tmp->next = NULL;

  if (!head)
  {
    head = tmp;
  }

  else
  {
    Data * p = head;
    while (p->next)
      p = p->next;
    p->next = tmp;
  }
  (*DC)++;
}

/*
 * When adding a string to the list, we actually need to add
 * the characters the string consists of. This function does
 * just that.
 */
void addChar(char c)
{
  Data * tmp = malloc(sizeof(Data));
  tmp->word = c;
  tmp->next = NULL;
  if (!head)
  {
    head = tmp;
  }
  else
  {
    Data * p = head;
    while (p->next)
      p = p->next;
    p->next = tmp;
  }
}

/*
 * A function that adds a string to the list
 */
void addString(char * string, int line, int *DC)
{
  /* check if only one pair of quotation marks was input, and issue an error if needed */
  if (!strcmp(string, "\""))
  {
    addError("Must specify a string", line, NULL);
    return;
  }
  /* validate string quotation marks format */
  if ((*string == '"') && (string[strlen(string) - 1] == '"'))
  {
    /* if correct format is recognized, change the last mark to the NULL terminator sign */
    string[strlen(string) - 1] = '\0';
    string++;
  }
  /* if validation is bad add an error */
  else
  {
    addError("Strings must be surrounded by quotation marks", line, NULL);
    return;
  }

  /* once format is identified to be correct, the function adds the characters */
  while (*string != '\0')
  {
    addChar(*string);
    string++;
    /* increment data count */
    (*DC)++;
  }
  addChar(0);
  /* increment data count */
  (*DC)++;
}

/*
 * A function returns the number of nodes in the list.
 */
int countData()
{
  int counter = 0;
  Data * ptr = head;
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
 * A function that updates the addresses of the data list's words once the instruction and data counters are calculated.
 */
void updateDataAddresses(int IC)
{
  Data * ptr;
  ptr = head;
  if (!ptr)
  {
    return;
  }

  while (ptr)
  {
    ptr->address = IC;
    IC++;
    ptr = ptr->next;
  }
}

/* A function that frees the linked list */
void freeData()
{
  Data * ptr = head;
  if (!ptr)
    return;
  while (ptr)
  {
    Data * tmp = ptr;
    ptr = ptr->next;
    free(tmp);
  }
    head = NULL;
}

Data * getHeadData()
{
  Data * tmp = head;
  return tmp;
}