%option noyywrap
%{

#include <sintatico.tab.h>
#include<string.h>

%}
%%

"+"         { return ADD; }
"-"         { return SUB; }

"*"         { return MUL; }
"/"         { return DIV; }

"^"         { return POW; }
"%"         { return MOD; }

"sen"       { return SEN; }
"cos"       { return COS; }
"tan"       { return TAN; }
"abs"       { return ABS; }

"("         { return LPAREN; }
")"         { return RPAREN; }
"["         { return LBRACK; }
"]"         { return RBRACK; }

[0-9]+"."[0-9]+ { yylval.real = atof(yytext);return REAL; }
[0-9]+          { yylval.integer = atoi(yytext); return NUM;  }
"x"             { return VAR;  }

"show"          { return CM_SHOW; }
"reset"         { return CM_RESET; }
"settings"      { return CM_SETTINGS; }
"quit"          { return CM_QUIT; }
"set"           { return CM_SET; }
"h_view"        { return CM_H_VIEW; }
"v_view"        { return CM_V_VIEW; }
"axis"          { return CM_AXIS; }
"on"            { return CM_ON; }
"off"           { return CM_OFF; }
"plot"          { return CM_PLOT; }
"integral"      { return CM_INTEGRAL; }
"steps"         { return CM_STEPS; }
"integrate"     { return CM_INTEGRATE; }
"matrix"        { return CM_MATRIX; }
"solve"         { return CM_SOLVE; }
"determinant"   { return CM_DETERMINANT; }
"linear_system" { return CM_LINEAR_SYSTEM; }
"about"         { return CM_ABOUT; }
"="             { return EQUALS; }
";"             { return SEMICOLON; }
":"             { return COLON; }
","             { return COMMA; }

\n          { return EOL; yy_flush_buffer(YY_CURRENT_BUFFER); }
[ \t]       { /* espaço em branco/tabulação */ }
[a-zA-Z_]+  { printf("Palavra nao reconhecida: %s\n", yytext); yy_flush_buffer(YY_CURRENT_BUFFER); return MISTERY; }
.           { printf("Simbolo invalido -> %s\n", yytext); yy_flush_buffer(YY_CURRENT_BUFFER); return MISTERY; }
<<EOF>>     { return END_OF_FILE; }

%%
