/**
 * @file filehandler.c
 * @author Daniel Grew 0978547
 * @brief This file contains functions meant to parse the files for the assignment
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "assignment4.h"

/**
 * @brief Extract the list of Words from the text document 
 * 
 * @param filename 
 * @return Word* 
 */
Word *GetWordList(char *filename, int *len)
{
    if(!filename)
    {
        return NULL;
    }

    // allocate space for the words to be extracted and stored 
    Word *words = malloc(sizeof(Word) * NUM_WORDS);

    // open the file
    FILE *file = fopen(filename, READ);
    if(!file)
    {
        free(words);
        return NULL;
    }

    // loop over the letters in the words to extract the words into the array
    int idx = 0;
    int word_idx = 0;
    char word_buff[MAX_WORD_LEN];
    // clear the buffer string
    for(int j = 0; j < MAX_WORD_LEN; j++)
    {
        word_buff[j] = '\0';
    }
    char c = 0;
    c = fgetc(file);

    while(c != EOF)
    {
        // check if a space has been reached
        if(c == SPACE || c == NEW_LINE || c == FILE_CHAR_1 || c == FILE_CHAR_2 || c == FILE_CHAR_3)
        {
            // check if wordbuffer is not empty
            if(strlen(word_buff) != 0)
            {
                // search for the string in the array of words
                int found = NOT_FOUND;
                for(int i = 0; i < idx; i++)
                {
                    if(strcmp(word_buff, words[i].str) == 0)
                    {
                        words[i].freq++;
                        words[i].prob = words[i].freq / (double)NUM_WORDS;
                        found = FOUND;
                        break;
                    }
                }
                // if the string is not found in the array already, then add it to the index and increase the index count
                if(found == NOT_FOUND)
                {
                    strcpy(words[idx].str, word_buff);
                    words[idx].freq++;
                    words[idx].prob = 1/(double)NUM_WORDS;
                    idx++;
                }

                // clear the buffer string
                for(int j = 0; j < MAX_WORD_LEN; j++)
                {
                    word_buff[j] = '\0';
                }
            }
            word_idx = 0;
            c = fgetc(file);
            continue;
        }

        // if a space hasn't been reached, then add the character to the string of the word at the current index value
        word_buff[word_idx] = c;
        word_idx++;
        c = fgetc(file);
    }

    fclose(file);
    *len = idx;
    return words;
}

/**
 * @brief Uses mergesort to sort the words in the array 
 * 
 * @param words 
 * @param len 
 */
void SortWords(Word *words, int len)
{
    if(!words)
    {
        return;
    }
    // check base case
    if(len <= 1)
    {
        return;
    }
    // calculate the midpoint
    int mid = floor(len/2);

    // allocate size for two arrays 
    Word *lower = malloc(sizeof(Word) * mid);
    Word *upper = malloc(sizeof(Word) * (len - mid));

    // copy the contents of array into lower and upper
    CopyArray(lower, words, 0, mid);
    CopyArray(upper, words, mid, len);

    SortWords(lower, mid);
    SortWords(upper, (len - mid));

    Merge(lower, mid, upper, (len - mid), words, len);

    // free the arrays
    free(lower);
    free(upper);
}


/**
 * @brief Merges two sorted arrays of words 
 * 
 * @param lower 
 * @param lower_len 
 * @param upper 
 * @param upper_len 
 * @param array 
 * @param array_len 
 */
void Merge(Word *lower, int lower_len, Word *upper, int upper_len, Word *array, int array_len)
{
    if(!lower || !upper || !array)
    {
        return;
    }
    int i = 0;
    int j = 0;
    int k = 0;

    // use strcmp to sort the words
    while(i < lower_len && j < upper_len)
    {
        // if the lower array element at index i is less than element in upper at index j
        if(strcmp(lower[i].str, upper[j].str) < 0)
        {
            array[k] = lower[i];
            i++;
        }
        else
        {
            // if the lower index is of a greater value than the value in the upper array
            array[k] = upper[j];
            j++;
        }
        k++;
    }
    // if the end of the sorted lower array has been reached
    if(i == lower_len)
    {
        // add rest of sorted upper index to the end of the sorted array
        for(int index = j; index < upper_len; index++)
        {
            array[k] = upper[index];
            k++;
        }
    }
    else
    {
        array[k] = lower[i];
        i++;
        k++;
        for(int index = i; index < lower_len; index++)
        {
            array[k] = lower[index];
            k++;
        }
    }
}

