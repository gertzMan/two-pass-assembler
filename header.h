#ifndef HEADER_H
#define HEADER_H

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structs.h"
#include "defines.h"

/* functions implemented in firstStage.c functions */
void firstPass(FILE * f, int * counter, int * DC);

/* functions implemented in secondStage.c functions */
void secondPass();

/* functions implemented in thirdStage.c*/
void thirdStage(char * name);

/* functions implemented in validationErrors.c functions */
void addError(char * err, int line, char * str);
void printErrors(char * filename);
void freeErrors();
int isError();
int getMaxLine();

/* functions implemented in symbolList.c functions */
void addSymbol(char * label, int address, int external, int operation, int line);
void freeSymbols();
void checkSymbol(char * label, int line);
Label* searchSymbol(char * label);
void updateSymbols(int IC);

/* functions implemented in dataList.c functions */
void addNumber(char * number, int line, int * DC);
void splitNumbers(char * token, int line, int * DC);
void freeData();
void addString(char * string, int line, int *DC);
void addChar(char c);
Data * getHeadData();
int countData();
void updateDataAddresses(int IC);

/* functions implemented in utils.c functions */
void checkAllocation(void * ptr);
int getDirective(char * token);
int checkComment(char * candidate);
void convertToStrange2(unsigned int word, char* str );
int labelReservedNameValidation(char * str);
FILE * openFile(char* filename, char * mode, char * extension);
char *  labelNamingValidation(char * label);
char *  labelFormValidation(char * candidate);

/* functions implemented in entryList.c functions */
void addEntry(char * label, int line);
void freeEntries();
int checkEntry(char * label);
Entry * getEntry();
Entry * getHeadEntry();

/* functions implemented in operandAnalysis.c functions */
void analyzeOperation(char * token, int line, int *IC);
int isRegister(char * token);
int isOperation(char * token);
int secondMethodFormValidation(char * candidate);
void addAdditional(char *param,int method,int isSource,int *IC,int line);

/* functions implemented in wordsList.c functions */
void addWordLine(WordLine * node);
void freeWords();
void freeWord(WordLine * ptr);
WordLine * getMissingLabel();
WordLine * getHeadWord();
int countWords();
void updateAddresses();

#endif