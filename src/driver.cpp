/*
 *   Authors:        Russell White, Will Rosenberger
 *   Date:           Sept. 20th, 2015
 *   Description:    Flex lexical anylizer for the COOL language
 *   Bugs:           Probably lots.
 */

#include <iostream>
#include <string>
using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "ast/ast.h"
using namespace bake_ast;
#include "typecheck/symbol_node.h"
#include "typecheck/build_st.h"
#include "typecheck/symbol_table_print.h"
#include "typecheck/visitor_tc.h"
using namespace typecheck;

extern int yylineno;
extern int nelements;
extern FILE* yyin;
extern FILE* yyout;
extern bool printLex;
ClassList* ast;

int yylex(void);
int yyparse(void);
void help(char* cmd_name);
void yylex_destroy(void);

int main(int argc, char** argv)
{
  vector<string> in_files; // Names of the input files
  string exe_fname; // Name of the output executable
  bool run_lex_only = false;


  // Check whether only an input file (without the -i option) was given
  if(argc == 2) {
    in_files.push_back(string(argv[1]));
  } else {
    // Get file names
    char c;
    while((c = getopt(argc, argv, "i:l:")) != -1) {
      switch(c) {
      case 'i': // Input file
	in_files.push_back(string(optarg));
        break;
      case 'l' :
        printLex = true;
        exe_fname = string(optarg);
        break;
      case '?':
        help(argv[0]);
        exit(-1);
        break;
      }
    }
  }

  // Fail if no input is given
  if(in_files.empty()) {
    cout << "Must specify at least one input file" << endl;
    help(argv[0]);
    return -1;
  }

  // We need to parse every file separately. ASTs will
  // combine as we go.
  for(auto in_fname : in_files) {
    string out_fname;
    if(printLex) {
      out_fname = in_fname + "-lex-bake";

      yyout = fopen(out_fname.c_str(), "w");
      if(!yyout) {
	cout << "Error opening file: " << out_fname << endl;
      }

    }

    // Open input file
    yyin = fopen(in_fname.c_str(), "r");

    if(!yyin) {
      cout << "Error opening file: " << in_fname << endl;
    }

    // Start the lexer
    yyparse();

    // Close file handlers
    fclose(yyin);

    if(printLex){
      fclose(yyout);
    }

  }

  PrettyPrint pp;
  ast->accept(&pp);

  cout << endl << "################" << endl << endl;

  BuildST build;
  try {
    ast->accept(&build);
  } catch (StBuildErr& e) {
    cout << e.what() << endl;
    return 0;
  }

  SymbolTablePrint spt;
  build.getCurrScope()->accept(&spt);

  cout << endl << "################" << endl << endl;

  TypeCheck tc;
  try {
    ast->accept(&tc);
    ast->accept(&pp);
  } catch (TypeErr& e) {
    cout << e.what() << endl;
    return 0;
  }


  // Frees memory
  yylex_destroy();

  delete ast;

  return 0;
}


/* Function prints the help message */
void help(char* cmd_name) {
  cout << "Usage: " << endl;
  cout << "\t" << cmd_name << " input_file" << endl;
  cout << "\t" << cmd_name << " -i input_file -l output_file" << endl;
  cout << "input_file: File to scan" << endl;
  cout << "output_file: File in which to place the output. Defaults to <input_file>-lex-bake" << endl;
}
