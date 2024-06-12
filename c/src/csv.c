#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "csv.h"
#include "matrix.h"

// Output results to a file.
void outputResults(int rows, int *a, int *b, int *c, char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Error opening file. Ensure its parent directory exists and you have permission to open it.\n");
        return;
    }
    fprintf(file, "----- A -----\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            fprintf(file, "%d,", M(a,rows,i,j));
        }
        fprintf(file, "\n");
    }
    fprintf(file, "----- B -----\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            fprintf(file, "%d,", M(b,rows,i,j));
        }
        fprintf(file, "\n");
    }
    fprintf(file, "----- RESULT -----\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            fprintf(file, "%d,", M(c,rows,i,j));
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

// Load a csv file containing pairs of matrices.
bool loadFile(int n, int size, int rows,
              int startMatrix, int endMatrix, int *matrixList,
              int *numPairs,
              char *fileName) {
    // open the file
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        return false;
    }
    // initialize variables for reading data
    bool readDone = false;
    int i = 0;
    int iter_i = 0;
    int matrixNum = 0;
    // * 2 to account for commas between each number
    // since there are n-1 commands, \0 still fits. but, \n doesn't, so +2 (in case \r\n)
    char line[rows * 2 + 2]; 
    // read data
    while (!readDone) {
        // read the next line
        if (fgets(line, sizeof(line), file) == NULL) {
            break;
        }
        // read the line data
        if (i == 0) {
            // header info, disregard
            i++;
        }
        else if (i == 1) {
            // matrix metadata
            // get number of pairs from metadata. disregard other data
            strtok(line, ",");
            strtok(NULL, ",");
            (*numPairs) = atoi(strtok(NULL, ","));
            i++;
        } else {
            if (line[0] == ',' || line[0] == '~') {
                // end of matrix. add it to the matrix list, then move on
                iter_i = 0;
                matrixNum++;
            } else if (line[0] == '#' || matrixNum > endMatrix) {
                // end of file or have finished reading the requested number of matrices
                readDone = true;
            } else if (matrixNum >= startMatrix) {
                // normal matrix data
                char *num = strtok(line, ",\r\n");
                int iter_j = 0;
                while (num != NULL) {
                    // insert data into matrix list
                    ML(matrixNum-startMatrix, iter_i, iter_j) = atoi(num);
                    // get next line
                    num = strtok(NULL, ",\r\n");
                    iter_j++;
                }
                iter_i++;
            } else {
                // we haven't yet reached the matrix we start loading from, so continue
            }
        }
    }
    // close the file
    fclose(file);
    return true;
}
