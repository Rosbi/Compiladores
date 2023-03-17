//
// Created by sophie on 01/03/23.
//
extern "C" {
    #include"ast_symbols.h"
    #include"hashTable.h"
    #include"semantico.tab.h"
}
#include<cstdio>
#include<vector>

int main() {
    // in_file = stdin;
    setup(stdin);
    // Program_Table.Global_Symbol_Table = criaTabela(15);
    yyparse();
    printFunctionBody(Program_Table.head->next->function.commands_head);
    // char** keys = getAllKeys(Program_Table.head->function.Local_Symbol_Table);
    // int i = 0;
    // while(keys[i]) {
    //     printf("\n%s\n", keys[i]);
    //     i++;
    // }

    return 0;
}
