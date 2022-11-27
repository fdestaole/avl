#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "avl.h"

#define max(a, b) ((a > b) ? a : b)

struct node_st
{
    GAME* game;
    NODE* right;
    NODE* left;
    int height;
};

struct avl
{
    NODE* root;
    int depth;
};
void binary_tree_pre_order(AVL* tree){
    pre_order_recursion(tree->root);
}
void pre_order_recursion(NODE* root){
    if (root != NULL) {
        printf("%s", return_name(root->game));
        pre_order_recursion(root->left);
        pre_order_recursion(root->right);
    }
}
NODE* search_node(NODE* root, int year){
    if(root == NULL) {
        return NULL;
    }
    if(year == return_year(root->game)) {
        return root;
    }
    if(year < return_year(root->game)) {
        return (search_node(root->left, year));
    }
    else {
        return (search_node(root->right, year));
    }
}
AVL *avl_create() {
    AVL *tree = (AVL *) malloc(sizeof(AVL));
    if (tree != NULL) {
        tree->root = NULL;
        tree->depth = -1;
    }
    return tree;
}
NODE* return_root(AVL* tree){
    return tree->root;
}

void avl_delete_aux(NODE** root) {
    if (*root != NULL) {
        avl_delete_aux(&((*root)->left));
        avl_delete_aux(&((*root)->right));
        free_game(&(*root)->game);
        free(*root);
    }
}

void avl_delete(AVL** tree) {
    avl_delete_aux(&(*tree)->root);
    free(*tree);
    *tree = NULL;
}

int avl_altura_no(NODE* root) {
    if (root == NULL) {
        return -1;
    } else {
        return root->height;
    }
}

NODE* avl_create_node(GAME* game) {
    NODE* node = (NODE *) malloc(sizeof (NODE));
    if (node != NULL) {
        node->height = 0;
        node->right = NULL;
        node->left = NULL;
        node->game = game;
    }
    return node;
}

NODE *rodar_direita(NODE* a) {
    NODE *b = a->left;
    a->left = b->right;
    b->right = a;

    a->height = max(avl_altura_no(a->left),
                    avl_altura_no(a->right)) + 1;
    b->height = max(avl_altura_no(b->left),
                    a->height) + 1;
    return b;
}

NODE *rodar_esquerda(NODE *a) {
    NODE *b = a->right;
    a->right = b->left;
    b->left = a;

    a->height = max(avl_altura_no(a->left),
                    avl_altura_no(a->right)) + 1;
    b->height = max(avl_altura_no(b->right),
                    a->height) + 1;
    return b;
}

NODE *rodar_esquerda_direita(NODE *a)   {
    a->left = rodar_esquerda(a->left);
    return rodar_direita(a);
}

NODE *rodar_direita_esquerda(NODE *a)   {
    a->right = rodar_direita(a->right);
    return rodar_esquerda(a);
}

NODE *avl_inserir_no_e_rotacionar(NODE* root,GAME* game) {
    root = insert_node(root, game);

    root->height = max(avl_altura_no(root->left),
                       avl_altura_no(root->right)) + 1;

    root = selecionar_e_executar_rotacao(root, game);

    return root;
}

NODE* insert_node(NODE *root, GAME* game) {
    if (root == NULL) {
        root = avl_create_node(game);
    }
    else if (compare(root, game) == 1) {
        root->right = avl_inserir_no_e_rotacionar(root->right, game);
    }
    else if (compare(root, game) == -1) {
        root->left = avl_inserir_no_e_rotacionar(root->left, game);
    }
    return root;
}

NODE *selecionar_e_executar_rotacao(NODE* root, GAME* game) {
    if (DesbalanceamentoEhNegativo(root)) {
        if (compare(root->right, game) == 1) {
            root = rodar_esquerda(root);
        }
        else {
            root = rodar_direita_esquerda(root);
        }
    }

    if (DesbalanceamentoEhPositivo(root)) {
        if (compare(root->left, game) == -1)
            root = rodar_direita(root);
        else
            root = rodar_esquerda_direita(root);
    }
    return root;
}

int compare(NODE *root, GAME* game) {
    if(return_year(game) != return_year(root->game)){
        if(strlen(return_name(game)) > strlen(return_name(root->game))){
            return 1;
        }
        else return -1;
    }
    else{
        if(return_year(game) > return_year(root->game)) return 1;
        else return -1;
    }
}

bool DesbalanceamentoEhPositivo(NODE *root) {
    return avl_altura_no(root->left)
           - avl_altura_no(root->right) == 2;
}

bool DesbalanceamentoEhNegativo(NODE *root) {
    return avl_altura_no(root->left)
           - avl_altura_no(root->right) == -2;
}

bool avl_insert(AVL* tree, GAME* game) {
    tree->root = avl_inserir_no_e_rotacionar(tree->root, game);
    return tree->root != NULL;
}







