%option noyywrap
%{

#include <sintatico.tab.h>
#include<string.h>

%}
%%

"int"	{ return INT_T; }
"float"	{ return FLOAT_T; }
"char"	{ return CHAR_T; }

","	{ return COMMA; }
"$" { return DOLLAR; }

[a-z]+	{ yylval.string=yytext; return IDENTIFIER;  }

\n          { return EOL; }
[ \t]       { /* espaço em branco, tabulação */ }
<<EOF>>     { return END_OF_FILE; }
.           { return MISTERY; }

%%
