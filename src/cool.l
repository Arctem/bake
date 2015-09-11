%{

#include <list>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <iostream>

// If you want to disable DEBUGGING, comment out the next line
// and uncomment the one after.
#define DEBUG(...) fprintf (stdout, __VA_ARGS__)
//#define DEBUG(...)


using namespace std;


// Put here any variables that you may need in the actions.

void out(const char *output);
void printline();

void out(const char *output) {
  std::cout << output << std::endl;
}

void printline() {
  std::cout << yylineno << std::endl;
}



%}

%option yylineno
%option noyywrap
%option stack

/* Chars allowable in element and attribute names */
IDENTIFIER  [a-z][a-zA-Z0-9:._]*
TYPE        [A-Z][a-zA-Z0-9:._]*

/* Start conditions */
%x CLASS_START
%x CLASS_INHERITANCE
%x INHERITANCE_TYPE
%x INHERITANCE_END
%x FEATURE
%x FEATURE_TYPE
%x METHOD
%x ATTRIBUTE
%x FORMAL

%%
  /* -----------------  RULES ----------------*/

class   { printline(); out("class"); BEGIN(CLASS_START); }

[ \t\n\r]*   { /* consume the whitespace */ }

.       { out(yytext); exit(0); }

<CLASS_START>{
  {TYPE}       { printline(); out("type"); out(yytext); BEGIN(CLASS_INHERITANCE); }

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out("Expected class definition."); exit(0); }
}

<CLASS_INHERITANCE>{
  inherits     { printline(); out("inherits"); BEGIN(INHERITANCE_TYPE); }

  [ \t\n\r]*   { /* consume the whitespace */ }

  .       { yyless(0); BEGIN(INHERITANCE_END); }
}
<INHERITANCE_TYPE>{
  {TYPE}       { printline(); out("type"); out(yytext); BEGIN(INHERITANCE_END); }

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<INHERITANCE_END>{
  \{           { printline(); out("lbrace"); BEGIN(FEATURE); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<FEATURE>{
  {IDENTIFIER} { printline(); out("identifier"); out(yytext); BEGIN(FEATURE_TYPE); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<FEATURE_TYPE>{
  \(           { printline(); out("lparen"); BEGIN(METHOD); }

  :            { printline(); out("colon"); BEGIN(ATTRIBUTE); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<ATTRIBUTE>{
  
}
<METHOD>{
  {IDENTIFIER}//TODO RESUME HERE HI HOW ARE YOU FUTURE ME

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<METHOD_MORE>{

}
<FORMAL_START>{
  {IDENTIFIER} { printline(); out("identifier"); out(yytext); BEGIN(FORMAL_MID); }

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { yyless(0); BEGIN(yy_pop_state()); }
}
<FORMAL_MID>{
  :            { printline(); out("colon"); BEGIN(FORMAL_END); }

  [ \t\n\r]*   { /* consume the whitespace */ }

  .       { out(yytext); exit(0); }
}
<FORMAL_END>{
  {TYPE}       { printline(); out("type"); out(yytext); BEGIN(yy_pop_state()); }

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
%%
