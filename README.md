# Two-Pass Assembler for Custom Assembly Language

A comprehensive two-pass assembler implementation in C for a custom assembly language, developed as part of a Systems Programming course at the Open University of Israel.

**Authors:** Roey Yohanan & Adam Gertzkin

## 📋 Overview

This assembler translates assembly source code (`.as` files) into machine code (`.ob` files) along with symbol tables for entry and external labels. It implements a classic two-pass assembly algorithm with comprehensive error checking and validation.

## 🎯 Features

- **Two-Pass Assembly Algorithm**: Efficient symbol resolution and address calculation
- **16 Assembly Instructions**: Including arithmetic, logical, branching, and I/O operations
- **4 Addressing Methods**: Immediate, Direct, Jump with parameters, and Register
- **Comprehensive Error Handling**: Detailed error messages with line numbers
- **Symbol Management**: Support for external and entry labels
- **Custom Output Encoding**: Base-4-like encoding using `/` and `.` characters
- **Memory Validation**: 256-word memory limit enforcement

## 🏗️ Architecture

### Three-Stage Process

1. **First Pass** (`firstStage.c`)

   - Parses source code line by line
   - Validates labels and syntax
   - Builds symbol table
   - Encodes instructions preliminarily
   - Processes directives (`.data`, `.string`, `.entry`, `.extern`)

2. **Second Pass** (`secondStage.c`)

   - Resolves label addresses
   - Updates instruction words with correct addresses
   - Validates all symbol references
   - Checks memory limits

3. **Third Pass** (`thirdStage.c`)
   - Generates output files (`.ob`, `.ent`, `.ext`)
   - Converts to special base-4 encoding
   - Exports symbol tables

### Key Modules

| File                 | Purpose                            |
| -------------------- | ---------------------------------- |
| `main.c`             | Entry point and orchestration      |
| `firstStage.c`       | First pass parsing and encoding    |
| `secondStage.c`      | Symbol resolution                  |
| `thirdStage.c`       | File generation                    |
| `operandAnalysis.c`  | Instruction parsing and validation |
| `symbolList.c`       | Symbol table management            |
| `dataList.c`         | Data segment management            |
| `entryList.c`        | Entry labels tracking              |
| `wordList.c`         | Instruction word storage           |
| `validationErrors.c` | Error tracking and reporting       |
| `utils.c`            | Helper functions                   |

## 🛠️ Installation & Usage

### Prerequisites

- GCC compiler
- Make utility
- Unix-like environment (Linux, macOS, or WSL)

### Building the Assembler

```bash
make
```

This creates an executable named `assembler`.

### Running the Assembler

```bash
./assembler <filename1> [filename2] ...
```

**Note:** Omit the `.as` extension when specifying files.

**Example:**

```bash
./assembler examples/goodFile1 examples/badFile
```

### Output Files

For a successful assembly of `file.as`:

- **`file.ob`** - Object file with encoded machine code
- **`file.ent`** - Entry labels and their addresses (if any `.entry` directives exist)
- **`file.ext`** - External label references (if any external labels are used)

For files with errors:

- **`errors-file.txt`** - Detailed error report

### Cleaning Build Files

```bash
make clean
```

## 📝 Assembly Language Syntax

### Instruction Set

| Opcode | Instruction | Operands  | Description                          |
| ------ | ----------- | --------- | ------------------------------------ |
| 0      | `mov`       | src, dest | Move data from source to destination |
| 1      | `cmp`       | src, dest | Compare two operands                 |
| 2      | `add`       | src, dest | Add source to destination            |
| 3      | `sub`       | src, dest | Subtract source from destination     |
| 4      | `not`       | dest      | Bitwise NOT                          |
| 5      | `clr`       | dest      | Clear destination                    |
| 6      | `lea`       | src, dest | Load effective address               |
| 7      | `inc`       | dest      | Increment                            |
| 8      | `dec`       | dest      | Decrement                            |
| 9      | `jmp`       | dest      | Jump to address                      |
| 10     | `bne`       | dest      | Branch if not equal                  |
| 11     | `red`       | dest      | Read input                           |
| 12     | `prn`       | dest      | Print output                         |
| 13     | `jsr`       | dest      | Jump to subroutine                   |
| 14     | `rts`       | -         | Return from subroutine               |
| 15     | `stop`      | -         | Halt execution                       |

### Addressing Methods

1. **Immediate**: `#<number>` (e.g., `#-5`)
2. **Direct**: `<label>` (e.g., `LOOP`)
3. **Jump**: `<label>(<param1>,<param2>)` (e.g., `L1(#-1,r6)`)
4. **Register**: `r0` through `r7`

### Directives

- **`.data <number>[,<number>...]`** - Define data words
- **`.string "<text>"`** - Define string constant
- **`.entry <label>`** - Export label
- **`.extern <label>`** - Import external label

### Example Program

```assembly
; Example: Simple loop
.entry LENGTH
.extern W
MAIN:   mov r3,LENGTH
LOOP:   jmp L1(#-1,r6)
        prn #-5
        bne W(r4,r5)
        sub r1,r4
        bne L3
L1:     inc K
.entry LOOP
        bne LOOP(K,W)
END:    stop
STR:    .string "abcdef"
LENGTH: .data 6,-9,15
K:      .data 22
.extern L3
```

## 📚 Documentation

The `HTML-docs/` folder contains comprehensive Hebrew documentation including:

- **Project overview and module descriptions** (`screen1.html`, `screen2.html`)
- **Detailed program flow diagrams** (`pixel.html`)
- **Visual architecture explanations**

Open `read-me.html` in your browser to access the documentation portal.

## 🧪 Testing

Example files are provided in the `examples/` directory:

- `goodFile1.as` - Valid assembly program with expected output
- `badFile.as` - Invalid program demonstrating error handling

## 🔧 Technical Details

- **Word Size**: 14 bits
- **Memory**: 256 words (addresses 100-355)
- **Starting Address**: 100
- **Encoding**: Custom base-4 format using `/` and `.` characters
- **Standard**: ANSI C (C89)
- **Compiler Flags**: `-ansi -pedantic -Wall`

## 📄 Project Structure

```
TwoPassAssembler/
├── main.c                  # Entry point
├── firstStage.c            # First pass implementation
├── secondStage.c           # Second pass implementation
├── thirdStage.c            # Output generation
├── operandAnalysis.c       # Instruction parsing
├── symbolList.c            # Symbol table
├── dataList.c             # Data management
├── entryList.c            # Entry labels
├── wordList.c             # Word list
├── validationErrors.c     # Error handling
├── utils.c                # Utilities
├── header.h               # Function declarations
├── structs.h              # Data structures
├── defines.h              # Constants
├── makefile               # Build configuration
├── examples/              # Test files
└── HTML-docs/             # Documentation
```

## 🎓 Educational Context

This project was developed as part of **Maman 14** (Assignment 14) for the Systems Programming Laboratory course, demonstrating:

- Multi-pass compilation techniques
- Symbol table management
- Memory management in C
- Modular software design
- Error handling and validation
- File I/O operations

## 📝 License

This is an academic project developed for educational purposes.

## 🤝 Contributors

- **Roey Yohanan**
- **Adam Gertzkin**

---

_Open University of Israel - Systems Programming Laboratory Course_
