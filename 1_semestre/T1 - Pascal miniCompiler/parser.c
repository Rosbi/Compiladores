#include"parser.h"
#include"stack.h"
#include"globals.h"

bool PROGRAMA(token_type input_token);
bool BLOCO(token_type input_token);
bool BLOCO1(token_type input_token);
bool BLOCO_C1(token_type input_token);
bool BLOCO_C11(token_type input_token);
bool BLOCO_C2(token_type input_token);
bool TIPO(token_type input_token);
bool PARAMETROS(token_type input_token);
bool PARAMETROS1(token_type input_token);
bool PARAMETROS11(token_type input_token);
bool PARAMETROS_C1(token_type input_token);
bool VARIAVEL1(token_type input_token);
bool VARIAVEL_C1(token_type input_token);
bool COMANDO(token_type input_token);
bool COMANDO0(token_type input_token);
bool COMANDO1(token_type input_token);
bool COMANDO2(token_type input_token);
bool COMANDO_C1(token_type input_token);
bool COMANDO_C2(token_type input_token);
bool EXPRESSAO(token_type input_token);
bool EXPRESSAO1(token_type input_token);
bool SINAL(token_type input_token);
bool EXP_SIMPLES(token_type input_token);
bool EXP_SIMPLES1(token_type input_token);
bool TERMO(token_type input_token);
bool TERMO1(token_type input_token);
bool FATOR(token_type input_token);
bool FATOR0(token_type input_token);
bool FATOR_E(token_type input_token);
bool FATOR_E1(token_type input_token);

token_type s_token = TOKEN_ERROR;

char* ll1_expected = "oi mae";

bool transition(token_type input_token){
    switch(s_token){
        case PROGRAMA_nt:        return PROGRAMA(input_token);
        case BLOCO_nt:           return BLOCO(input_token);
        case BLOCO1_nt:          return BLOCO1(input_token);
        case BLOCO_C1_nt:        return BLOCO_C1(input_token);
        case BLOCO_C11_nt:       return BLOCO_C11(input_token);
        case BLOCO_C2_nt:        return BLOCO_C2(input_token);
        case TIPO_nt:            return TIPO(input_token);
        case PARAMETROS_nt:      return PARAMETROS(input_token);
        case PARAMETROS1_nt:     return PARAMETROS1(input_token);
        case PARAMETROS11_nt:    return PARAMETROS11(input_token);
        case PARAMETROS_C1_nt:   return PARAMETROS_C1(input_token);
        case VARIAVEL1_nt:       return VARIAVEL1(input_token);
        case VARIAVEL_C1_nt:     return VARIAVEL_C1(input_token);
        case COMANDO_nt:         return COMANDO(input_token);
        case COMANDO0_nt:        return COMANDO0(input_token);
        case COMANDO1_nt:        return COMANDO1(input_token);
        case COMANDO2_nt:        return COMANDO2(input_token);
        case COMANDO_C1_nt:      return COMANDO_C1(input_token);
        case COMANDO_C2_nt:      return COMANDO_C2(input_token);
        case EXPRESSAO_nt:       return EXPRESSAO(input_token);
        case EXPRESSAO1_nt:      return EXPRESSAO1(input_token);
        case SINAL_nt:           return SINAL(input_token);
        case EXP_SIMPLES_nt:     return EXP_SIMPLES(input_token);
        case EXP_SIMPLES1_nt:    return EXP_SIMPLES1(input_token);
        case TERMO_nt:           return TERMO(input_token);
        case TERMO1_nt:          return TERMO1(input_token);
        case FATOR_nt:           return FATOR(input_token);
        case FATOR0_nt:          return FATOR0(input_token);
        case FATOR_E_nt:         return FATOR_E(input_token);
        case FATOR_E1_nt:        return FATOR_E1(input_token);

        default:                 return false;
    }
}

