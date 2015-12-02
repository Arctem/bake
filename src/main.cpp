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
        return -1;
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

  add_builtins();

  // Prints the AST
  PrettyPrint pp;
  ast->accept(&pp);

  //  Builds the scope table
  BuildST build;
  try {
    ast->accept(&build);
  } catch (StBuildErr& e) {
    cout << e.what() << endl;
    return 0;
  }

  CheckScope cs;
  try {
    build.getCurrScope()->accept(&cs);
  } catch (ScopeCheckErr& e) {
    cout << e.what() << endl;
    return 0;
  }

  // Runs the type checker  
  TypeCheck tc(build.getCurrScope());

  try {
    ast->accept(&tc);
  } catch (TypeErr& e) {
    cout << e.what() << endl;
    return 0;
  }

  // Build the IR
  ir::BuildIR bir(ast);

  cout << endl << "################" << endl << endl;

  // Prints the symbol tree
  SymbolTablePrint spt;
  build.getCurrScope()->accept(&spt);

  cout << endl << "################" << endl << endl;

  // Prints the IR
  ir::IrPrint irp;
  irp.visit(bir.getClassList());

  delete ast;

  return 0;
}
