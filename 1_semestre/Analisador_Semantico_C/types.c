#include"ast_symbols.h"
#include"types.h"
#include"errors.h"

const int TIPOS_POINTER_SIZE = 32;
const int TIPOS_INT_SIZE     = 32;
const int TIPOS_CHAR_SIZE    =  8;
const int TIPOS_VOID_SIZE    =  8;

const int compatibility_table[29][6] = {
                            /*  INT/INT  CHAR/CHAR  INT/CHAR  PNT/INT  PNT/CHAR PNT/PNT   */
    /* PLUS_COMP         */ {      1,        1,        1,        1,       1,       0      },
    /* MINUS_COMP        */ {      1,        1,        1,        2,       2,       0      },
    /* MUL_COMP          */ {      1,        1,        1,        0,       0,       0      },
    /* DIV_COMP          */ {      1,        1,        1,        0,       0,       0      },
    /* REMAINDER_COMP    */ {      1,        1,        1,        0,       0,       0      },
    /* BIT_AND_COMP      */ {      1,        1,        1,        0,       0,       0      },
    /* BIT_OR_COMP       */ {      1,        1,        1,        0,       0,       0      },
    /* BIT_XOR_COMP      */ {      1,        1,        1,        0,       0,       0      },
    /* LOG_AND_COMP      */ {      1,        1,        1,        1,       1,       1      },
    /* LOG_OR_COMP       */ {      1,        1,        1,        1,       1,       1      },
    /* EUQAL_COMP        */ {      1,        1,        1,        3,       3,       3      },
    /* DIFF_COMP         */ {      1,        1,        1,        3,       3,       3      },
    /* LESS_COMP         */ {      1,        1,        1,        3,       3,       3      },
    /* GREAT_COMP        */ {      1,        1,        1,        3,       3,       3      },
    /* LEQ_COMP          */ {      1,        1,        1,        3,       3,       3      },
    /* GEQ_COMP          */ {      1,        1,        1,        3,       3,       3      },
    /* RSHIFT_COMP       */ {      1,        1,        1,        4,       4,       0      },
    /* LSHIFT_COMP       */ {      1,        1,        1,        4,       4,       0      },
    /* ASSIGN_COMP       */ {      1,        1,        1,        7,       7,       5      },
    /* ADD_ASSIGN_COMP   */ {      1,        1,        1,        6,       6,       7      },
    /* SUB_ASSIGN_COMP   */ {      1,        1,        1,        6,       6,       7      },
                            /*    INT       CHAR      PNT        --       --       -      */
    /* UN_PLUS_COMP      */ {      1,        1,        8,        0,       0,       0      },
    /* UN_MINUS_COMP     */ {      1,        1,        9,        0,       0,       0      },
    /* UN_DEFERENCE_COMP */ {      0,        0,        1,        0,       0,       0      },
    /* UN_INC_COMP       */ {      1,        1,        1,        0,       0,       0      },
    /* UN_DEC_COMP       */ {      1,        1,        1,        0,       0,       0      },
    /* UN_BIT_NOT_COMP   */ {      1,        1,        0,        0,       0,       0      },
    /* UN_LOG_NOT_COMP   */ {      1,        1,        1,        0,       0,       0      },
    /* UN_ADDRESS_COMP   */ {      1,        1,        1,        0,       0,       0      },
};
const int types_fusion[3][3] = {
    { INT_INT,      INT_CHAR,    POINTER_INT     },
    { INT_CHAR,     CHAR_CHAR,   POINTER_CHAR    },
    { POINTER_INT, POINTER_CHAR, POINTER_POINTER },
};

Type_matching verifyTypes(struct var_type var1, struct var_type var2){
    Type_matching error = MATCH;

    if(var1.pointers == var2.pointers && var1.type == var2.type){ //variáveis compatíveis
        error = MATCH;
    }else if(!var1.pointers != !var2.pointers){     //uma, e apenas uma, é ponteiro
        error = PTR_AND_NON_PTR;
    }else if(var1.pointers > 0){    // ambas são ponteiros
        if(var1.pointers != var2.pointers){ // diferença de ponteiros
            error = PTR_MISSMATCH;
        }else if(var1.type != var2.type){ //diferença da base dos ponteiros
            error = BASE_PTR_MISSMATCH;
        }
    }else{  //nenhuma é ponteiro, mas os tipos diferem
        error = TYPE_MISSMATCH;
    }

    return error;
}

Error_list checkTypeMissmatch(int result_to_analyze, struct var_type var1, struct var_type var2, int var1_type, int var2_type){
    Error_list error = NO_ERROR;
    Type_matching matching = verifyTypes(var1, var2);

    switch(result_to_analyze){
        case 3: //pointer/(int/char/pointer) comparison
            if(matching == PTR_MISSMATCH || matching == BASE_PTR_MISSMATCH){
                error = WRONG_TYPE_COMPARISON;
            }else if(matching == PTR_AND_NON_PTR){
                error = WRONG_TYPE_COMPARISON_W;
            }
            break;
        case 5: //pointer/pointer assignment
            if(matching != MATCH){
                error = INCOMPATIBLE_ASSIGNMENT;
            }
            break;
        case 2: //pointer/(int/char) subtraction
        case 4: //pointer/(int/char) shift
            if(var1.pointers == 0){ //se var esquerda é valor, e var direita é ponteiro
                error = INVALID_BIN_OPERANDS;
            }
            break;
        case 6: //pointer/(int/char) (add/sub)assign
            if(var1.pointers == 0){ //se var esquerda é valor, e var direita é ponteiro
                error = INCOMPATIBLE_ASSIGNMENT;
            }
            break;
        case 7: error = INCOMPATIBLE_ASSIGNMENT; break;
        case 8: error = WRONG_ARG_UNR_PLUS;      break;
        case 9: error = WRONG_ARG_UNR_MINUS;     break;
    }

    return error;
}

Error_list matchTypes(int operation, struct var_type var1, struct var_type var2){
    int var1_type, var2_type, result;
    if(var1.pointers)
        { var1_type = POINTER_COMP; }
    else if(var1.type == TIPOS_INT)
        { var1_type = INT_COMP; }
    else
        { var1_type = CHAR_COMP; }

    if(var2.pointers)
        { var2_type = POINTER_COMP; }
    else if(var2.type == TIPOS_INT)
        { var2_type = INT_COMP; }
    else
        { var2_type = CHAR_COMP; }

    if(operation >= UN_PLUS_COMP){
        result = compatibility_table[operation][var1_type];
    }else{
        result = compatibility_table[operation][types_fusion[var1_type][var2_type]];
    }
    switch(result){
        case  0:
            if(operation >= UN_PLUS_COMP){
                return INVALID_UNR_OPERAND;
            }else{
                return INVALID_BIN_OPERANDS;
            }
        case  1: return NO_ERROR;
        default: return checkTypeMissmatch(result, var1, var2, var1_type, var2_type);
    }
}
