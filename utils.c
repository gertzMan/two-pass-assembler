#include "header.h"

/*
 --------------- util --------------

 This file contains utility functions for different parts of the code
 ---------------------------------------
 */


/*
 --------------- general --------------
 
 general utils functions for every stage
 ---------------------------------------
 */

/* A function that checks if pointer is null, it can help with
* valadating memory allocations.
*/
void checkAllocation(void * ptr)
{
    if (!ptr)
    {
        printf("The program has quit due to a memory allocation error.\n");
        exit(0);
    }
}


/* A function that checks if token is a comment */
int checkComment(char * candidate)
{
    return(*candidate == ';')? TRUE : FALSE;
}

/*
 * A function that takes in a parameter and divides it into parts,
 * such that each part represents a whole number.
 */
void splitNumbers(char * currNum, int line, int * DC)
{
    /* if the token is null */
    if (!(currNum = strtok(NULL, " ,\t\n")))
    {
        /* add error and return */
        addError("You must specify numbers", line, NULL);
        return;
    }
    /* if token is not null */
    else
    {
        /* send first token to addNumber() */
            addNumber(currNum, line, DC);
        /* send the rest tokens to addNumber() */
        while ((currNum = strtok(NULL, " ,\t\n")))
        {
            addNumber(currNum, line, DC);
        }
    }
}

/*
 --------------- firstStage --------------
 
 firstStage utility functions 
 
 -----------------------------------------
 */


/* Check if candidate is meant to be a label   */
char *  labelFormValidation(char * candidate){

    if(candidate[strlen(candidate) - 1] == ':'){
        candidate[strlen(candidate) - 1] = '\0';
        return candidate;
    }
    return 0;
}


/* Check if label is valid (by syntax)   */
char *  labelNamingValidation(char * label){

    char * ptr = label;

    if (!isalpha(*ptr)){
        return 0;
    }
    
    while ((*ptr) != '\0')
    {
        if (!isalpha(*ptr))
        {
            if (!isdigit(*ptr))
            {
                return 0;
            }
        }
        ptr++;
    }
    return label;
}


