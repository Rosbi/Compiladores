#include<stdio.h>
#include"globals.h"
#include"lex_analyser.h"
#include"parser.h"
#include"custom_print.h"
#include<unistd.h>

int main(){
    file_in = stdin;

    token_type token = TOKEN_ERROR;
    while(token != TOKEN_EOF){
        token = getToken(file_in);
        myprintf("%s", tokenStringify(token));
    }
/*    stackCreate(&stck);
    token_type input_token;

    while(true){
        input_token = advance();
        stackPush(stck, S_nt);
        while(s_token != NEWLINE){

            if(stackIsEmpty(stck)){
                myprintf("CADEIA ACEITA");
                break;
            }

            // printStack(stck);
            s_token = stackPop(stck);
            
            //Tokens terminais
            if(s_token > terminal_start && s_token < terminal_end){
                if(eat(input_token)){
                    input_token = advance();
                }

            }
            //Tokens não-terminas
            else if(s_token > nonterminal_start && s_token < nonterminal_end){
                if(!transition(input_token)){
                    myprintf("ERRO SINTATICO EM: %sESPERADO: %s", tokenStringify(input_token), ll1_expected);
                    stackDump(stck);
                    break;
                }
            }
            //Outros casos
            else{
                
            }

            if(input_token == TOKEN_ERROR){
                myprintf("ERRO LEXICO: %c", lex_error);
                break;
            }
        }
        while(input_token != NEWLINE && input_token != TOKEN_EOF){
            input_token = getToken(file_in);
        }
        if(input_token == TOKEN_EOF){
            break;
        }
    }*/

    return 0;
}