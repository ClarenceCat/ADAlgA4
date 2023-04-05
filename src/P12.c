/**
 * @file P12.c
 * @author Daniel Grew 0978547
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment4.h"

/**
 * @brief Uses the greedy algorithm to construct a tree
 * 
 * @param words 
 * @param len 
 * @return Tree* 
 */
Tree *GreedyBST(Word *words, int len)
{
    // check that words is not null
    if(!words)
    {
        return NULL;
    }

    // initialize the tree
    Tree *bst = InitializeTree();
    if(!bst)
    {
        return NULL;
    }

    // recursively build tree
    bst->root = GreedyBuildTree(words, 0, len);

    if(!bst->root)
    {
        DeleteTree(bst);
        return NULL;
    }

    return bst;
}

/**
 * @brief Recursively builds tree
 * 
 * @param words 
 * @param start_idx 
 * @param end_idx 
 * @return Node* 
 */
Node *GreedyBuildTree(Word *words, int start_idx, int end_idx)
{
    if(start_idx > end_idx)
    {
        return NULL;
    }
    if(start_idx == end_idx)
    {
        // return InitializeNode(start_idx);
        return NULL;
    }

    int idx = start_idx;
    double greatest_freq = 0;
    for(int i = start_idx; i < end_idx; i++)
    {
        if(words[i].prob > greatest_freq)
        {
            greatest_freq = words[i].prob;
            idx = i;
        }
    }

    // recursively call the function to build the left and right subtrees subtrees
    Node *root = InitializeNode(idx);
    root->left = GreedyBuildTree(words, start_idx, idx);
    root->right = GreedyBuildTree(words, idx+1, end_idx);

    return root;
}

