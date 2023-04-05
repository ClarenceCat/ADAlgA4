/**
 * @file tree.c
 * @author Daniel Grew 0978547
 * @brief 
 * @version 0.1
 * @date 2022-03-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "assignment4.h"

/**
 * @brief Initializes an empty tree structure
 * 
 * @return Tree* 
 */
Tree *InitializeTree()
{
    Tree *new_tree = malloc(sizeof(Tree));

    if(!new_tree)
    {
        return NULL;
    }

    new_tree->root = NULL;

    return new_tree;
}

/**
 * @brief Initializes an empty node struct with index set to index
 * 
 * @return Node* 
 */
Node *InitializeNode(int index)
{
    Node *new_node = malloc(sizeof(Node));
    if(!new_node)
    {
        return NULL;
    }
    new_node->index = index;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/**
 * @brief Deletes a tree struct freeing all nodes
 * 
 * @param tree 
 */
void DeleteTree(Tree *tree)
{
    if(!tree)
    {
        return;
    }

    // recursively call remove node until
    DeleteSubtree(tree->root);

    // free the tree structure itself
    free(tree);
}

/**
 * @brief Recursively frees nodes
 * 
 * @param subtree_root 
 */
void DeleteSubtree(Node *subtree_root)
{
    if(subtree_root == NULL)
    {
        return;
    }
    // recursively call delete subtree to free all nodes until a NULL is reached 
    DeleteSubtree(subtree_root->left);
    DeleteSubtree(subtree_root->right);

    free(subtree_root);
}

/**
 * @brief Recursively searches the tree for a key word
 * 
 * @param node 
 * @param key 
 * @param words 
 * @return int 
 */
int SearchTree(Node *node, char *key, Word *words)
{
    if(!key || !words)
    {
        return NOT_FOUND;
    }

    // check the current node is null
    if(node == NULL)
    {
        printf("not found\n");
        return NOT_FOUND;
    }

    int idx = node->index;
    printf("Compared with \"%s\" (%f), ", words[idx].str, words[idx].prob);


    if(strcmp(key, words[idx].str) == 0)
    {
        printf("found.\n");
        return FOUND;
    }
    else if(strcmp(key, words[idx].str) < 0)
    {
        printf("Go Left.\n");
        return SearchTree(node->left, key, words);
    }
    else 
    {
        printf("Go Right.\n");
        return SearchTree(node->right, key, words);
    }
}


void PrintTree(Node *t, Word *words)
{
    if(t == NULL)
    {
        return;
    }

    PrintTree(t->left, words);
    PrintTree(t->right, words);

    FILE *f = fopen("bin/check.txt", "a");
    fprintf(f, "%s\n", words[t->index].str);
    fclose(f);
}
