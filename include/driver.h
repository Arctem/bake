#pragma once

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
#include "typecheck/check_scope.h"
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
int perform_lex(string in_fname, bool print_lex);

ClassStatement* buildObject();
ClassStatement* buildIO();
ClassStatement* buildString();
ClassStatement* buildInt();
ClassStatement* buildInt8();
ClassStatement* buildInt64();
ClassStatement* buildBool();
ClassStatement* buildFloat();

