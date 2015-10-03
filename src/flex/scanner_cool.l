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
#include "parser_cool.h"

// define line below as 1 to get debugging
#define  SCANNER_DEBUG 0

extern int yycol;
bool printLex;

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
      printf("Debug: %d: Lexed: %s", yylineno,message);
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
IDENTIFIER  [a-z][a-zA-Z0-9._]*
TYPE        [A-Z][a-zA-Z0-9._]*
INTEGER     [0-9]+
STRING      \"([^\n\Z\"])*\"

/* Start conditions */
%x COMMENT
%x BLOCK_COMMENT

%%
  /* -----------------  RULES --------------- */
  /* ---------------- KEYWORDS -------------- */
class        { outputLex("class");    adjust(); return CLASS;}
inherits     { outputLex("inherits"); adjust(); return INHERIT; }
case         { outputLex("case");     adjust(); return CASE;}
esac         { outputLex("esac");     adjust(); return ESAC;}
if           { outputLex("if");       adjust(); return IF;}
then         { outputLex("then");     adjust(); return THEN;}
else         { outputLex("else");     adjust(); return ELSE;}
fi           { outputLex("fi");       adjust(); return FI;}
in           { outputLex("in");       adjust(); return IN;}
let          { outputLex("let");      adjust(); return LET;}
isvoid       { outputLex("isvoid");   adjust(); return yytokentype::ISVOID;}
new          { outputLex("new");      adjust(); return yytokentype::NEW;}
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
                yylval.valueString = yytext;
                return yytokentype::TYPE;
              }
{IDENTIFIER} {
                outputLex("identifier");
                out(yytext);
                adjust();
                yylval.valueString = yytext;
                return IDENTIFIER;
              }

{INTEGER}    {
                adjust();
                int num = atoi(yytext);
                if(num < -2147483647 || num > 2147483647) {
                  errorOut("Integer outside value range");
                  exit(-1);
                } else {
                  outputLex("integer");
                  out(yytext);
                }
                yylval.valueInt = atoi(yytext);
                return INTEGER;
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
                yylval.valueString = yytext + 1;
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
                exit(-1);
              }

 /* ----------- OTHER BLOCKS ------------ */
 /* ------- Single Line Comment --------- */
<COMMENT>{
    \n            { adjust(); yy_pop_state(); }
    [ \t\n\r]*    { adjust(); /* consume the whitespace */ }
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
                  exit(-1);
               }

  .             { adjust(); /* anything is allowed in comments */ }
}
%%
