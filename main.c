#include "avl.h"
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void operations(AVL* tree);

int main(){

    AVL* tree = avl_create();
    int option;
    adding_info(tree);

    avl_print_2d(tree);

    scanf("%d",&option);

    print_avl(tree, option);

    return 0;
}

void operations(AVL* tree){
    char* string = readLine();
    // int removable;

    while(strcmp(string,"F") == 0){
        // removable = atoi(string);
        string = readLine();
    }
    binary_tree_pre_order(tree);

    return;
}
