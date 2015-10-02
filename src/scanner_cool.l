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
// If you want to disable DEBUGGING, comment out the next line
// and uncomment the one after.
#define DEBUG(...) fprintf (stdout, __VA_ARGS__)
//#define DEBUG(...)

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

#ifndef SCANDEBUG
  #define SCANDEBUG 0
#endif

void printdebug(const char *fmt, ...)
{
  char text[1024];
  if (SCANDEBUG)
  {
    if (fmt)
    {
      va_list arg;
      va_start(arg,fmt);
        vsprintf(text,fmt,arg);
      va_end(arg);
        printf("%s",text);
    }
  }
}

void adjust(void)
{
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
class        { printline(); out("class");
                adjust(); printdebug("class"); return CLASS;}
inherits     { printline(); out("inherits"); return INHERIT; }
case         { printline(); out("case"); return CASE;}
esac         { printline(); out("esac"); return ESAC;}
if           { printline(); out("if"); return IF;}
then         { printline(); out("then"); return THEN;}
else         { printline(); out("else"); return ELSE;}
fi           { printline(); out("fi"); return FI;}
in           { printline(); out("in"); return IN;}
let          { printline(); out("let"); return LET;}
isvoid       { printline(); out("isvoid"); return ISVOID;}
new          { printline(); out("new"); return NEW;}
not          { printline(); out("not"); return NOT;}
of           { printline(); out("of"); return OF;}
while        { printline(); out("while"); return WHILE;}
loop         { printline(); out("loop"); return LOOP;}
pool         { printline(); out("pool"); return POOL;}


  /* --------------- BOOL Keywords ----------- */
f[a|A][l|L][s|S][e|E]        { printline(); out("false"); return FALSE;}
t[r|R][u|U][e|E]             { printline(); out("true"); return TRUE;}


  /* ----- Integers, Identifiers, Types ------ */
{TYPE}       { adjust(); printdebug("Scanner_Type\n"); return TYPE;}
{IDENTIFIER} { printline(); out("identifier"); out(yytext); return IDENTIFIER;}
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
\@           { printline(); out("at"); return '@';}
:            { printline(); out("colon"); return ':';}
,            { printline(); out("comma"); return ',';}
\/            { printline(); out("divide"); return '/';}
\.           { printline(); out("dot"); return '.';}
\{           { printline(); out("lbrace"); return '{';}
\(           { printline(); out("lparen"); return '(';}
-\>          { printline(); out("rarrow"); return RARROW;}
\}           { printline(); out("rbrace"); return '}';}
\)           { printline(); out("rparen"); return ')';}
;            { printline(); out("semi"); return ';';}

  /* ------ Assignments & Comparisions ------ */
\<-          { printline(); out("larrow"); return LARROW; }
=            { printline(); out("equals"); return '='; }
\<=          { printline(); out("le"); return LEQUAL;}
=\>          { printline(); out("re"); return GOES_TO;}
\<           { printline(); out("lt"); return '<';}

  /* -------------- Arthimetic ------------- */
-            { printline(); out("minus"); return '-';}
\+           { printline(); out("plus"); return '+';}
\~           { printline(); out("tilde"); return '~';}
\*           { printline(); out("times"); return '*';}

  /* -------------- Strings --------------- */
{STRING}     {
                printline();
                out("string");
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
