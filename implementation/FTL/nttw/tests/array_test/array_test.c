/**
 * NTTW Array Test Program
 * \file array_test.c
 * \brief Array Test Program for the NTTW C Library.
 *
 * This file is part of NTTW Library.
 *
 * NTTW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * DGV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with NTTW.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Shekhar S. Chandra, 2008-9
*/
#include <stdio.h>

#include "array.h"

int main(int argc, char *argv[])
{
    nttw_integer *data;
    size_t j, N = 0; //Use size_t instead of int for portability

    printf(">| Array Test\n");
    printf(">| Copyright Shekhar Chandra, 2009\n");
    printf(">| Machine Integer Size of %u bits\n",BITS);
    printf(">| Memory Alignment at %u bytes\n",ALIGNOF(data));
    if(argc != 2)
    {
        printf(">| %s <n>\n",argv[0]);
        printf(">| Allocates, Prints and Deallocates array of size n\n");
        return EXIT_FAILURE;
    }
    N = atoi(argv[1]);

    //-----------------------------------------
    printf(">| Allocating memory\n");
    data = array_1D(N);

    printf(">| Data: \n");
    for(j = 0; j < N; j ++)
    {
        data[j] = 1 + (int)j;
        printf(FORMAT_CSVOUTPUT_STR,data[j]);
    }
    printf("\n");

    //-----------------------------------------
    printf(">| Deallocating memory\n");
    free_array(data);
    printf(">| Operation Complete\n");
    return EXIT_SUCCESS;
}
