#include "header.h"
/*
---------------------------------------- validationErrors ---------------------------------------

 Instead of sending the errors to the err steam, we create a an error file in case of any
 error detected. If an error is detected it is added as a node to a linked list, and finally printed
 out to an errors file.
--------------------------------------------------------------------------------------------------
*/

static Error * head = NULL;

/*
 * A function that adds an error to to the list.
 * Parameters:
 * err: error description.
 * line: the line of the error.
 * str: additional error description.
 */
void addError(char * err, int line, char * str)
{
    Error * tmp = malloc(sizeof(Error));
    checkAllocation(tmp);

    tmp->str_error = err;
    tmp->line = line;
    /* if we received another string */
    if (str)
    {
        /* check if last char is newline, if so, remove it */
        if (str[strlen(str)-1] == '\n')
        {
            str[strlen(str)-1] = 0;
        }
        /* assign the string to str */
        tmp->str = malloc(sizeof(char) * MAX_LINE);
        checkAllocation(tmp->str);
        strcpy(tmp->str, str);
    }
    /* if we didn't receive another string */
    else
    {
        tmp->str = NULL;
    }
        tmp->next = NULL;
    if (!head)
    {
        head = tmp;
    }
    else
    {
        Error * p = head;
        while (p->next)
            p = p->next;
        /* point it to the new error */
        p->next = tmp;
    }

}

/*
 * A function to check if the error list is empty or not
 */
int isError()
{
    if (head)
        return TRUE;
    else
        return FALSE;
}

/*
 * A function that returns the last line an error was found in.
 */
int getMaxLine()
{
    Error * p;
    int maxLine = 1;
    p = head;
    if (!p)
        return FALSE;
    while (p)
    {
        if (p->line > maxLine)
            maxLine = p->line;
        p = p->next;
    }
    return maxLine;
}

/* A function that writes the errors found to the error list */
void printErrors(char * filename)
{
    FILE * tmp = NULL;
    Error * ptr = head;
    int maxLine = getMaxLine();
    int index = 1;

    char error_filename[FILE_NAME_LEN];
    strcpy(error_filename, "errors-");
    strcat(error_filename, filename);

    if ((tmp = openFile(error_filename, "w", TXT_EXTENSION)))
    {
        if (!ptr)
        {
            fclose(tmp);
            return;
        }
        while (index <= maxLine)
        {
            ptr = head;
            while (ptr)
            {
                if (ptr->line == index)
                {
                    if (ptr->str)
                        fprintf(tmp, "ERROR, LINE %d:\t %s \"%s\".\n", ptr->line, ptr->str_error, ptr->str);
                    else
                    {
                        fprintf(tmp, "ERROR, LINE %d:\t %s.\n", ptr->line, ptr->str_error);
                    }
                }
                ptr = ptr->next;
            }
            index++;
        }
        ptr = head;
        while (ptr)
        {
            if (ptr->line < 0)
            {
                if (ptr->str)
                    fprintf(tmp, "%s: \"%s\"\n.", ptr->str_error, ptr->str);
                else
                {
                    fprintf(tmp, "%s.\n", ptr->str_error);
                }
            }
            ptr = ptr->next;
        }
        printf("Operation failed. Errors exported to %s.txt\n", error_filename);
    }
    fclose(tmp);

}

/* A function that frees the errors list */
void freeErrors()
{
    Error * ptr = head;
    if (!ptr)
        return;

    while (ptr)
    {
        Error * tmp = ptr;
        ptr = ptr->next;
        free(tmp->str);
        free(tmp);
    }
    head = NULL;
}
