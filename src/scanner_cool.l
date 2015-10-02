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
#include "parser_cool.h"

extern int yycol;
bool printLex;

using namespace std;

 /* Functions used for ease of printing */
void out(const char *output);
void printline();

void out(const char *output) {
  fprintf(yyout, "%s\n", output);
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
IDENTIFIER  [a-z][a-zA-Z0-9:._]*
TYPE        [A-Z][a-zA-Z0-9:._]*
INTEGER     [0-9]+
STRING      \"([^\n\Z\"])*\"

/* Start conditions */
%x COMMENT
%x BLOCK_COMMENT

%%
  /* -----------------  RULES --------------- */
  /* ---------------- KEYWORDS -------------- */
class        { outputLex("class"); adjust(); return CLASS;}
inherits     { outputLex("inherits"); return INHERIT; }
case         { outputLex("case"); return CASE;}
esac         { outputLex("esac"); return ESAC;}
if           { outputLex("if"); return IF;}
then         { outputLex("then"); return THEN;}
else         { outputLex("else"); return ELSE;}
fi           { outputLex("fi"); return FI;}
in           { outputLex("in"); return IN;}
let          { outputLex("let"); return LET;}
isvoid       { outputLex("isvoid"); return ISVOID;}
new          { outputLex("new"); return NEW;}
not          { outputLex("not"); return NOT;}
of           { outputLex("of"); return OF;}
while        { outputLex("while"); return WHILE;}
loop         { outputLex("loop"); return LOOP;}
pool         { outputLex("pool"); return POOL;}


  /* --------------- BOOL Keywords ----------- */
f[a|A][l|L][s|S][e|E]        { outputLex("false"); return FALSE;}
t[r|R][u|U][e|E]             { outputLex("true"); return TRUE;}


  /* ----- Integers, Identifiers, Types ------ */
{TYPE}       { adjust(); outputLex("type"); return TYPE;}
{IDENTIFIER} { outputLex("identifier"); out(yytext); return IDENTIFIER;}
{INTEGER}    {
                int num = atoi(yytext);
                if(num < -2147483647 || num > 2147483647) {
                  errorOut("Integer outside value range");
                  exit(-1);
                } else {
                  printline();
                  out("integer");
                  out(yytext);
                }
                return INTEGER;
             }


  /* --------------- Punctuation ------------ */
\@           { outputLex("at"); return '@';}
:            { outputLex("colon"); return ':';}
,            { outputLex("comma"); return ',';}
\/            { outputLex("divide"); return '/';}
\.           { outputLex("dot"); return '.';}
\{           { outputLex("lbrace"); return '{';}
\(           { outputLex("lparen"); return '(';}
-\>          { outputLex("rarrow"); return RARROW;}
\}           { outputLex("rbrace"); return '}';}
\)           { outputLex("rparen"); return ')';}
;            { outputLex("semi"); return ';';}

  /* ------ Assignments & Comparisions ------ */
\<-          { outputLex("larrow"); return LARROW; }
=            { outputLex("equals"); return '='; }
\<=          { outputLex("le"); return LEQUAL;}
=\>          { outputLex("re"); return GOES_TO;}
\<           { outputLex("lt"); return '<';}

  /* -------------- Arthimetic ------------- */
-            { outputLex("minus"); return '-';}
\+           { outputLex("plus"); return '+';}
\~           { outputLex("tilde"); return '~';}
\*           { outputLex("times"); return '*';}

  /* -------------- Strings --------------- */
{STRING}     {
                outputLex("string");
                yytext[yyleng - 1] = '\0';
                out(yytext + 1);
                return STRING;
             }

  /* -------------- Comments -------------- */
\(\*         { yy_push_state(BLOCK_COMMENT); }
--           { yy_push_state(COMMENT); }

  /* ------- Consumes Whitespace  -------- */
[ \t\n\r]*   { }

 /* --  Anything is an Invalid Character -- */
.            {
                errorOut((string("invalid character: ") + yytext).c_str());
                out(yytext);
                exit(-1);
              }

 /* ----------- OTHER BLOCKS ------------ */
 /* ------- Single Line Comment --------- */
<COMMENT>{
    \n            { yy_pop_state(); }
    [ \t\n\r]*    { /* consume the whitespace */ }
    .          {  }
 }

 /* ------- Single Line Comment --------- */
<BLOCK_COMMENT>{
  /* Ignore everything in comments, but allow nexting comments because we cool. */
  \(\*         { yy_push_state(BLOCK_COMMENT); }
  \*\)         { yy_pop_state(); }
  [ \t\n\r]*   { /* consume the whitespace */ }

  <<EOF>>      {
                  errorOut("<<EOF>> found before end of comment");
                  exit(-1);
               }

  .             { /* anything is allowed in comments */ }
}
%%
