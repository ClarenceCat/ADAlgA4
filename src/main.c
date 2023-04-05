/**
 * @file main.c
 * @author Daniel Grew
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "assignment4.h"

int main(int argc, char **argv)
{
    // try to read the file
    int word_count = 0;
    Word *words = GetWordList("./bin/data_A4_Q1.txt", &word_count);

    printf("%s \n", words[370].str);

    SortWords(words, word_count);

    
    Tree *bst = GreedyBST(words, word_count);

    printf("Please input string to search: ");
    char *input = GetUserInput();

    double ave_searches = -1;
    int **bst_table = OptimalBST(words, word_count, &ave_searches);

    if(!bst_table)
    {
        free(input);
        DeleteTree(bst);
        free(words);
        return ERROR;
    }

    // convert table into Tree
    Tree *bst_optimal = ConstructTree(bst_table, word_count);

    if(!bst_optimal)
    {
        DeleteTable(bst_table, word_count + 1);
        free(input);
        DeleteTree(bst);
        free(words);
        return ERROR;
    }

    printf("Searching the tree constructed with Dynamic programming algorithm\n");
    SearchTree(bst_optimal->root, input, words);

    printf("\n");

    printf("Searching the tree constructed with the greedy algorithm \n");
    SearchTree(bst->root, input, words);
    

    free(input);
    DeleteTable(bst_table, word_count + 1);
    DeleteTree(bst_optimal);
    DeleteTree(bst);
    free(words);

    // ask for user to input filename
    printf("Please enter the file name containing the matrix data: ");
    char *matrix_file_str = GetUserInput();
    if(!matrix_file_str)
    {
        printf("Failed to read user input\n");
    }

    int dim = 0;
    int num_lines = 0;
    char **lines = ReadMatrixFile(matrix_file_str, &dim, &num_lines);

    free(matrix_file_str);

    if(!lines)
    {
        printf("Failed to read file\n");
        return ERROR;
    }

    int **matrix_1 = MatrixFromLines(lines, 0, dim, dim);
    if(!matrix_1)
    {
        printf("Failed to extract matrix from string array\n");
        DeleteStringArray(lines, num_lines);
        return ERROR;
    }

    int **matrix_2 = MatrixFromLines(lines, dim+1, num_lines, dim);
    if(!matrix_2)
    {
        printf("Failed to extract matrix from string array\n");
        DeleteMatrix(matrix_1, dim);
        DeleteStringArray(lines, num_lines);
        return ERROR;
    }

    DeleteStringArray(lines, num_lines);

    // call the perfect marriage function
    int **marriage = PerfectMarriage(matrix_1, matrix_2, dim);

    printf("Marriage Matrix: \n");
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            printf("%d ", marriage[i][j]);
        }
        printf("\n");
    }

    DeleteMatrix(matrix_1, dim);
    DeleteMatrix(matrix_2, dim);
    DeleteMatrix(marriage, dim);

    return 0;
}

/**
 * @brief Get the User Input 
 * 
 * @return char* 
 */
char *GetUserInput()
{
    char *input = malloc(sizeof(char) * MAX_INPUT);
    if(fgets(input, MAX_INPUT - 1, stdin) == NULL)
    {
        return NULL;
    }

    // remove trailing return if there is one
    int len = strlen(input);
    if(input[len-1] == NEW_LINE)
    {
        input[len-1] = NULL_TERM;
    }
    printf("\n");

    return input;
}