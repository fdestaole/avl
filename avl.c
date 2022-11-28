#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "avl.h"
#include "game.h"

typedef struct node_st NODE;

void pre_order_recursion(NODE* root);
static void avl_apagar_aux(NODE **raiz);
static NODE *avl_inserir_no_e_rotacionar(NODE *raiz, GAME* game);

static bool DesbalanceamentoEhNegativo(NODE *raiz);

static bool DesbalanceamentoEhPositivo(NODE *raiz);

static bool ItemEhMaior(const NODE *raiz, GAME *game);

static bool ItemEhMenor(const NODE *raiz, GAME *game);

static NODE *selecionar_e_executar_rotacao(NODE *raiz, GAME *game);

static NODE *inserir_no(NODE *raiz, GAME *game);

struct node_st
{
    GAME* game;
    NODE *direita;
    NODE *esquerda;
    int altura;
};

struct avl
{
    NODE* raiz;
    int profundidade;
};

void binary_tree_pre_order(AVL* tree){
    pre_order_recursion(tree->raiz);
}
void pre_order_recursion(NODE* root){
    if (root != NULL) {
        printf("%s\n", return_name(root->game));
        pre_order_recursion(root->esquerda);
        pre_order_recursion(root->direita);
    }
}
AVL *avl_criar() {
    AVL *arvore = (AVL *) malloc(sizeof(AVL));
    if (arvore != NULL) {
        arvore->raiz = NULL;
        arvore->profundidade = -1;
    }
    return arvore;
}

static void avl_apagar_aux(NODE **raiz) {
    if (*raiz != NULL) {
        avl_apagar_aux(&((*raiz)->esquerda));
        avl_apagar_aux(&((*raiz)->direita));
        free_game(&(*raiz)->game);
        free(*raiz);
    }
}

void avl_apagar(AVL **arvore) {
    avl_apagar_aux(&(*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

int avl_altura_no(NODE* raiz) {
    if (raiz == NULL) {
        return -1;
    } else {
        return raiz->altura;
    }
}

NODE *avl_cria_no(GAME* game) {
    NODE *no = (NODE *) malloc(sizeof (NODE));
    if (no != NULL) {
        no->altura = 0;
        no->direita = NULL;
        no->esquerda = NULL;
        no->game = game;
    }
    return no;
}

NODE *rodar_direita(NODE *a) {
    NODE *b = a->esquerda;
    a->esquerda = b->direita;
    b->direita = a;

    a->altura = max(avl_altura_no(a->esquerda),
                    avl_altura_no(a->direita)) + 1;
    b->altura = max(avl_altura_no(b->esquerda),
                    a->altura) + 1;
    return b;
}

NODE *rodar_esquerda(NODE *a) {
    NODE *b = a->direita;
    a->direita = b->esquerda;
    b->esquerda = a;

    a->altura = max(avl_altura_no(a->esquerda),
                    avl_altura_no(a->direita)) + 1;
    b->altura = max(avl_altura_no(b->direita),
                    a->altura) + 1;
    return b;
}

NODE *rodar_esquerda_direita(NODE *a)   {
    a->esquerda = rodar_esquerda(a->esquerda);
    return rodar_direita(a);
}

NODE *rodar_direita_esquerda(NODE *a)   {
    a->direita = rodar_direita(a->direita);
    return rodar_esquerda(a);
}

static NODE *avl_inserir_no_e_rotacionar(NODE *raiz, GAME* game) {
    raiz = inserir_no(raiz, game);

    raiz->altura = max(avl_altura_no(raiz->esquerda),
                       avl_altura_no(raiz->direita)) + 1;

    raiz = selecionar_e_executar_rotacao(raiz, game);

    return raiz;
}

//TODO: resolver problema do item const
static NODE *inserir_no(NODE *raiz, GAME *game) {
    if (raiz == NULL) {
        raiz = avl_cria_no(game);
    }
    else if (ItemEhMaior(raiz,game)) {
        raiz->direita = avl_inserir_no_e_rotacionar(raiz->direita, game);
    }
    else if (ItemEhMenor(raiz, game)) {
        raiz->esquerda = avl_inserir_no_e_rotacionar(raiz->esquerda, game);
    }
    return raiz;
}

static NODE *selecionar_e_executar_rotacao(NODE *raiz, GAME* game) {
    if (DesbalanceamentoEhNegativo(raiz)) {
        if (ItemEhMaior(raiz->direita, game)) {
            raiz = rodar_esquerda(raiz);
        }
        else {
            raiz = rodar_direita_esquerda(raiz);
        }
    }

    if (DesbalanceamentoEhPositivo(raiz)) {
        if (ItemEhMenor(raiz->esquerda, game))
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);
    }
    return raiz;
}

static bool ItemEhMenor(const NODE *raiz, GAME* game) {
    if (return_year(game) != return_year(raiz->game))return return_year(game) < return_year(raiz->game);
    else return strlen(return_name(game)) < strlen(return_name(raiz->game));
}

static bool ItemEhMaior(const NODE *raiz, GAME* game) {
    if (return_year(game) != return_year(raiz->game))return return_year(game) > return_year(raiz->game);
    else return strlen(return_name(game)) > strlen(return_name(raiz->game));
}

static bool DesbalanceamentoEhPositivo(NODE *raiz) {
    return avl_altura_no(raiz->esquerda)
               - avl_altura_no(raiz->direita) == 2;
}

static bool DesbalanceamentoEhNegativo(NODE *raiz) {
    return avl_altura_no(raiz->esquerda)
               - avl_altura_no(raiz->direita) == -2;
}

boolean avl_inserir(AVL *arvore, GAME* game) {
    arvore->raiz = avl_inserir_no_e_rotacionar(arvore->raiz,game);
    return arvore->raiz != NULL;
}






