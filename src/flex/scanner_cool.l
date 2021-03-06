%{
  /*
  *   Authors:        Russel White, Melanie Palmer, Will Roosenberger
  *   Date:           Sept. 20th, 2015
  *   Description:    Flex lexical anylizer for the COOL language
  *   Bugs:           None known
  */
#include <list>
#include <cstdio>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stack>
#include <stdarg.h>

#include "ast/ast.h"
#include "parser_cool.hpp"

// define line below as 1 to get debugging
#define SCANNER_DEBUG 0

#define yyterminate() return YY_NULL

extern int yycol;
bool printLex = false;

using namespace std;

 /* Functions used for ease of printing */
void out(const char *output);
void printline();

void out(const char *output) {
  if(printLex == true){
    fprintf(yyout, "%s\n", output);
  }
}

void printline() {
  fprintf(yyout, "%d\n", yylineno);
}

void errorOut(const char* message) {
  fprintf(stderr, "Error: %d: Lexer: %s\n", yylineno, message);
}

void outputLex(const char* message){
   if(printLex == true){
      printline();
      out(message);
   }

   if(SCANNER_DEBUG == 1){
      printf("Debug: %d: Lexed: %s\n", yylineno,message);
   }
}

void adjust(void){
  for(int i=0; yytext[i] != '\0'; i++)
  {
    if (yytext[i] == '\n'){yycol = 0;}
    else {yycol++;}
  }
}


%}

/* Flex options used throughout */
%option yylineno
%option noyywrap
%option stack

/* Chars allowable in element and attribute names */
IDENTIFIER  [a-z][a-zA-Z0-9_]*
TYPE        [A-Z][a-zA-Z0-9_]*
INTEGER     [0-9]+
FLOAT       [0-9]*\.[0-9]+
STRING      \"([^\n\Z\"])*\"

/* Start conditions */
%x COMMENT
%x BLOCK_COMMENT

%%
  /* -----------------  RULES --------------- */
  /* ---------------- KEYWORDS -------------- */
class        { outputLex("class");    adjust(); return CLASS;}
inherits     { outputLex("inherits"); adjust(); return INHERIT; }
case         { outputLex("case");     adjust(); return CASES;}
esac         { outputLex("esac");     adjust(); return ESAC;}
if           { outputLex("if");       adjust(); return IF;}
then         { outputLex("then");     adjust(); return THEN;}
else         { outputLex("else");     adjust(); return ELSE;}
fi           { outputLex("fi");       adjust(); return FI;}
in           { outputLex("in");       adjust(); return IN;}
let          { outputLex("let");      adjust(); return LET;}
isvoid       { outputLex("isvoid");   adjust(); return ISVOID;}
new          { outputLex("new");      adjust(); return NEW;}
not          { outputLex("not");      adjust(); return NOT;}
of           { outputLex("of");       adjust(); return OF;}
while        { outputLex("while");    adjust(); return WHILE;}
loop         { outputLex("loop");     adjust(); return LOOP;}
pool         { outputLex("pool");     adjust(); return POOL;}


  /* --------------- BOOL Keywords ----------- */
f[a|A][l|L][s|S][e|E]        {
                                outputLex("false");
                                adjust();
                                yylval.boolean = false;
                                return FALSE;
                             }
t[r|R][u|U][e|E]             {
                                outputLex("true");
                                adjust();
                                yylval.boolean = true;
                                return TRUE;
                              }


  /* ----- Integers, Identifiers, Types ------ */
{TYPE}       {
                adjust();
                outputLex("type");
                out(yytext);

                if(not strcmp(yytext, "Int32")) {
                  yylval.valueString = new std::string("Int");
                } else {
                  yylval.valueString = new std::string(yytext);
                }

                return TYPE;
              }
{IDENTIFIER} {
                outputLex("identifier");
                out(yytext);
                adjust();
                yylval.valueString = new std::string(yytext);
                return IDENTIFIER;
              }


{FLOAT} {

             adjust();
             double num = atof(yytext);

             if(num < 0 ){
               errorOut("Float is not unsigned. Invalid for COOL. ");
               return YY_NULL;
             }
             outputLex("float");
             out(yytext);
             yylval.valueFloat = atof(yytext);
             return FLOAT;
         }

{INTEGER}    {
                adjust();
                long long num = atoll(yytext);

                if(num < 0 ){
                  errorOut("Integer is not unsigned. Invalid for COOL. ");
                  return YY_NULL;
                } else if(num <= 2147483647) {
                  outputLex("int 32");
                  out(yytext);
                  yylval.valueInt32 = atoi(yytext);
                  return INTEGER;

                }

                errorOut("Integer outside value range over a 8, 32, or 64 bit integer");
                return YY_NULL;
             }




  /* --------------- Punctuation ------------ */
\@           { outputLex("at");     adjust(); return '@';}
:            { outputLex("colon");  adjust(); return ':';}
,            { outputLex("comma");  adjust(); return ',';}
\/           { outputLex("divide"); adjust(); return '/';}
\.           { outputLex("dot");    adjust(); return '.';}
\{           { outputLex("lbrace"); adjust(); return '{';}
\(           { outputLex("lparen"); adjust(); return '(';}
-\>          { outputLex("rarrow"); adjust(); return RARROW;}
\}           { outputLex("rbrace"); adjust(); return '}';}
\)           { outputLex("rparen"); adjust(); return ')';}
;            { outputLex("semi"); adjust(); return ';';}

  /* ------ Assignments & Comparisions ------ */
\<-          { outputLex("larrow"); adjust(); return LARROW; }
=            { outputLex("equals"); adjust(); return '='; }
\<=          { outputLex("le");     adjust(); return LEQUAL;}
=\>          { outputLex("re");     adjust(); return GOES_TO;}
\<           { outputLex("lt");     adjust(); return '<';}

  /* -------------- Arthimetic ------------- */
-            { outputLex("minus"); adjust(); return '-';}
\+           { outputLex("plus");  adjust(); return '+';}
\~           { outputLex("tilde"); adjust(); return '~';}
\*           { outputLex("times"); adjust(); return '*';}

  /* -------------- Strings --------------- */
{STRING}     {
                adjust();
                yytext[yyleng - 1] = '\0';
                outputLex("string");
                out(yytext + 1);
                yylval.valueString = new std::string(yytext + 1);
                return STRING;
             }

  /* -------------- Comments -------------- */
\(\*         { adjust(); yy_push_state(BLOCK_COMMENT); }
--           { adjust(); yy_push_state(COMMENT); }

  /* ------- Consumes Whitespace  -------- */
[ \t\n\r]*   { adjust(); }

 /* --  Anything is an Invalid Character -- */
.            {
                errorOut((string("invalid character: ") + yytext).c_str());
                yyterminate();
              }

 /* ----------- OTHER BLOCKS ------------ */
 /* ------- Single Line Comment --------- */
<COMMENT>{
    \n            { adjust(); yy_pop_state(); }
    [ \t\r]*    { adjust(); /* consume the whitespace */ }
    .          { adjust(); }
 }

 /* ------- Single Line Comment --------- */
<BLOCK_COMMENT>{
  /* Ignore everything in comments, but allow nexting comments because we cool. */
  \(\*         { adjust(); yy_push_state(BLOCK_COMMENT); }
  \*\)         { adjust(); yy_pop_state(); }
  [ \t\n\r]*   { adjust(); /* consume the whitespace */ }

  <<EOF>>      {
                  adjust();
                  errorOut("<<EOF>> found before end of comment");
                  yyterminate();
               }

  .             { adjust(); /* anything is allowed in comments */ }
}
%%
