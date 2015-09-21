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
#include <stack>

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
class        { printline(); out("class"); }
inherits     { printline(); out("inherits"); }
case         { printline(); out("case"); }
esac         { printline(); out("esac"); }
if           { printline(); out("if"); }
then         { printline(); out("then"); }
else         { printline(); out("else"); }
fi           { printline(); out("fi"); }
in           { printline(); out("in"); }
let          { printline(); out("let"); }
isvoid       { printline(); out("isvoid"); }
new          { printline(); out("new"); }
not          { printline(); out("not"); }
of           { printline(); out("of"); }
while        { printline(); out("while"); }
loop         { printline(); out("loop"); }
pool         { printline(); out("pool"); }


  /* --------------- BOOL Keywords ----------- */
f[a|A][l|L][s|S][e|E]        { printline(); out("false"); }
t[r|R][u|U][e|E]             { printline(); out("true"); }


  /* ----- Integers, Identifiers, Types ------ */
{TYPE}       { printline(); out("type"); out(yytext); }
{IDENTIFIER} { printline(); out("identifier"); out(yytext); }
{INTEGER}    {

                printline(); out("integer"); out(yytext);
             }


  /* --------------- Punctuation ------------ */
\@           { printline(); out("at"); }
:            { printline(); out("colon"); }
,            { printline(); out("comma"); }
\/            { printline(); out("divide"); }
\.           { printline(); out("dot"); }
\{           { printline(); out("lbrace"); }
\(           { printline(); out("lparen"); }
-\>          { printline(); out("rarrow"); }
\}           { printline(); out("rbrace"); }
\)           { printline(); out("rparen"); }
;            { printline(); out("semi"); }

  /* ------ Assignments & Comparisions ------ */
\<-          { printline(); out("larrow"); }
=            { printline(); out("equals"); }
\<=          { printline(); out("le"); }
\<           { printline(); out("lt"); }

  /* -------------- Arthimetic ------------- */
-            { printline(); out("minus"); }
\+           { printline(); out("plus"); }
\~           { printline(); out("tilde"); }
\*           { printline(); out("times"); }

  /* -------------- Strings --------------- */
{STRING}     {
                printline();
                out("string");
                yytext[yyleng - 1] = '\0';
                out(yytext + 1);
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
                  errorOut("ERROR: <<EOF>> found before end of comment");
                  exit(-1);
               }

  .             { /* anything is allowed in comments */ }
}
%%
