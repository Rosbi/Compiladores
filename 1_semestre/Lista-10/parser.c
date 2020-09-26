#include"parser.h"

static token_type g_token = TOKEN_ERROR;

const int productions_quantity = 6;
const int terminals_quantity   = 6;
const int8_t LL1_table[productions_quantity][terminals_quantity] = {

}

bool S(){

}
bool E(){
    
}
bool E1(){
    
}
bool T(){
    
}
bool T1(){
    
}
bool F(){
    
}

bool error(){}

bool advance(FILE* file_in){
    do{
        g_token = getToken(file_in);
    }while(g_token == WHITESPACE);
    return true;
}

bool eat(token_type t){
    if(g_token == t){
        advance();
        return true;
    }
    error(t);
    return false;
}
