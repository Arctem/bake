%{

/* An XML scanner that checks for unbalanced tags and syntax errors.
 * If the input XML file is syntactically correct, prints out number of
 * elements.
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


// Put here any variables that you may need in the actions.
int nelements = 0;
std::stack<char*> elemstack;

%}

%option yylineno
%option noyywrap

/* Chars allowable in element and attribute names */
NAME        [a-zA-Z][a-zA-Z0-9:._]*

/* Start conditions */
%x NEWELEMENT

%%
  /* -----------------  RULES ----------------*/


  /* ignore the preamble and any whitespace after it if present.
   * starts with <? and ends in ?>
   */
\<\?.*\?\>[ \t\n\r]*   { /* */ }


  /* Element start tag "<name" */
\<{NAME}      {
                 char* elementname = (char*) malloc(yyleng);
		 strcpy(elementname, yytext+1);
		 elemstack.push(elementname);
                 BEGIN(NEWELEMENT);
                 DEBUG("< (%s) ", elementname);
		 nelements++;
               }

  /* Element close tag  "</name>" */
\<\/{NAME}\>  {
                 char* elementname = yytext + 2;
                 yytext[yyleng-1] = '\0'; // Delete the last char('>')
		 if(strcmp(elementname, elemstack.top()) == 0) {
                   DEBUG("</ (%s) >", elementname);
		   free(elemstack.top());
		   elemstack.pop();
		 } else {
		   printf("\nMismatched elements: %s %s\n", elementname, elemstack.top());
		   exit(1);
		 }
               }

\<         { printf("\nInvalid character '%s' on line %d\n",yytext,yylineno); exit(1); }

.          {/* absorb things outside of tags */}

  /* Start condition for new element tags. Anything that can go
   * between "<elementname" and ">" should be defined here.
   * Also, catch > and /> here.
   */
<NEWELEMENT>{

    /* Element start tag closing ">" */
  \>          { DEBUG("> "); BEGIN(INITIAL); }

    /* Element start tag closing "/>" */
  \/\>          { DEBUG("/> "); BEGIN(INITIAL); free(elemstack.top()); elemstack.pop(); }


    /* Eat up the whitespace in element start tags */
  [ \t\n\r]*   { /* consume the whitespace */ }

    /* Any element attributes */
  {NAME}=(\"(\\\"|[^\"])+\")|('(\\'|[^'])+') {
                         char* attrname = yytext;
                         DEBUG("(%s) ", attrname);
                       }


    /* Anything that we can't recognize */
  .          {
              printf("\nInvalid character '%s' on line %d\n",yytext,yylineno);
              exit(1);
             }

} /* End of NEWELEMENT start condition */

  /* Keep the indentation for better display */
[ \t\n\r]*     { DEBUG("%s",yytext);}
<<EOF>>      {
               if(elemstack.size() > 0) {
		 printf("\n %d unclosed elements.\n", elemstack.size());
		 exit(1);
	       }
               return 0; // to tell the main that we are done.
             }

  /* Here define a rule to match text between elements */
%%
