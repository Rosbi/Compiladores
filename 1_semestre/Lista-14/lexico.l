%option noyywrap
%{

#include <sintatico.tab.h>
#include<string.h>
#include"custom_print.h"

int colunas = 0;

%}
%%

"+"         { colunas++; return ADD; }
"-"         { colunas++; return SUB; }

"*"         { colunas++; return MUL; }
"/"         { colunas++; return DIV; }

"^"         { colunas++; return POW; }
"%"         { colunas++; return MOD; }

"sen"       { colunas+=3; return SEN; }
"cos"       { colunas+=3; return COS; }
"tan"       { colunas+=3; return TAN; }
"abs"       { colunas+=3; return ABS; }

"("         { colunas++; return LPAREN; }
")"         { colunas++; return RPAREN; }

[0-9]+                  { colunas+=strlen(yytext); return NUM;  }
[0-9]+"."               { colunas+=strlen(yytext); return REAL; }
[0-9]*"."[0-9]+         { colunas+=strlen(yytext); return REAL; }
[a-zA-z][a-zA-Z0-9]*    { colunas+=strlen(yytext); return VAR;  }

\n          { return EOL; }
[ \t]       { colunas++; /* espaço em branco/tabulação */ }
.           { return MISTERY; }
<<EOF>>     { return END_OF_FILE; }

%%
