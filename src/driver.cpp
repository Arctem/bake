/*
 *   Authors:        Russell White, Will Rosenberger
 *   Date:           Sept. 20th, 2015
 *   Description:    Flex lexical analyzer for the COOL language
 *   Bugs:           Probably lots.
 */

#include <iostream>
#include <string>
#include <vector>

#include "ast/ast.h"

#include "typecheck/symbol_node.h"
#include "typecheck/build_st.h"
#include "typecheck/symbol_table_print.h"
#include "typecheck/visitor_tc.h"

#include "lean/optionparser.h"

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

static option::ArgStatus RequireString(const option::Option& opt, bool msg);

enum optionIndex { UNKNOWN, HELP, INPUT };
const option::Descriptor usage[] =
  {
    {UNKNOWN, 0,  "",      "", option::Arg::None, "USAGE: bake [options]\n\n" "Options:" },
    {HELP,    0, "h",  "help", option::Arg::None, "  --help, -h  \tPrint usage and exit." },
    {INPUT,   0, "i", "input",     RequireString, "  --input, -i \tSpecify input file." },
    {UNKNOWN, 0,  "",      "", option::Arg::None, "\nExamples:\n"
     "  ./bake src/flex/test/parser_tests/valid-hello.cl\n" },

    {0,0,0,0,0,0}
  };


int main(int argc, char** argv)
{
  vector<string> in_files; // Names of the input files
  string exe_fname; // Name of the output executable
  bool run_lex_only = false;

  // skip program name argv[0] if present
  argc -= (argc > 0);
  argv += (argc > 0);
  option::Stats stats(usage, argc, argv);
  option::Option *options = new option::Option[stats.options_max],
    *buffer = new option::Option[stats.buffer_max];
  option::Parser parse(usage, argc, argv, options, buffer);

  if(parse.error())
    return 1;

  if(options[HELP] || argc == 0) {
    option::printUsage(std::cout, usage);
    return 0;
  }

  if(options[INPUT]) {
    in_fname = options[INPUT].last()->arg;
    std::cout << "File: " << in_fname << std::endl;
  } else if(argc == 2) {

  }

  for (option::Option* opt = options[UNKNOWN]; opt; opt = opt->next())
    std::cout << "Unknown option: " << opt->name << "\n";

  for (int i = 0; i < parse.nonOptionsCount(); ++i)
    std::cout << "Non-option #" << i << ": " << parse.nonOption(i) << "\n";

  /*
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
  */

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

static option::ArgStatus RequireString(const option::Option& opt, bool msg) {
  if(!opt.arg) {
    std::cout << "Error: Argument required by " << opt.name << std::endl;
    return option::ARG_ILLEGAL;
  }
  return option::ARG_OK;
}

/* Function prints the help message */
void help(char* cmd_name) {
  std::cout << "Usage: " << std::endl;
  std::cout << "\t" << cmd_name << " input_file" << std::endl;
  std::cout << "\t" << cmd_name << " -i input_file -l output_file" << std::endl;
  std::cout << "input_file: File to scan" << std::endl;
  std::cout << "output_file: File in which to place the output. Defaults to <input_file>-lex-bake" << std::endl;
}
