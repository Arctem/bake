#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int yylineno;
extern int nelements;
extern FILE* yyin;

int yylex(void);

int main(int argc, char** argv)
{
  if (argc < 2) {
    printf("Usage: %s file\n",argv[0]);
    printf("  where file is an XML file to scan\n");
    exit(-1);
  }

  if ((yyin = fopen(argv[1],"r")) == NULL) {
    printf("Unable to open file %s\n",argv[1]);
    exit(-1);
  }

  yylex();
  printf("# elements in the file %s is %d\n",argv[1],nelements);
}