/*
* A function that determines if an operation 
* has been identified. 
*/
int isOperation(char * currWord)
{
    int i;
        Opcode opCodes[NUM_OF_OPCODES] = {
        {"mov", 0, 1705},
        {"cmp", 1, 1769},
        {"add", 2, 1705},
        {"sub", 3, 1705},
        {"not", 4, 42},
        {"clr", 5, 42},
        {"lea", 6, 553},
        {"inc", 7, 42},
        {"dec", 8, 42},
        {"jmp", 9, 58},
        {"bne", 10, 58},
        {"red", 11, 42},
        {"prn", 12, 106},
        {"jsr", 13, 58},
        {"rts", 14, 4},
        {"stop", 15, 4}};
	

    for (i = 0; i < OPCODES_AMOUNT; i++)
    {
	
        if (!strcmp(currWord, opCodes[i].str))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/*
* A function that determines if a register 
* has been identified.
*/
int isRegister(char * currWord)
{
    int i;
    char * registers[NUM_OF_REGISTERS] = {"r1", "r2", "r3", "r4", "r5", "r6", "r7"};
    if (strlen(currWord) == 2)
    {
        if (currWord[0] == 'r')
        {
            if (isdigit(currWord[1]))
            {
                for (i=0; i<NUM_OF_REGISTERS; i++)
                {
                    if (!strcmp(currWord, registers[i]))
                    {
                        return TRUE;
                    }
                }

            }
        }
    }
    return FALSE;
}


/*This function determines if we received a directive.
 it will return an enum int of the proper directive, or an error flag
 if there's no such directive. if the string doesn't start with ".",
 it will return an enum defined as NONE, meaning it is not a directive*/
int getDirective(char * token)
{
    /* if first char is '.' */
    if (*token == '.')
    {
        /* return enum corresponding to the directive */
        if (!strcmp(token, STR_DIRECTIVE_DATA))
        {
            return DIRECTIVE_DATA;
        }
        else if (!strcmp(token, STR_DIRECTIVE_STRING))
        {
            return DIRECTIVE_STRING;
        }
        else if (!strcmp(token, STR_DIRECTIVE_ENTRY))
        {
            return DIRECTIVE_ENTRY;
        }
        else if (!strcmp(token, STR_DIRECTIVE_EXTERN))
        {
            return DIRECTIVE_EXTERN;
        }
        /* if string is unknown */
        else
        {
            /* return error */
            return DIRECTIVE_ERROR;
        }
    }
    /* if this isn't a directive */
    else
    {
        return DIRECTIVE_NONE;
    }

}

/*
 --------------- thrirdStage --------------

 Third stage utility functions.

 -----------------------------------------
 */

/* 
* A function that converts a bit patternt into the special 
* binary numbering system we use. 1 -> / and 0 -> .
*/

void convertToStrange2(unsigned int word, char* target )
{
    int i;
    for (i=0; i<BITS_IN_WORD; i++ )
    {
        target[i] = ((1<<(BITS_IN_WORD-1-i)) & word)? '/':'.';
    }
target[i] = '\0';
}


/*
* A function that checks if the given candidate is the format expected of
* the operands of the jump addressing ( adressing method 2) method. 
* It returns null if not in the expected format otherwise it returns the 
* first occurrence of the opening bracket    
*/
int secondMethodFormValidation(char * candidate){
    char * ptr = candidate;
    int i = 0;
    int numOfBlancs = 0;	
    int openPlacing = 0; /* The first occurrence of the opening bracket */
    int closePlacing = 0; /* The first occurrence of the closing bracket  */
    int commaPlacing = 0;

    while((ptr[i]) && (ptr[i] != '\n')){
        if((ptr[i] == '(')){
            if(commaPlacing || closePlacing || openPlacing){
                return FALSE;

            } else {
                openPlacing = i - numOfBlancs;
            }
        }
        if((ptr[i] == ',')){
            if(commaPlacing || closePlacing){
                return FALSE;

            } else {
                commaPlacing = i;

            }
        }
        if((ptr[i] == ')')){
            if(closePlacing){
                return FALSE;

            } else {
                closePlacing = i;
            }
        }
        if(ptr[i] == '\t' || ptr[i] == ' '){
            if(openPlacing){
                return FALSE;
            } else {
                numOfBlancs ++;
            }
        }
            i++;

    }

    if(openPlacing && closePlacing && commaPlacing){
        return openPlacing;
    } else {
        return FALSE;
    }
}

/*
* A function that adds the given word to the word list. It recieves the word, 
* the line, the addressing method and if it is a source operand. 
* It determines how to code the word, and adds it. 
*/
void addAdditional(char *param,int method,int isSource,int *IC,int line){
    WordLine *wordToAdd = (WordLine *)(calloc(1,sizeof(WordLine)));
    checkAllocation(wordToAdd);
    (*IC)++;
    wordToAdd->line = line;

    if(method == IMMEDIATE){
        int num = atoi(param+1);
        wordToAdd->word |= num PUSH_IMMEDIATE;
    } else if(method == DIRECT) {
        wordToAdd->missingLabel = (char *)(malloc(sizeof(char)));
        strcpy(wordToAdd->missingLabel,param);
        wordToAdd->word = 0;
    } else {
        int num = atoi(param+1);
        if(isSource){
            wordToAdd->word |= num PUSH_SRC_REG;
        } else{
            wordToAdd->word |= num PUSH_TARG_REG;
        }
    }

    addWordLine(wordToAdd);
}

/* A function that checkes if the given string is a reserved label (register or oparation)  */
int labelReservedNameValidation(char * str){
    return (isOperation(str) || isRegister(str));
}

/* A function that opens a file with the given name (and extention) and returnes the instance of the file object */
FILE * openFile(char* filename, char * mode, char * extension)
{
    /*Temp file to be returned*/
    FILE * tmp = NULL;
    /*Full filename string*/
    char full_filename[FILE_NAME_LEN];
    /*Copy the filename from argv to the full filename string*/
    strcpy(full_filename, filename);
    /*Add the .as extension to the full filename.*/
    strcat(full_filename, extension);
    /*Open the file. if fopen return null, exit the function and print error to screen*/
    if (!(tmp = fopen(full_filename, mode)))
    {
        printf("Can't open file %s.\n", full_filename);
        return NULL;
    }
    /*Return pointer to the file*/
    return tmp;
}
