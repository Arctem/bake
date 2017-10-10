# Bake
Compiler for CSE423.
Cake Whisperers:
  Andrew (A to the J) Burns, Melanie Burns (Palmer), William Rosenberger, Russell White

## Overview
Bake currently has the following three parts of compilation implemented: 
* Lexical analysis
* Parsing
* Type checking

#### Lexical analysis
Utilizing FLEX, Bake reads in a .cl file and converts it to line seperated tokens. It ignores comments and extra whitespace while reading the file. The conversion is done as per the COOL specification.

#### Parsing
After lexical analysis, Bake interfaces with BISON to match our grammar from the tokens returned from flex. As it matches the grammar in BISON, it builds the AST for our grammar. The AST can be pretty printed for testing.

#### Type checking
The first step in checking for type validity is to build a symbol table for each scope. Each of these scope tables are stored in a tree structure, allowing Bake to easily determine whether a requested feature is visible in the current scope. We call this tree of scope tables the scope tree. There are four types of nodes in the scope tree:
* Groot 
  * Global Root. See also: A magnificent tree that guards the galaxy
  * Child scopes can only be Class scopes.
  * Contains a map from the name of the child scope to the scope object for that class
* Class
  * Contains the attributes and methods for a class
  * Attributes are contained in a map from the attribute name to the name of the type of that attribute
  * Methods are contained in a map from the name of the method to the scope object for that method
* Method
  * The only additions method makes to the current scope are the parameters it takes in.
  * Parameters are stored in a map from the name of the parameter to the name of the type of the parameter
  * Methods may also contain Let scopes, which are anonymous. Lets are stored in a simple vector.
* Let statement
  * Let statements define additional variables. These are, again, contained in a map from name to type.

## Features
- Command line arguments for input and lexer output (see How to Compile and Run).
- Tokenizes each official COOL token.
- Matches the grammar off of those tokens
- Builds an AST off the grammar
- Pretty print of our AST
- Builds a scope table off the AST
- Pretty prints the scope table
- Verifies the types of the AST off of the scope table

## Bugs
- Automated testing is sorta kinda working. You can run it with either `make test` or
  `bin/lextest` for more detailed output. Unfortunately that's only for testing the
  flex/bison stuff. Other stuff you'll have to run yourself. Just do
  `./bake src/typecheck/tests/<test-file>` and you'll see it do its thing. Exciting!

## How to Compile and Run
- Run `make`. To build tests, run `make test`.
- Run `./bake <input-file>`
- To specify multiple files, run `./bake -i <file1> -i <file2> -i <file3>`. An
  arbitrary number of files are accepted.

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