/**
 * @brief Copy an array from a destination to a source
 * 
 * @param dest 
 * @param src 
 * @param start 
 * @param end 
 */
void CopyArray(Word *dest, Word *src, int start, int end)
{
    if(!dest || !src)
    {
        return;
    }

    int index = 0;
    for(int i = start; i < end; i++)
    {
        dest[index] = src[i];
        index++;
    }
}


char ** ReadMatrixFile(char *filename, int *dim, int *line_count)
{
    if(!filename)
    {
        return NULL;
    }

    int num_lines = CountFileLines(filename);
    if(num_lines == ERROR)
    {
        return NULL;
    }

    // open file
    FILE *file = fopen(filename, READ);
    if(!file)
    {
        return NULL;
    }

    // get the first line of the file
    char num_buff[MAX_NUM_LEN];
    fgets(num_buff, MAX_NUM_LEN, file);

    // get the dimension of the array
    int dimension = -1;
    dimension = atoi(num_buff);

    // initialize the array
    char ** lines = malloc(sizeof(char *) * num_lines);

    // loop through the array and add the 
    char buff[MAX_LINE_LEN];
    int idx = 0;
    while(fgets(buff, MAX_LINE_LEN, file) && idx <num_lines)
    {
        // allocate space and copy the line
        lines[idx] = malloc(sizeof(char) * strlen(buff));
        strcpy(lines[idx], buff);
        idx++;
    }
    // close file
    fclose(file);
    *dim = dimension;
    *line_count = num_lines;
    return lines;
}

int **MatrixFromLines(char **lines, int start, int end, int dim)
{
    if(!lines || dim < 3 || dim > 4)
    {
        return NULL;
    }

    // initialize a matrix
    int **matrix = InitializeMatrix(dim);

    // construct format string
    char format[MAX_LINE_LEN];
    strcpy(format, "");

    int idx = 0;

    for(int i = start; i < start + dim; i++)
    {
        if(dim == 3)
        {
            sscanf(lines[i], "%d %d %d", &matrix[idx][0], &matrix[idx][1], &matrix[idx][2]);
        }
        else 
        {
            sscanf(lines[i], "%d %d %d %d", &matrix[idx][0], &matrix[idx][1], &matrix[idx][2], &matrix[idx][3]);
        }
        idx++;
    }

    return matrix;
}

/**
 * @brief Frees matrix
 * 
 * @param matrix 
 * @param n 
 */
void DeleteMatrix(int **matrix, int n)
{
    if(!matrix)
    {
        return;
    }
    for(int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

/**
 * @brief frees a list of strings 
 * 
 * @param arr 
 * @param len 
 */
void DeleteStringArray(char **arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        free(arr[i]);
    }

    free(arr);
}

int **InitializeMatrix(int dim)
{
    if(dim < 0)
    {
        return NULL;
    }

    int **matrix = malloc(sizeof(int *) * dim);

    // initialize the int arrays at each row
    for(int i = 0; i < dim; i++)
    {
        matrix[i] = malloc(sizeof(int) * dim);
    }

    return matrix;
}

/**
 * @brief Gets the number of lines in a file
 * 
 * @param filename 
 * @return int 
 */
int CountFileLines(char *filename)
{
    if(!filename)
    {
        return ERROR;
    }

    FILE *file = fopen(filename, READ);
    if(!file)
    {
        return ERROR;
    }

    int count = 0;
    char buff[MAX_LINE_LEN];
    while(fgets(buff, MAX_LINE_LEN, file))
    {
        count++;
    }

    fclose(file);
    return count;
}
