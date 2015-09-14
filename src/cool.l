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
%x CLASS_END
%x INHERITANCE_TYPE
%x INHERITANCE_END
%x FEATURES
%x FEATURE_TYPE
%x FEATURE_END
%x METHOD
%x METHOD_TYPE
%x METHOD_MID
%x METHOD_PRE_EXPRESSION
%x METHOD_POST_EXPRESSION
%x ATTRIBUTE
%x ATTRIBUTE_MID
%x ATTRIBUTE_EXPR
%x FORMAL_START
%x FORMAL_MID
%x FORMAL_END

%x EXPRESSION

%x LBRACE
%x RBRACE
%x COLON
%x SEMICOLON

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
  \{           { printline(); out("lbrace"); BEGIN(FEATURES); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<FEATURES>{
  {IDENTIFIER} { printline(); out("identifier"); out(yytext); BEGIN(FEATURE_TYPE); }

  \}           { printline(); out("rbrace"); BEGIN(CLASS_END); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<FEATURE_TYPE>{
  \(           { printline(); out("lparen"); yy_push_state(FORMAL_START); }

  :            { printline(); out("colon"); BEGIN(ATTRIBUTE); }

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<FEATURE_END>{
  ;            { printline(); out("semi"); BEGIN(FEATURES); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<CLASS_END>{
  ;            { printline(); out("semi"); BEGIN(INITIAL); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<ATTRIBUTE>{
  {TYPE}       { printline(); out(yytext); BEGIN(ATTRIBUTE_MID); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<ATTRIBUTE_MID>{
  \<-          {
                 printline();
		 out("larrow");
		 BEGIN(ATTRIBUTE_EXPR);
               }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { yyless(0); BEGIN(FEATURE_END); }
}
<ATTRIBUTE_EXPR>{
  %{ yy_push_state(EXPRESSION); %}

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { yyless(0); BEGIN(FEATURE_END); }
}
<METHOD>{
  ,            { printline(); out("comma"); yy_push_state(FORMAL_START); }

  \)           { printline(); out("rparen"); BEGIN(METHOD_MID); }

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<METHOD_MID>{
  :            { printline(); out("colon"); BEGIN(METHOD_TYPE); }

  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<METHOD_TYPE>{
  {TYPE}       { printline(); out("type"); out(yytext); BEGIN(METHOD_PRE_EXPRESSION); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<METHOD_PRE_EXPRESSION>{
  \{           { printline(); out("lbrace"); BEGIN(METHOD_POST_EXPRESSION); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<METHOD_POST_EXPRESSION>{
  %{ yy_push_state(EXPRESSION); %}
  
  \}           { printline(); out("rbrace"); BEGIN(FEATURE_END); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<FORMAL_START>{
  {IDENTIFIER} { printline(); out("identifier"); out(yytext); BEGIN(FORMAL_MID); }

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { yyless(0); yy_pop_state(); }
}
<FORMAL_MID>{
  :            { printline(); out("colon"); BEGIN(FORMAL_END); }
  
  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}
<FORMAL_END>{
  {TYPE}       { printline(); out("type"); out(yytext); BEGIN(METHOD); }

  [ \t\n\r]*   { /* consume the whitespace */ }
  
  .       { out(yytext); exit(0); }
}


<EXPRESSION>{

}
%%
