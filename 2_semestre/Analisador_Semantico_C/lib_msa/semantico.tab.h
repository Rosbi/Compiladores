/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SEMANTICO_TAB_H_INCLUDED
# define YY_YY_SEMANTICO_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    VOID_T = 258,                  /* VOID_T  */
    INT_T = 259,                   /* INT_T  */
    CHAR_T = 260,                  /* CHAR_T  */
    RETURN_T = 261,                /* RETURN_T  */
    DO_T = 262,                    /* DO_T  */
    WHILE_T = 263,                 /* WHILE_T  */
    FOR_T = 264,                   /* FOR_T  */
    IF_T = 265,                    /* IF_T  */
    ELSE_T = 266,                  /* ELSE_T  */
    ADD = 267,                     /* ADD  */
    SUB = 268,                     /* SUB  */
    ASTERISK = 269,                /* ASTERISK  */
    DIV = 270,                     /* DIV  */
    MOD = 271,                     /* MOD  */
    INC = 272,                     /* INC  */
    DEC = 273,                     /* DEC  */
    AMPERSAND = 274,               /* AMPERSAND  */
    BIT_OR = 275,                  /* BIT_OR  */
    BIT_NOT = 276,                 /* BIT_NOT  */
    BIT_XOR = 277,                 /* BIT_XOR  */
    LOG_AND = 278,                 /* LOG_AND  */
    LOG_OR = 279,                  /* LOG_OR  */
    LOG_NOT = 280,                 /* LOG_NOT  */
    EQUALS = 281,                  /* EQUALS  */
    NOT_EQUALS = 282,              /* NOT_EQUALS  */
    LESS = 283,                    /* LESS  */
    GREAT = 284,                   /* GREAT  */
    LEQ = 285,                     /* LEQ  */
    GEQ = 286,                     /* GEQ  */
    RSHIFT = 287,                  /* RSHIFT  */
    LSHIFT = 288,                  /* LSHIFT  */
    ASSIGN = 289,                  /* ASSIGN  */
    ADD_ASSIGN = 290,              /* ADD_ASSIGN  */
    SUB_ASSIGN = 291,              /* SUB_ASSIGN  */
    SEMICOLON = 292,               /* SEMICOLON  */
    COMMA = 293,                   /* COMMA  */
    COLON = 294,                   /* COLON  */
    LPAREN = 295,                  /* LPAREN  */
    RPAREN = 296,                  /* RPAREN  */
    LCBRACK = 297,                 /* LCBRACK  */
    RCBRACK = 298,                 /* RCBRACK  */
    LBRACK = 299,                  /* LBRACK  */
    RBRACK = 300,                  /* RBRACK  */
    QUEST_MARK = 301,              /* QUEST_MARK  */
    NUMBER_SIGN = 302,             /* NUMBER_SIGN  */
    DEFINE = 303,                  /* DEFINE  */
    PRINTF_T = 304,                /* PRINTF_T  */
    SCANF_T = 305,                 /* SCANF_T  */
    EXIT_T = 306,                  /* EXIT_T  */
    NUM_HEXA = 307,                /* NUM_HEXA  */
    NUM_OCTA = 308,                /* NUM_OCTA  */
    NUM_INT = 309,                 /* NUM_INT  */
    CHARACTER = 310,               /* CHARACTER  */
    STRING = 311,                  /* STRING  */
    IDENTIFIER = 312,              /* IDENTIFIER  */
    LINE_COMMENT = 313,            /* LINE_COMMENT  */
    BLOCK_COMMENT = 314,           /* BLOCK_COMMENT  */
    UNTERMINATED_COMMENT = 315,    /* UNTERMINATED_COMMENT  */
    UNKNOWN_CHAR = 316,            /* UNKNOWN_CHAR  */
    END_OF_FILE = 317,             /* END_OF_FILE  */
    ADDRESS = 318,                 /* ADDRESS  */
    MUL = 319,                     /* MUL  */
    BIT_AND = 320,                 /* BIT_AND  */
    POINTER_DEFERENCE = 321,       /* POINTER_DEFERENCE  */
    UNR_PLUS = 322,                /* UNR_PLUS  */
    UNR_MINUS = 323,               /* UNR_MINUS  */
    CONDITIONAL_EXP = 324,         /* CONDITIONAL_EXP  */
    CONDITIONAL_EXP_THENELSE = 325, /* CONDITIONAL_EXP_THENELSE  */
    SUBSCRIPT = 326,               /* SUBSCRIPT  */
    CAST = 327,                    /* CAST  */
    FUNCTION_CALL = 328,           /* FUNCTION_CALL  */
    COMMA_SEPARATOR = 329,         /* COMMA_SEPARATOR  */
    BREAK_T = 330,                 /* BREAK_T  */
    SWITCH_T = 331,                /* SWITCH_T  */
    CASE_T = 332,                  /* CASE_T  */
    DEFAULT_T = 333,               /* DEFAULT_T  */
    TYPEDEF_T = 334,               /* TYPEDEF_T  */
    STRUCT_T = 335                 /* STRUCT_T  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "semantico.y"

	char* string;
	int integer;
	char charac;
	struct symbol* symbol_union;
	struct array* array_union;
	struct expression* expression_union;
	struct parameters* parameters_union;
	struct command_list* commands_union;
	struct function_definition* func_def_union;

#line 156 "semantico.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);
/* "%code provides" blocks.  */
#line 1 "semantico.y"

#include<stdio.h>
extern FILE* in_file;
void setup(FILE* set_in_file);

#line 189 "semantico.tab.h"

#endif /* !YY_YY_SEMANTICO_TAB_H_INCLUDED  */
