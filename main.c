#include "avl.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>

void operations(AVL* tree);

int main(){

    AVL* tree = avl_create();
    adding_info(tree);
    avl_delete(&tree);

    return 0;
}
void operations(AVL* tree){
    char* string = readLine();
    NODE* root = return_root(tree);
    int removable;

    while(strcmp(string,"F") != 0){
        removable = atoi(string);
        string = readLine();
    }
    pre_order_recursion(root);

    return;
}