bool PROGRAMA(token_type input_token){
    switch(input_token){
        case PROGRAM:
            stackPush(stck, PERIOD);
            stackPush(stck, BLOCO_nt);
            stackPush(stck, SEMICOLON);
            stackPush(stck, ID);
            stackPush(stck, PROGRAM);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool BLOCO(token_type input_token){
    switch(input_token){
        case ID:
            stackPush(stck, BLOCO1_nt);
            break;
        case VAR:
            stackPush(stck, BLOCO1_nt);
            stackPush(stck, BLOCO_C1_nt);
            stackPush(stck, VAR);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool BLOCO1(token_type input_token){
    switch(input_token){
        case PROCEDURE:
            stackPush(stck, BLOCO1_nt);
            stackPush(stck, SEMICOLON);
            stackPush(stck, BLOCO_nt);
            stackPush(stck, SEMICOLON);
            stackPush(stck, PARAMETROS_nt);
            stackPush(stck, ID);
            stackPush(stck, PROCEDURE);
            break;
        case FUNCTION:
            stackPush(stck, BLOCO1_nt);
            stackPush(stck, SEMICOLON);
            stackPush(stck, BLOCO_nt);
            stackPush(stck, SEMICOLON);
            stackPush(stck, ID);
            stackPush(stck, COLON);
            stackPush(stck, PARAMETROS_nt);
            stackPush(stck, ID);
            stackPush(stck, FUNCTION);
            break;
        case BEGIN:
            stackPush(stck, END);
            stackPush(stck, BLOCO_C2_nt);
            stackPush(stck, COMANDO_nt);
            stackPush(stck, BEGIN);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool BLOCO_C1(token_type input_token){
    switch(input_token){
        case ID:
            stackPush(stck, BLOCO1_nt);
            stackPush(stck, SEMICOLON);
            stackPush(stck, TIPO_nt);
            stackPush(stck, COLON);
            stackPush(stck, BLOCO_C11_nt);
            stackPush(stck, ID);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool BLOCO_C11(token_type input_token){
    switch(input_token){
        case COLON:
            break;
        case COMMA:
            stackPush(stck, BLOCO_C11_nt);
            stackPush(stck, ID);
            stackPush(stck, COMMA);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool BLOCO_C2(token_type input_token){
    switch(input_token){
        case SEMICOLON:
            stackPush(stck, BLOCO_C2_nt);
            stackPush(stck, COMANDO_nt);
            stackPush(stck, SEMICOLON);
            break;
        case END:
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool TIPO(token_type input_token){
    switch(input_token){
        case ID:
            stackPush(stck, ID);
            break;
        case NUMBER:
            stackPush(stck, NUMBER);
            stackPush(stck, SINAL_nt);
            stackPush(stck, PERIOD);
            stackPush(stck, PERIOD);
            stackPush(stck, NUMBER);
            stackPush(stck, SINAL_nt);
            break;
        case PLUS:
            stackPush(stck, NUMBER);
            stackPush(stck, SINAL_nt);
            stackPush(stck, PERIOD);
            stackPush(stck, PERIOD);
            stackPush(stck, NUMBER);
            stackPush(stck, SINAL_nt);
            break;
        case MINUS:
            stackPush(stck, NUMBER);
            stackPush(stck, SINAL_nt);
            stackPush(stck, PERIOD);
            stackPush(stck, PERIOD);
            stackPush(stck, NUMBER);
            stackPush(stck, SINAL_nt);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool PARAMETROS(token_type input_token){
    switch(input_token){
        case SEMICOLON:
            break;
        case COLON:
            break;
        case LPAREN:
            stackPush(stck, PARAMETROS1_nt);
            stackPush(stck, LPAREN);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool PARAMETROS1(token_type input_token){
    switch(input_token){
        case ID:
            stackPush(stck, PARAMETROS1_nt);
            stackPush(stck, ID);
            stackPush(stck, COLON);
            stackPush(stck, PARAMETROS11_nt);
            stackPush(stck, ID);
            stackPush(stck, PARAMETROS_C1_nt);
            break;
        case VAR:
            stackPush(stck, PARAMETROS1_nt);
            stackPush(stck, ID);
            stackPush(stck, COLON);
            stackPush(stck, PARAMETROS11_nt);
            stackPush(stck, ID);
            stackPush(stck, PARAMETROS_C1_nt);
            break;
        case RPAREN:
            stackPush(stck, RPAREN);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool PARAMETROS11(token_type input_token){
    switch(input_token){
        case COLON:
            break;
        case COMMA:
            stackPush(stck, PARAMETROS11_nt);
            stackPush(stck, ID);
            stackPush(stck, COMMA);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool PARAMETROS_C1(token_type input_token){
    switch(input_token){
        case ID:
            break;
        case VAR:
            stackPush(stck, VAR);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool VARIAVEL1(token_type input_token){
    switch(input_token){
        case LBRACKET:
            stackPush(stck, VARIAVEL1_nt);
            stackPush(stck, RBRACKET);
            stackPush(stck, VARIAVEL_C1_nt);
            stackPush(stck, EXPRESSAO_nt);
            stackPush(stck, LBRACKET);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool VARIAVEL_C1(token_type input_token){
    switch(input_token){
        case SEMICOLON:
            break;
        case END:
            break;
        case COMMA:
            stackPush(stck, VARIAVEL_C1_nt);
            stackPush(stck, EXPRESSAO_nt);
            stackPush(stck, COMMA);
            break;
        case RPAREN:
            break;
        case RBRACKET:
            break;
        case ATTRIBUTION:
            break;
        case THEN:
            break;
        case DO_t:
            break;
        case DIFF:
            break;
        case LESS:
            break;
        case LEQ:
            break;
        case GEQ:
            break;
        case GREAT:
            break;
        case EQUALS:
            break;
        case PLUS:
            break;
        case MINUS:
            break;
        case LOG_OR:
            break;
        case LOG_AND:
            break;
        case MULTIPLY:
            break;
        case DIVIDE:
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool COMANDO(token_type input_token){
    switch(input_token){
        case ID:
            stackPush(stck, COMANDO0_nt);
            stackPush(stck, ID);
            break;
        case SEMICOLON:
            break;
        case BEGIN:
            stackPush(stck, COMANDO_C2_nt);
            stackPush(stck, BEGIN);
            break;
        case END:
            stackPush(stck, COMANDO0_nt);
            stackPush(stck, ID);
            break;
        case IF_t:
            stackPush(stck, COMANDO2_nt);
            stackPush(stck, COMANDO_C2_nt);
            stackPush(stck, COMANDO_nt);
            stackPush(stck, BEGIN);
            stackPush(stck, THEN);
            stackPush(stck, EXPRESSAO_nt);
            stackPush(stck, IF_t);
            break;
        case WHILE_t:
            stackPush(stck, COMANDO_nt);
            stackPush(stck, DO_t);
            stackPush(stck, EXPRESSAO_nt);
            stackPush(stck, WHILE_t);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool COMANDO0(token_type input_token){
    switch(input_token){
        case LPAREN:
            stackPush(stck, COMANDO1_nt);
            break;
        case LBRACKET:
            stackPush(stck, EXPRESSAO_nt);
            stackPush(stck, ATTRIBUTION);
            stackPush(stck, VARIAVEL1_nt);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool COMANDO1(token_type input_token){
    switch(input_token){
        case LPAREN:
            stackPush(stck, COMANDO_C1_nt);
            stackPush(stck, EXPRESSAO_nt);
            stackPush(stck, LPAREN);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool COMANDO2(token_type input_token){
    switch(input_token){
        case SEMICOLON:
            break;
        case END:
            break;
        case ELSE_t:
            stackPush(stck, COMANDO_C2_nt);
            stackPush(stck, COMANDO_nt);
            stackPush(stck, BEGIN);
            stackPush(stck, ELSE_t);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool COMANDO_C1(token_type input_token){
    switch(input_token){
        case COMMA:
            stackPush(stck, COMANDO_C1_nt);
            stackPush(stck, EXPRESSAO_nt);
            stackPush(stck, COMMA);
            break;
        case RPAREN:
            stackPush(stck, RPAREN);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool COMANDO_C2(token_type input_token){
    switch(input_token){
        case SEMICOLON:
            stackPush(stck, COMANDO_C2_nt);
            stackPush(stck, COMANDO_nt);
            stackPush(stck, SEMICOLON);
            break;
        case END:
            stackPush(stck, END);
            break;
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool EXPRESSAO(token_type input_token){
    switch(input_token){
        case ID:
        case NUMBER:
        case LPAREN:
        case PLUS:
        case MINUS:
        case LOG_NOT:
            stackPush(stck, EXPRESSAO1_nt);
            stackPush(stck, EXP_SIMPLES_nt);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool EXPRESSAO1(token_type input_token){
    switch(input_token){
        case SEMICOLON:
        case END:
        case COMMA:
        case RPAREN:
        case RBRACKET:
        case THEN:
        case DO_t:
            break;
        case DIFF:
            stackPush(stck, EXP_SIMPLES_nt);
            stackPush(stck, DIFF);
            break;
        case LESS:
            stackPush(stck, EXP_SIMPLES_nt);
            stackPush(stck, LESS);
            break;
        case LEQ:
            stackPush(stck, EXP_SIMPLES_nt);
            stackPush(stck, LEQ);
            break;
        case GEQ:
            stackPush(stck, EXP_SIMPLES_nt);
            stackPush(stck, GEQ);
            break;
        case GREAT:
            stackPush(stck, EXP_SIMPLES_nt);
            stackPush(stck, GREAT);
            break;
        case EQUALS:
            stackPush(stck, EXP_SIMPLES_nt);
            stackPush(stck, EQUALS);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool SINAL(token_type input_token){
    switch(input_token){
        case ID:
        case NUMBER:
        case LPAREN:
        case LOG_NOT:
            break;
        case PLUS:
            stackPush(stck, PLUS);
            break;
        case MINUS:
            stackPush(stck, MINUS);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool EXP_SIMPLES(token_type input_token){
    switch(input_token){
        case ID:
        case NUMBER:
        case LPAREN:
        case PLUS:
        case MINUS:
        case LOG_NOT:
            stackPush(stck, EXP_SIMPLES1_nt);
            stackPush(stck, TERMO_nt);
            stackPush(stck, SINAL_nt);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool EXP_SIMPLES1(token_type input_token){
    switch(input_token){
        case SEMICOLON:
        case END:
        case COMMA:
        case RPAREN:
        case RBRACKET:
        case THEN:
        case DO_t:
        case DIFF:
        case LESS:
        case LEQ:
        case GEQ:
        case GREAT:
        case EQUALS:
            break;
        case PLUS:
            stackPush(stck, EXP_SIMPLES1_nt);
            stackPush(stck, TERMO_nt);
            stackPush(stck, PLUS);
            break;
        case MINUS:
            stackPush(stck, EXP_SIMPLES1_nt);
            stackPush(stck, TERMO_nt);
            stackPush(stck, MINUS);
            break;
        case LOG_OR:
            stackPush(stck, EXP_SIMPLES1_nt);
            stackPush(stck, TERMO_nt);
            stackPush(stck, LOG_OR);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool TERMO(token_type input_token){
    switch(input_token){
        case ID:
        case NUMBER:
        case LPAREN:
        case LOG_NOT:
            stackPush(stck, TERMO1_nt);
            stackPush(stck, FATOR_nt);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool TERMO1(token_type input_token){
    switch(input_token){
        case SEMICOLON:
        case END:
        case COMMA:
        case RPAREN:
        case RBRACKET:
        case THEN:
        case DO_t:
        case DIFF:
        case LESS:
        case LEQ:
        case GEQ:
        case GREAT:
        case EQUALS:
        case PLUS:
        case MINUS:
        case LOG_OR:
            break;
        case LOG_AND:
            stackPush(stck, TERMO1_nt);
            stackPush(stck, FATOR_nt);
            stackPush(stck, LOG_AND);
            break;
        case MULTIPLY:
            stackPush(stck, TERMO1_nt);
            stackPush(stck, FATOR_nt);
            stackPush(stck, MULTIPLY);
            break;
        case DIVIDE:
            stackPush(stck, TERMO1_nt);
            stackPush(stck, FATOR_nt);
            stackPush(stck, DIVIDE);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool FATOR(token_type input_token){
    switch(input_token){
        case ID:
            stackPush(stck, FATOR0_nt);
            stackPush(stck, ID);
            break;
        case NUMBER:
            stackPush(stck, NUMBER);
            break;
        case LPAREN:
            stackPush(stck, RPAREN);
            stackPush(stck, EXPRESSAO_nt);
            stackPush(stck, LPAREN);
            break;
        case LOG_NOT:
            stackPush(stck, FATOR_nt);
            stackPush(stck, LOG_NOT);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool FATOR0(token_type input_token){
    switch(input_token){
        case LPAREN:
            stackPush(stck, FATOR_E_nt);
            stackPush(stck, LPAREN);
            break;
        case LBRACKET:
            stackPush(stck, VARIAVEL1_nt);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool FATOR_E(token_type input_token){
    switch(input_token){
        case ID:
            stackPush(stck, FATOR_E1_nt);
            stackPush(stck, EXPRESSAO_nt);
            break;
        case NUMBER:
        case LPAREN:
        case PLUS:
        case MINUS:
        case LOG_NOT:
            stackPush(stck, FATOR_E1_nt);
            stackPush(stck, EXPRESSAO_nt);
            break;
        case RPAREN:
            stackPush(stck, RPAREN);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}
bool FATOR_E1(token_type input_token){
    switch(input_token){
        case COMMA:
            stackPush(stck, FATOR_E1_nt);
            stackPush(stck, EXPRESSAO_nt);
            stackPush(stck, COMMA);
            break;
        case RPAREN:
            stackPush(stck, RPAREN);
            break;
        default:
            ll1_expected = "";
            return false;
    }
    return true;
}

bool error(){}

token_type advance(){
    token_type token;
    do{
        token = getToken(file_in);
    }while(token == WHITESPACE || token == NEWLINE);
    return token;
}

bool eat(token_type t){
    if(s_token == t){
        return true;
    }
    error(t);
    return false;
}
