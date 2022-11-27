#ifndef EX_7_AVL_H
#define EX_7_AVL_H

#include <stdbool.h>
#include "game.h"


typedef struct avl AVL;
typedef struct node_st NODE;

void binary_tree_pre_order(AVL* tree);
void pre_order_recursion(NODE* root);
NODE* search_node(NODE* root, int year);
void avl_delete_aux(NODE** root);
NODE* return_root(AVL* tree);
NODE *avl_inserir_no_e_rotacionar(NODE* root,GAME* game);
bool DesbalanceamentoEhNegativo(NODE* root);
bool DesbalanceamentoEhPositivo(NODE* root);
int compare(NODE *root, GAME* game);
NODE *selecionar_e_executar_rotacao(NODE* root,GAME* game);
NODE* insert_node(NODE* root,GAME* game);
void avl_delete(AVL** tree);
AVL *avl_create();
bool avl_insert(AVL* tree,GAME* game);

#endif //EX_7_AVL_H
