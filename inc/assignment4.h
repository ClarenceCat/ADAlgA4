/**
 * @file assignment4.h
 * @author Daniel Grew
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_WORD_LEN 100
#define MAX_LINE_LEN 100
#define MAX_NUM_LEN 10
#define NUM_WORDS 2045
#define READ "r"
#define SPACE ' '
#define NEW_LINE '\n'
#define NULL_TERM '\0';
#define FILE_CHAR_1 '\xef'
#define FILE_CHAR_2 '\xbb'
#define FILE_CHAR_3 '\xbf'

#define FOUND 1
#define NOT_FOUND 0
#define EMPTY_STR ""
#define ERROR -1

#define MAX_INPUT 100

typedef struct textword 
{
    char str[NUM_WORDS];
    int freq;
    double prob;
} Word;

typedef struct nodestruct 
{
    int index;
    struct nodestruct *left;
    struct nodestruct *right;
}Node;

typedef struct treestruct
{
    Node *root;
}Tree;


Word *GetWordList(char *filename, int *len);
void SortWords(Word *words, int len);
void Merge(Word *lower, int lower_len, Word *upper, int upper_len, Word *array, int array_len);
void CopyArray(Word *dest, Word *src, int start, int end);

char ** ReadMatrixFile(char *filename, int *dim, int *line_count);
void DeleteStringArray(char **arr, int len);
int **InitializeMatrix(int dim);
int **MatrixFromLines(char **lines, int start, int end, int dim);
void DeleteMatrix(int **matrix, int n);

int SearchTree(Node *node, char *key, Word *words);
Tree *InitializeTree();
Node *InitializeNode(int index);
void DeleteSubtree(Node *subtree_root);
void DeleteTree(Tree *tree);

int **OptimalBST(Word *words, int len, double *max_comp);
int ** InitializeRootTable(int len);
void DeleteProbTable(double **table, int num_rows);
double ** InitializeProbTable(int len);
void DeleteTable(int **table, int num_rows);


Tree *GreedyBST(Word *words, int len);
Node *GreedyBuildTree(Word *words, int start_idx, int end_idx);

char *GetUserInput();

void PrintTree(Node *t, Word *words);

int CountFileLines(char *filename);

int ** PerfectMarriage(int **men, int **women, int dim);

Tree *ConstructTree(int **table, int len);
Node *TreeConstructUsingTable(int **table, int min, int max);


