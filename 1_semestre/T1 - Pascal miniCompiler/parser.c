#include"parser.h"
#include"stack.h"
#include"globals.h"

token_type s_token = TOKEN_ERROR;

char* ll1_expected = "oi mae";

bool transition(token_type input_token){
    switch(s_token){
        case S_nt:
            return S(input_token);
        case E_nt:
            return E(input_token);
        case E1_nt:
            return E1(input_token);
        case T_nt:
            return T(input_token);
        case T1_nt:
            return T1(input_token);
        case F_nt:
            return F(input_token);
        default:
            return false;
    }
}

bool S(token_type input_token){
    switch(input_token){
        case ID:
        case LPAREN:
            stackPush(stck, DOLLAR);
            stackPush(stck, E_nt);
            break;
        default:
            ll1_expected = "id, (";
            return false;
    }
    return true;
}
bool E(token_type input_token){
    switch(input_token){
        case ID:
        case LPAREN:
            stackPush(stck, E1_nt);
            stackPush(stck, T_nt);
        break;
        default:
            ll1_expected = "id, (";
            return false;
    }
    return true;
}
bool E1(token_type input_token){
    switch(input_token){
        case PLUS_SIGN:
            stackPush(stck, E1_nt);
            stackPush(stck, T_nt);
            stackPush(stck, PLUS_SIGN);
            break;
        case RPAREN:
        case DOLLAR:
            break;
        default:
            ll1_expected = "+, ), $";
            return false;
    }
    return true;
}
bool T(token_type input_token){
    switch (input_token)
    {
    case ID:
    case LPAREN:
        stackPush(stck, T1_nt);
        stackPush(stck, F_nt);
        break;
    default:
            ll1_expected = "id, (";
        return false;
    }
    return true;
}
bool T1(token_type input_token){
    switch(input_token){
        case MULT_SIGN:
            stackPush(stck, T1_nt);
            stackPush(stck, F_nt);
            stackPush(stck, MULT_SIGN);
            break;
        case PLUS_SIGN:
        case RPAREN:
        case DOLLAR:
            break;
        default:
            ll1_expected = "+, *, ), $";
            return false;
    }
    return true;
}
bool F(token_type input_token){
    switch(input_token){
        case ID:
            stackPush(stck, ID);
            break;
        case LPAREN:
            stackPush(stck, RPAREN);
            stackPush(stck, E_nt);
            stackPush(stck, LPAREN);
            break;
        default:
            ll1_expected = "id, )";
            return false;
    }
    return true;
}

bool error(){}

token_type advance(){
    token_type token;
    do{
        token = getToken(file_in);
    }while(token == WHITESPACE);
    return token;
}

bool eat(token_type t){
    if(s_token == t){
        return true;
    }
    error(t);
    return false;
}
