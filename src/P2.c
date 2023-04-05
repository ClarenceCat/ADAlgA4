/**
 * @file P2.c
 * @author Daniel Grew 0978547
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment4.h"

int ** PerfectMarriage(int **men, int **women, int dim)
{
    // check for matrices 
    if(!men || !women || dim < 0)
    {
        return NULL;
    }

    // set up free people
    int free_men = dim;

    // initialize matrix to return 
    int **ret_matrix = InitializeMatrix(dim);

    // initialize all values to 0
    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            ret_matrix[i][j] = 0;
        }
    }
    // loop until all men are taken
    while(free_men > 0)
    {
        // loop over all men
        for(int man_idx = 0; man_idx < dim; man_idx++)
        {
            // check if man is free
            int man_taken = 0;
            for(int i = 0; i < dim; i++)
            {
                if(ret_matrix[man_idx][i] == 1)
                {
                    man_taken = 1;
                    break;
                }
            }
            // if man is taken then continue the loop
            if(man_taken == 1)
            {
                continue;
            }
            
            // if man is not taken then loop through the people in the women matrix
            for(int attr_index = 0; attr_index < dim; attr_index++)
            {
                int woman_idx = men[man_idx][attr_index] - 1;

                // see if the woman is available
                int w_taken = -1;
                for(int w_avail = 0; w_avail < dim; w_avail++)
                {
                    if(ret_matrix[w_avail][woman_idx] == 1)
                    {
                        w_taken = w_avail;
                    }
                }
                
                // check if woman was available
                if(w_taken < 0)
                {
                    // set the ret matrix
                    ret_matrix[man_idx][woman_idx] = 1;
                    free_men--;
                    break;
                }

                // if not available, see if the index of current partner
                int new_partner = -1;
                int cur_partner = -1;
                for(int s = 0; s < dim; s++)
                {
                    if(women[woman_idx][s] - 1 == man_idx)
                    {
                        new_partner = s;
                    }
                    else if(women[woman_idx][s] - 1 == w_taken)
                    {
                        cur_partner = s;
                    }
                }

                // compare partner rankings - if new partner outranks old, replace
                if(new_partner < cur_partner)
                {
                    ret_matrix[w_taken][woman_idx] = 0;
                    ret_matrix[man_idx][woman_idx] = 1;
                    break;
                }
            }
        }
    }
    return ret_matrix;
}

