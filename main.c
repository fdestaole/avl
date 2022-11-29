#include "avl.h"
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void operations(AVL *tree);

int main()
{
    AVL *tree = avl_create();
    int option;
    char *string;
    int ano;

    adding_info(tree);

    scanf("%d", &option);
    scanf("%*c");
    scanf("%*c");
    do{
        string = readLine();
        ano = atoi(string);
        deletar_por_ano(tree, ano);
    } while (strcmp(string, "F") != 0);

    print_avl(tree, option);
}
