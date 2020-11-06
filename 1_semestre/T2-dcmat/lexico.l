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

[0-9]+"."[0-9]+ { yylval.real = atof(yytext);return REAL; }
[0-9]+          { yylval.integer = atoi(yytext); return NUM;  }
"x"             { return VAR;  }

"show settings"         { return CM_SHOW_SETTINGS; }
"reset settings"        { return CM_RESET_SETTINGS; }
"quit"                  { return CM_QUIT; }
"set"                   { return CM_SET; }
"h_view"                { return CM_H_VIEW; }
"v_view"                { return CM_V_VIEW; }
"axis on"               { return CM_AXIS_ON; }
"axis off"              { return CM_AXIS_OFF; }
"plot"                  { return CM_PLOT; }
"integral steps"        { return CM_INTEGRAL_STEPS; }
"integrate"             { return CM_INTEGRATE; }
"matrix"                { return CM_MATRIX; }
"show matrix"           { return CM_SHOW_MATRIX; }
"solve determinant"     { return CM_SOLVE_DETERMINANT; }
"solve linear_system"   { return CM_SOLVE_LINEAR_SYSTEM; }
"about"                 { return CM_ABOUT; }
";"                     { return SEMICOLON; }
":"                     { return COLON; }


\n          { return EOL; yy_flush_buffer(YY_CURRENT_BUFFER); }
[ \t]       { /* espaço em branco/tabulação */ }
.           { printf("Simbolo invalido -> %s\n", yytext); yy_flush_buffer(YY_CURRENT_BUFFER); return MISTERY; }
<<EOF>>     { return END_OF_FILE; }

%%
