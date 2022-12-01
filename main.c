#include "avl.h"
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    AVL *tree = avl_create();
    int option;
    int ano;
    char* string;

    adding_info(tree);

    scanf("%d", &option);
    avl_print_2d(tree);
    while(getchar() != '\n');
    
    do{
        string = readLine();
        ano = atoi(string);
        deletar_por_ano(tree, ano);
    } while (strcmp(string, "F") != 0);

    print_avl(tree, option);
    free(string);
    avl_delete(&tree);
    
    return 0;
}
