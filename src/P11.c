/**
 * @file P11.c
 * @author Daniel Grew 0978547
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "assignment4.h"

int **OptimalBST(Word *words, int len, double *max_comp)
{
    // we want to initialize a two dimensional array to use as the average number table
    // rows: from 0 -> len - 1
    // cols: from 1 -> len (array from 1 -> len - 1)
    int ** min_root_table = InitializeRootTable(len);
    double ** prob_table = InitializeProbTable(len);

    // initialize the prob table
    for(int init_idx = 0; init_idx < len; init_idx++)
    {
        prob_table[init_idx][init_idx+1] = words[init_idx].prob;
        min_root_table[init_idx][init_idx+1] = init_idx + 1;
    }

    // diagonal count
    for(int d = 1; d <= len; d++)
    {
        for(int i = 1; i <= len - d; i++)
        {
            int j = i + d;
            double min_val = -1;
            int k_min = -1;
            for(int k = i; k <= j; k++)
            {
                if(prob_table[i - 1][k - 1] + prob_table[k][j] < min_val || min_val < 0)
                {
                    min_val = prob_table[i - 1][k - 1] + prob_table[k][j];
                    k_min = k - 1;
                }
            }
            min_root_table[i - 1][j] = k_min;
            double sum = words[i-1].prob;
            for(int sum_idx = i; sum_idx <= j; sum_idx++)
            {
                sum += words[sum_idx - 1].prob;
            }
            prob_table[i-1][j] = min_val + sum;
        }
    }

    *max_comp = prob_table[0][len];
    DeleteProbTable(prob_table, len + 1);

    return min_root_table;
}


Tree *ConstructTree(int **table, int len)
{
    if(!table)
    {
        return NULL;
    }

    Tree *new_tree = InitializeTree();

    // dig down and load the tree
    new_tree->root = TreeConstructUsingTable(table, 0, len);

    return new_tree;
}

Node *TreeConstructUsingTable(int **table, int min, int max)
{
    if(!table)
    {
        return NULL;
    }
    if(min >= max)
    {
        return NULL;
    }

    // get the index of the node
    int word_idx = table[min][max];
    Node *new_node = InitializeNode(word_idx);

    // recursively call function to load the rest of the table
    new_node->left = TreeConstructUsingTable(table, min, word_idx - 1);
    new_node->right = TreeConstructUsingTable(table, word_idx + 1, max);

    return new_node;
}


/**
 * @brief Initializes a table of ints with the diagonal set to 0
 * 
 * @param len 
 * @return int** 
 */
int ** InitializeRootTable(int len)
{
    if(len < 0)
    {
        return NULL;
    }

    // allocate memory
    int **new_table = malloc(sizeof(int *) * (len + 1));

    if(new_table == NULL)
    {
        return NULL;
    }

    for(int i = 0; i < len + 1; i++)
    {
        new_table[i] = malloc(sizeof(int) * (len + 1));
        // make sure alloc worked
        if(new_table[i] == NULL)
        {
            // loop through the already allocated array data and free the memory
            for(int m = 0; m < i; m++)
            {
                free(new_table[i]);
            }
            // free the table
            free(new_table);
            return NULL;
        }
    }

    // set entire matrix to 0
    for(int m = 0; m < len + 1; m++)
    {
        for(int s = 0; s < len + 1; s++)
        {
            new_table[m][s] = 0;
        }
    }

    // loop through the table and initialize the diagonal
    for(int j = 0; j <= len; j++)
    {
        new_table[j][j] = 0;
    }

    return new_table;
}


/**
 * @brief Initializes a table of ints with the diagonal set to 0
 * 
 * @param len 
 * @return int** 
 */
double ** InitializeProbTable(int len)
{
    if(len < 0)
    {
        return NULL;
    }

    // allocate memory
    double **new_table = malloc(sizeof(double *) * (len + 1));

    if(new_table == NULL)
    {
        return NULL;
    }

    for(int i = 0; i < len + 1; i++)
    {
        new_table[i] = malloc(sizeof(double) * (len + 1));
        // make sure alloc worked
        if(new_table[i] == NULL)
        {
            // loop through the already allocated array data and free the memory
            for(int m = 0; m < i; m++)
            {
                free(new_table[i]);
            }
            // free the table
            free(new_table);
            return NULL;
        }
    }

    // set entire matrix to 0
    for(int m = 0; m < len + 1; m++)
    {
        for(int s = 0; s < len + 1; s++)
        {
            new_table[m][s] = 0;
        }
    }

    // loop through the table and initialize the diagonal
    for(int j = 0; j <= len; j++)
    {
        new_table[j][j] = 0;
    }

    return new_table;
}

/**
 * @brief Frees all elements in a table
 * 
 * @param table 
 * @param num_rows 
 */
void DeleteTable(int **table, int num_rows)
{
    if(!table || num_rows < 0)
    {
        return;
    }
    // loop through the rows and free the data at each row
    for(int x = 0; x < num_rows; x++)
    {
        free(table[x]);
    }

    // free the table
    free(table);
}

void DeleteProbTable(double **table, int num_rows)
{
    if(!table || num_rows < 0)
    {
        return;
    }
    // loop through the rows and free the data at each row
    for(int x = 0; x < num_rows; x++)
    {
        free(table[x]);
    }

    // free the table
    free(table);
}
