/*
 *   Authors:        Russell White, Will Rosenberger
 *   Date:           Sept. 20th, 2015
 *   Description:    Flex lexical anylizer for the COOL language
 *   Bugs:           Probably lots.
 */

#include "driver.h"

int main(int argc, char** argv) {
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
    // Start the lexer
    int err;
    if((err = perform_lex(in_fname, printLex))) {
      cout << "Failed lex on " << in_fname << endl;
      return err;
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
