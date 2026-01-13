#ifndef DEFINES_H
#define DEFINES_H
/*
 --------------- defines --------------

 This file contains define directive for
 use across the code.
 ---------------------------------------
 */

/* boolean enum */
enum boolean {FALSE, TRUE};

/*  Definitions that improve code redability
 * and help avoid "Magic numbers" -
 * the appearance of pure numbers in the code
 */
#define DECIMAL_BASE       10
#define BITS_IN_WORD       14
#define FILE_NAME_LEN      501
#define NUM_OF_REGISTERS   8
#define OPCODES_AMOUNT     16
#define MAX_CODE_LINES     256
#define NUM_OF_OPCODES 16
#define STARTING_ADDRESS 100

/* BITWISE operations shortcuts */
#define PUSH_SOURCE_OPERAN <<4
#define PUSH_TARGET_OPERAN <<2
#define PUSH_FIRST_PARAMER <<12
#define PUSH_SECOND_PARAME <<10
#define PUSH_OPCODE        <<6
#define PUSH_IMMEDIATE     <<2
#define PUSH_SRC_REG       <<8
#define PUSH_TARG_REG      <<2
#define MAX_LINE 80

/* enum directive used to identify the type of directive input.
 * each member represents a type of directive. NONE means no directive
 * and ERROR stands for a malformed directive
 */
enum directive{DIRECTIVE_NONE, DIRECTIVE_DATA, DIRECTIVE_STRING, DIRECTIVE_ENTRY, DIRECTIVE_EXTERN, DIRECTIVE_ERROR};

/* Addressing method enum - NONE means first word */
enum addresing_method {NONE = -1, IMMEDIATE = 0, DIRECT = 1, JUMP = 2, REGISTER = 3};

/* Directive string constants, to be compared with input */
#define STR_DIRECTIVE_DATA   ".data"
#define STR_DIRECTIVE_STRING ".string"
#define STR_DIRECTIVE_ENTRY  ".entry"
#define STR_DIRECTIVE_EXTERN ".extern"

/* File extensions */
#define AS_EXTENSION ".as"
#define TXT_EXTENSION ".txt"
#define OB_EXTENSION ".ob"
#define ENT_EXTENSION ".ent"
#define EXT_EXTENSION ".ext"

#endif


