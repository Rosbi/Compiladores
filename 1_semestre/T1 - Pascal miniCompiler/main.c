#include<stdio.h>
#include"globals.h"
#include"lex_analyser.h"
#include"parser.h"
#include"custom_print.h"

int main(){
    file_in = stdin;

    stackCreate(&stck);
    token_type input_token;

    input_token = advance();
    stackPush(stck, PROGRAMA_nt);
    while(input_token != TOKEN_EOF){

        s_token = stackPop(stck);
        
        //Tokens terminais
        if(s_token > terminal_start && s_token < terminal_end){
            if(eat(input_token)){
                input_token = advance();
            }else{
                myprintf("ERRO DE SINTAXE. Linha: %d -> \"%s\"", getLinha(), last_read_token);
                break;
            }

        }
        //Tokens não-terminas
        else if(s_token > nonterminal_start && s_token < nonterminal_end){
            if(!transition(input_token)){
                myprintf("ERRO DE SINTAXE. Linha: %d -> \"%s\"", getLinha(), last_read_token);
                break;
            }
        }
        //Outros casos
        else{
            
        }

        if(input_token == TOKEN_ERROR){
            myprintf("ERRO LEXICO. LINHA: %d COLUNA: %d -> %c", getLinha(), getColuna(), lex_error);
            break;
        }
    }

    if(stackIsEmpty(stck)){
        myprintf("PROGRAMA CORRETO.");
    }else{
        stackDump(stck);
    }
    stackFree(&stck);

    return 0;
}