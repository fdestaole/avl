#ifndef TADGENERICO_AVL_H
#define TADGENERICO_AVL_H

#include "game.h"

typedef int boolean;

#define max(a, b) ((a > b) ? a : b)
typedef struct avl AVL;

void avl_apagar(AVL **arvore);
AVL *avl_criar();
void binary_tree_pre_order(AVL* tree);
boolean avl_inserir(AVL *arvore, GAME* game);

#endif //TADGENERICO_AVL_H
