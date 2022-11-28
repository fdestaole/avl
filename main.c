#include "avl.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>

void operations(AVL* tree);

int main(){

    AVL* tree = avl_criar();
    adding_info(tree);

    return 0;
}
void operations(AVL* tree){
    char* string = readLine();
    int removable;

    while(strcmp(string,"F") == 0){
        removable = atoi(string);
        string = readLine();
    }
    binary_tree_pre_order(tree);

    return;
}
