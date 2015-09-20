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
INTEGER     [0-9]+
STRING      \"([^\n\Z\"])*\"

/* Start conditions */
%x COMMENT
%x BLOCK_COMMENT

%%
  /* -----------------  RULES ----------------*/

\(\*         { yy_push_state(BLOCK_COMMENT); }

--           { yy_push_state(COMMENT); }

\@           { printline(); out("at"); }

case         { printline(); out("case"); }

class        { printline(); out("class"); }

:            { printline(); out("colon"); }

,            { printline(); out("comma"); }

\/            { printline(); out("divide"); }

\.           { printline(); out("dot"); }

else         { printline(); out("else"); }

=            { printline(); out("equals"); }

esac         { printline(); out("esac"); }

false        { printline(); out("false"); }

fi           { printline(); out("fi"); }

if           { printline(); out("if"); }

in           { printline(); out("in"); }

inherits     { printline(); out("inherits"); }

{INTEGER}    { printline(); out("integer"); out(yytext); }

isvoid       { printline(); out("isvoid"); }

\<-          { printline(); out("larrow"); }

\{           { printline(); out("lbrace"); }

\<=          { printline(); out("le"); }

let          { printline(); out("let"); }

loop         { printline(); out("loop"); }

\(           { printline(); out("lparen"); }

\<           { printline(); out("lt"); }

-            { printline(); out("minus"); }

new          { printline(); out("new"); }

not          { printline(); out("not"); }

of           { printline(); out("of"); }

\+           { printline(); out("plus"); }

pool         { printline(); out("pool"); }

-\>          { printline(); out("rarrow"); }

\}           { printline(); out("rbrace"); }

\)           { printline(); out("rparen"); }

;            { printline(); out("semi"); }

{STRING}     {
                printline();
                out("string");
                yytext[yyleng - 1] = '\0';
                out(yytext + 1);
             }

then         { printline(); out("then"); }

\~           { printline(); out("tilde"); }

\*           { printline(); out("times"); }

true         { printline(); out("true"); }

{TYPE}       { printline(); out("type"); out(yytext); }

while        { printline(); out("while"); }

{IDENTIFIER} { printline(); out("identifier"); out(yytext); }

[ \t\n\r]*   { /* consume the whitespace */ }

.       { out(yytext); exit(0); }

<COMMENT>{
  \n         { yy_pop_state(); }

  .          {  }
}
<BLOCK_COMMENT>{
  /* Ignore everything in comments, but allow nexting comments because we cool. */
  \(\*       { yy_push_state(COMMENT); }

  \*\)       { yy_pop_state(); }

  .          {  }
}
%%
