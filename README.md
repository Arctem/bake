# bake
Compiler for CSE423.
Cake Whisperers:
  Andrew (AJ) Burns, Melanie Palmer, William Rosenberger, Russell White

## Overview
Bake is currently in the lexical analyzer stage of our COOL compiler. Utilizing FLEX, it reads in a .cl file and converts it to line seperated tokens. It ignores comments and extra whitespace while reading the file. The conversion is done as per the COOL specification.

## Features
- Command line arguments for input and output (see How to Compile and Run).
- Tokenizes each official COOL token.
- Testing script to automatically perform unit test.
 - Runs and checks output of all our test cases

## Bugs
None Known at this time.

## How to Compile and Run
- Run cmake_script.sh in terminal to create the makefile and build the project.
  - To make clean, delete the build directory and rerun the script.
- Go into build/src/
- Run ./bake &lt;input-file&gt;
  - Alternately, you can run specifying the input and output files:
    Run ./bake -i &lt;input-file&gt; -o &lt;output-file&gt;
      - "-i &lt;input-file&gt;" denotes the name of the input file to the lexer
      - "-o &lt;output-file&gt;" denotes the name of the output file from the lexer.
      - default output-file name is: "<input-file>-lex-bake"
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
Andrew Burns: Researching and implementing CMake for compiling and linking the project. Documentation--readme.
Melanie Palmer: Researching COOL and writing COOL code for test cases. Helping with FLEX code. Helping with testing script. Helping with Debugging error cases. Documentation--code comments.
William Rosenberger: Researching and attempting to use gtest. Writing testing script. Adding file I/O to driver.cpp. Helping with debugging error cases.
Russell White: Writing FLEX rules for lexing. Helped with CMake. Documention--code comments. Configured CircleCI.
