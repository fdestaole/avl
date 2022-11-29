#ifndef TADGENERICO_AVL_H
#define TADGENERICO_AVL_H

#include "game.h"
#include <stdbool.h>

#define max(a, b) ((a > b) ? a : b)
typedef struct avl AVL;

void avl_delete(AVL **arvore);
AVL *avl_create();
void binary_tree_pre_order(AVL* tree);
bool avl_insert(AVL *arvore, GAME* game);
void print_avl(AVL *tree, int option);
void avl_print_2d(AVL *tree);
void deletar_por_ano(AVL *tree, int year);

#endif // TADGENERICO_AVL_H
