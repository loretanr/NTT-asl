/**
 * Inverse Number Theoretic Transform
 * Computes the inverse NTT of an image provided
 * Outputs image result.
 * NTTW Inverse FNTT 2D Program
 * \file intt.c
 * \brief Inverse FNTT 2D Program for the NTTW C Library.
 *
 * This file is part of NTTW Library.
 *
 * NTTW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NTTW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with NTTW.  If not, see <http://www.gnu.org/licenses/>.
 *
 * \author Shekhar S. Chandra, 2008-9
*/
//NTTW
#include "timing.h"
#include "prime.h"
#include "number32.h"
#include "image.h"

///Global
const int totalRows = 1000;
const int totalCols = 10;
const char *filename = "primes.csv";

int main(int argc, char *argv[])
{
    nttw_integer *image, *result, *primes, root = 0, modulus = 0, proot = 0;
    int rows, cols, binaryFile = FALSE, dyadicTransform = TRUE;
    unsigned long long duration = 0;

    printf(">| Inverse Number TT Program.\n");
    printf(">| Copyright Shekhar Chandra, 2009\n");
    printf(">| Machine Integer Size of %lu bits\n",BITS);
#if defined (NTTW_64)
    printf(">| Using 64-bit mode.\n");
#else
    printf(">| Using 32-bit mode.\n");
#endif

    if(argc != 3)
    {
        printf(">| Usage: %s <filename> <output>\n",argv[0]);
        printf(">| filename is loaded and transformed to produce output.\n");
        printf(">| Files should be PGM formats.\n");
        return EXIT_FAILURE;
    }

    //--------------------------------------------
    ///Load Image
    if(!readPGM(&image,&rows,&cols,argv[1],binaryFile))
    {
        fprintf(stderr,">| Error Opening File: %s\n",argv[1]);
        return EXIT_FAILURE;
    }
    if(rows % 2 == 1) ///Odd #rows then assume prime-length
    {
        dyadicTransform = FALSE;
        ///Read primes list
        if( !readCSV(&primes,totalRows,totalCols,filename) )
        {
            printf(">| Could not open primes file.\n");
            exit(EXIT_FAILURE);
        }
        ///Compute roots
        root = findFirstPrimitiveRoot(rows);
        modulus = findAlternatePrime(primes,totalRows*totalCols,rows);
        proot = findFirstPrimitiveRoot(modulus);
        printf(">| Root: %u, Prime': %u, Primitive Root: %u.\n",root,modulus,proot);
    }

    ///Output parameters to be used
    result = array_1D(rows*cols);
    //init_1D(result,rows*cols,0);

    //--------------------------------------------
    ///Fast FRT
    fprintf(stderr,">| Transforming... ");
    START_TIMER;

    if(dyadicTransform)
        fntt_2D(image,result,rows,NTTW_INVERSE);
    else
        fntt_2D_prime(image,result,rows,root,modulus,proot,NTTW_INVERSE,TRUE);

    STOP_TIMER;
    duration = MICROSECONDS_ELAPSED;
    fprintf(stderr,"Done. Time: %llu usecs.\n", duration);

    ///Save Result
    writePGM(result,rows,cols,255,argv[2],binaryFile);

    //--------------------------------------------
    ///Cleanup
    printf(">| Operation Complete\n");
    free_array(image);
    free_array(result);
    if(!dyadicTransform)
        free_array(primes);

    return EXIT_SUCCESS;
}
