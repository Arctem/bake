/*
*   Authors:        Russel White, Will Roosenberger
*   Date:           Sept. 20th, 2015
*   Description:    Flex lexical anylizer for the COOL language
*   Bugs:           None known
*/

#include <iostream>
#include <string>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "ast.h"
// using namespace bake_ast;

extern int yylineno;
extern int nelements;
extern FILE* yyin;
extern FILE* yyout;
extern bool printLex;

int yylex(void);
int yyparse(void);
void help(char* cmd_name);
void yylex_destroy(void);

int main(int argc, char** argv)
{
  string in_fname; // Name of the input file
  string out_fname; // Name of the output file
  bool run_lex_only;


  // Check whether only an input file (without the -i option) was given
  if(argc == 2) {
    in_fname = string(argv[1]);
  } else {
    // Get file names
    char c;
    while((c = getopt(argc, argv, "i:l:p")) != -1) {
      switch(c) {
      case 'i': // Input file
        in_fname = string(optarg);
        break;
      case 'l': // output only lex
        out_fname = string(optarg);
        printLex = true;
        run_lex_only = true;
        break;
      case 'p' :
        printLex = true;
        break;
      case '?':
        help(argv[0]);
        exit(-1);
        break;
      }
    }
  }

  // Fail if in is empty
  if(in_fname.empty()) {
    cout << "Must specify input file" << endl;
    help(argv[0]);
    return -1;
  }

  if(printLex == true) {
    // Fail if out is empty
    if(out_fname.empty()) {
      out_fname = in_fname + "-lex-bake";
    }

    yyout = fopen(out_fname.c_str(), "w");
    if(!yyout) {
      cout << "Error opening files" << endl;
    }

  }

  // Open Files
  yyin = fopen(in_fname.c_str(), "r");

  if(!yyin) {
    cout << "Error opening files" << endl;
  }

  if(run_lex_only == true){
    // Start the lexer
    yylex();

    // Close file handlers
    fclose(yyin);
    fclose(yyout);

    yylex_destroy();
    return 0;
  }

  // Start the lexer
  yyparse();

  // Close file handlers
  fclose(yyin);

  if(printLex){
    fclose(yyout);
  }

  // Frees memory

  return 0;
}


/* Function prints the help message */
void help(char* cmd_name) {
  cout << "Usage: " << endl;
  cout << "\t" << cmd_name << " input_file" << endl;
  cout << "\t" << cmd_name << " -i input_file -l output_file" << endl;
  cout << "\t" << cmd_name << " -i input_file -y output_file" << endl;
  cout << "-y: Prints the lexer files" << endl;
  cout << "input_file: File to scan" << endl;
  cout << "output_file: File in which to place the output. Defaults to <input_file>-lex-bake" << endl;
}
