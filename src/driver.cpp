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

extern int yylineno;
extern int nelements;
extern FILE* yyin;
extern FILE* yyout;

int yylex(void);
void help(char* cmd_name);

int main(int argc, char** argv)
{
  string in_fname; // Name of the input file
  string out_fname; // Name of the output file

  // Get file names
  char c;
  while((c = getopt(argc, argv, "i:o:")) != -1) {
    switch(c) {
    case 'i': // Input file
      in_fname = string(optarg);
      break;
    case 'o': // Output file
      out_fname = string(optarg);
      break;
    case '?':
      help(argv[0]);
      exit(-1);
      break;
    }
  }

  if(in_fname.empty()) {
    cout << "Must specify input file" << endl;
    help(argv[0]);
    exit(-1);
  }

  if(out_fname.empty()) {
    out_fname = in_fname + "-lex-bake";
  }

  // Open files
  yyin = fopen(in_fname.c_str(), "r");
  yyout = fopen(out_fname.c_str(), "w");
  if(!yyin or !yyout) {
    cout << "Error opening files" << endl;
  }

  yylex();

  fclose(yyin);
  fclose(yyout);
}

void help(char* cmd_name) {
  cout << "Usage: " << cmd_name << " -i input_file -o output_file\n";
  cout << "  input_file: File to scan" << endl;
  cout << "  output_file: File in which to place the output. Defaults to <input_file>-lex-bake" << endl;
}
