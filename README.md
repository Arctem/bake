# bake
Compiler for CSE423.
Cake Whisperers:
  Andrew (AJ) Burns, Melanie Palmer, William Rosenberger, Russell White

## Overview
Bake is currently in the parser stage of our COOL compiler. Utilizing FLEX, it reads in a .cl file and converts it to line seperated tokens. It ignores comments and extra whitespace while reading the file. The conversion is done as per the COOL specification. It then interfaces with BISON to match our grammar from the tokens returned from flex. As it matches the grammar in BISON, it builds the AST for our grammar. The AST can be pretty printed for testing. 

## Features
- Command line arguments for input and lexer output (see How to Compile and Run).
- Tokenizes each official COOL token.
- Matches the grammar off of those tokens
- Builds an AST off the grammar
- Pretty print of our AST

## Bugs
None Known at this time.

## How to Compile and Run
- Run cmake_script.sh in terminal to create the makefile and build the project.
  - To make clean, delete the build directory and rerun the script.
- Go into build/src/
- Run ./bake &lt;input-file&gt;
  - Alternately, you can run specifying the input and output files:
    Run ./bake -i &lt;input-file&gt; to run the compiler
            AND
    Run ./bake -i &lt;input-file&gt; -l &lt;output-file&gt to recieve the lex output
      - "-i &lt;input-file&gt;" denotes the name of the input file to the compiler
      - "-l &lt;output-file&gt;" denotes the name of the output file from the lexer.
      - default output-file name is: "<input-file>-lex-bake"

-- THIS TEST NO LONGER EXISTS, CHECK BACK FOR TESTING SOON! --
- Run unit tests:
  - navigate to the bake/tests folder
    - ./test_lexer.py
  - Note: this script assumes the cool command is in the path.

## How to use COOL Reference Interpreter
- Make sure you have executable permission on the "cool" executable.
  - chmod a+x cool
- Run ./cool [file.cl]
  - Run with "--lex" for the lexer

## Division of Labor
- Andrew Burns:  
  - Researching and implementing CMake for compiling and linking the project. Documentation--readme.
  - AST Stuff : Design, Classes, Pretty Print, CONSTRUCTORS!, etc., CMake
- Melanie Palmer:
  - Researching COOL and writing COOL code for test cases. Helping with FLEX code. Helping with testing script. Helping with Debugging error cases. Documentation--code comments.
  - Refactoring flex, refactoring commandline arguments, BISON : grammar, debugging, integration, etc.
- William Rosenberger:
  - Researching and attempting to use gtest. Writing testing script. Adding file I/O to driver.cpp. Helping with debugging error cases.
  - AST Stuff : Design, Classes, Pretty Print, CONSTRUCTORS!, etc.
- Russell White:
  - Writing FLEX rules for lexing. Helped with CMake. Documention--code comments. Configured CircleCI.
  - Integration of AST & BISON, GTest, CircleCI, CMake
