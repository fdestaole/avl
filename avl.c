#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "avl.h"
#include "game.h"

typedef struct node_st NODE;

void pre_order_recursion(NODE *root);
void in_order_recursion(NODE *root);
void post_order_recursion(NODE *root);
static void avl_delete_aux(NODE **root);
static NODE *avl_insert_node_and_rotate(NODE *root, GAME *game);

static bool negative_unbalance(NODE *root);

static bool positive_unbalance(NODE *root);

static bool IsBigger(const NODE *root, GAME *game);

static bool IsSmaller(const NODE *root, GAME *game);

static NODE *select_and_rotate(NODE *root, GAME *game);

static NODE *insert_node(NODE *root, GAME *game);

struct node_st
{
    GAME *game;
    NODE *right;
    NODE *left;
    int height;
};

struct avl
{
    NODE *root;
    int depth;
};

void binary_tree_pre_order(AVL *tree)
{
    pre_order_recursion(tree->root);
}
void pre_order_recursion(NODE *root)
{
    if (root != NULL)
    {
        printf("%s\n", return_name(root->game));
        pre_order_recursion(root->left);
        pre_order_recursion(root->right);
    }
}

void binary_tree_in_order(AVL *tree)
{
    in_order_recursion(tree->root);
}
void in_order_recursion(NODE *root)
{
    if (root != NULL)
    {
        in_order_recursion(root->left);
        printf("%s\n", return_name(root->game));
        in_order_recursion(root->right);
    }
}

void binary_tree_post_order(AVL *tree)
{
    post_order_recursion(tree->root);
}
void post_order_recursion(NODE *root)
{
    if (root != NULL)
    {
        post_order_recursion(root->left);
        post_order_recursion(root->right);
        printf("%s\n", return_name(root->game));
    }
}

void print_avl(AVL *tree, int option)
{
    switch (option)
    {
    case 1:
        binary_tree_pre_order(tree);
        break;
    case 2:
        binary_tree_in_order(tree);
        break;
    case 3:
        binary_tree_post_order(tree);
        break;
    default:
        printf("Invalid option!\n");
        break;
    }
}

AVL *avl_create()
{
    AVL *tree = (AVL *)malloc(sizeof(AVL));
    if (tree != NULL)
    {
        tree->root = NULL;
        tree->depth = -1;
    }
    return tree;
}

static void avl_delete_aux(NODE **root)
{
    if (*root != NULL)
    {
        avl_delete_aux(&((*root)->left));
        avl_delete_aux(&((*root)->right));
        free_game(&(*root)->game);
        free(*root);
    }
}

void avl_delete(AVL **tree)
{
    avl_delete_aux(&(*tree)->root);
    free(*tree);
    *tree = NULL;
}

int avl_height_node(NODE *root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
    {
        return root->height;
    }
}

NODE *avl_create_node(GAME *game)
{
    NODE *new = (NODE *)malloc(sizeof(NODE));
    if (new != NULL)
    {
        new->height = 0;
        new->right = NULL;
        new->left = NULL;
        new->game = game;
    }
    return new;
}

NODE *rotate_right(NODE *a)
{
    NODE *b = a->left;
    a->left = b->right;
    b->right = a;

    a->height = max(avl_height_node(a->left),
                    avl_height_node(a->right)) +
                1;
    b->height = max(avl_height_node(b->left),
                    a->height) +
                1;
    return b;
}

NODE *rotate_left(NODE *a)
{
    NODE *b = a->right;
    a->right = b->left;
    b->left = a;

    a->height = max(avl_height_node(a->left),
                    avl_height_node(a->right)) +
                1;
    b->height = max(avl_height_node(b->right),
                    a->height) +
                1;
    return b;
}

NODE *rotate_left_right(NODE *a)
{
    a->left = rotate_left(a->left);
    return rotate_right(a);
}

NODE *rotate_right_left(NODE *a)
{
    a->right = rotate_right(a->right);
    return rotate_left(a);
}

static NODE *avl_insert_node_and_rotate(NODE *root, GAME *game)
{
    root = insert_node(root, game);

    root->height = max(avl_height_node(root->left),
                       avl_height_node(root->right)) +
                   1;

    root = select_and_rotate(root, game);

    return root;
}

static NODE *insert_node(NODE *root, GAME *game)
{
    if (root == NULL)
    {
        root = avl_create_node(game);
    }
    else if (IsBigger(root, game))
    {
        root->right = avl_insert_node_and_rotate(root->right, game);
    }
    else if (IsSmaller(root, game))
    {
        root->left = avl_insert_node_and_rotate(root->left, game);
    }
    return root;
}

static NODE *select_and_rotate(NODE *root, GAME *game)
{
    if (negative_unbalance(root))
    {
        if (IsBigger(root->right, game))
        {
            root = rotate_left(root);
        }
        else
        {
            root = rotate_right_left(root);
        }
    }

    if (positive_unbalance(root))
    {
        if (IsSmaller(root->left, game))
        {
            root = rotate_right(root);
        }
        else
        {
            root = rotate_left_right(root);
        }
    }
    return root;
}

static bool IsSmaller(const NODE *root, GAME *game)
{
    if (return_year(game) != return_year(root->game))
        return return_year(game) < return_year(root->game);
    else
        return strcmp(return_name(game), return_name(root->game)) < 0;
}

static bool IsBigger(const NODE *root, GAME *game)
{
    if (return_year(game) != return_year(root->game))
        return return_year(game) > return_year(root->game);
    else
        return strcmp(return_name(game), return_name(root->game)) > 0;
}

static bool positive_unbalance(NODE *root)
{
    return avl_height_node(root->left) - avl_height_node(root->right) == 2;
}

static bool negative_unbalance(NODE *root)
{
    return avl_height_node(root->left) - avl_height_node(root->right) == -2;
}

bool avl_insert(AVL *tree, GAME *game)
{
    tree->root = avl_insert_node_and_rotate(tree->root, game);
    return tree->root != NULL;
}

static void print2DUtil(NODE *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 8;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = 8; i < space; i++)
        printf(" ");
    printf("%d %c\n", return_year(root->game), return_name(root->game)[0]);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void avl_print_2d(AVL *tree)
{
    // Pass initial space count as 0
    print2DUtil(tree->root, 0);
}
