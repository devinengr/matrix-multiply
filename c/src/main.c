#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "matrix.h"
#include "test.h"
#include "csv.h"


// Get current time in seconds with nanosecond precision.
double curTime() {
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    // division by 1000000000.0 lets us merge nanoseconds with seconds
    return now.tv_sec + (now.tv_nsec / 1000000000.0);
}

// Output results.
void printResults(double t_s, double t_e,
                  int pairNumber, int size, int rows,
                  int *matrixList, int *result) {
    char fileName[40];
    sprintf(fileName, "results/%dx%d_pair%d.txt", rows, rows, pairNumber);
    printf("Time taken: %.9lf seconds\nWriting results to %s...\n", t_e - t_s, fileName);
    outputResults(rows, matrixList, matrixList + size, result, fileName);
}

// Run the brute force algorithm. Returns time elapsed.
void runBruteForce(int pairNumber, int size, int rows, int *matrixList, int *result) {
    // run brute force
    double t_s = curTime();
    matrixMultiplyBruteForce(rows, rows, rows,
                             matrixList, matrixList + size, result,
                             0, 0, 0, 0);
    double t_e = curTime();
    // output results
    printResults(t_s, t_e, pairNumber, size, rows, matrixList, result);
}

// Run Strassen's algorithm. Returns time elapsed.
void runStrassens(int pairNumber, int cutoff, int n, int size, int rows, int *matrixList, int *result) {
    // run strassen's algorithm
    double t_s = curTime();
    matrixMultiplyStrassens(cutoff, n,
                            rows, rows, rows,
                            matrixList, matrixList + size, result,
                            0, 0, 0, 0);
    double t_e = curTime();
    // output results
    printResults(t_s, t_e, pairNumber, size, rows, matrixList, result);
}

// Main function.
int main(int argc, char *argv[]) {
    // run tests if program is run with the test flag
    if (argc > 1) {
        if (strcmp("test", argv[1]) == 0) {
            testRun();
            return 0;
        }
    }
    // print a line
    printf("-----\n");
    // get values
    int n = 0;
    printf("Please specify n: ");
    scanf("%d", &n);
    int rows = 1 << n; // get 2^n fast
    int size = rows * rows;
    int startMatrix = 0;
    int endMatrix = 1;
    // allocate space for matrices
    // both startMatrix and endMatrix are inclusive, so add 1
    int numMatrices = (endMatrix - startMatrix) + 1;
    int *matrixList = malloc(sizeof(int) * size * numMatrices);
    int *result = malloc(sizeof(int) * size);
    // get filename. Add extra space for longer names
    char fileName[40];
    sprintf(fileName, "res/n%d.csv", n);
    // print how much memory was allocated
    printf("Initial memory allocation: %lld MB\n",
                ((sizeof(int) * size * numMatrices)
               + (sizeof(int) * size))
               / 1000000 /* convert to MB */);
    // run user-specified number of multiplications up to # of pairs in file
    int numPairsUser = 0;
    int numPairsFile = 0;
    printf("Please specify the number of pairs to multiply: ");
    scanf("%d", &numPairsUser);
    // run user-specified algorithm
    int algorithm = 0;
    printf("\t[0] for Brute Force\n\t[1] for Strassen's\n\t[2] for Both\nPlease specify the algorithm: ");
    scanf("%d", &algorithm);
    // check that the user specified a correct algorithm
    if (algorithm != 0 && algorithm != 1 && algorithm != 2) {
        printf("Correct algorithm unspecified. Defaulting to Brute Force.\n");
        algorithm = 0;
    }
    // get cutoff point to switch to brute force if algorithm is Both
    int cutoff = -1;
    if (algorithm == 2) {
        printf("Please specify a cutoff to switch to Brute Force: ");
        scanf("%d", &cutoff);
    }
    // print a line
    printf("-----\n");
    // run the algorithm user-specified number of times
    for (int i = 0; i < numPairsUser; i++) {
        // load file. i * 2 since there are 2 pairs of matrices per run
        startMatrix = i * 2;
        endMatrix = startMatrix + 1;
        printf("Loading pair %d of %d-by-%d matrices...\n", i, rows, rows);
        // check that the file exists
        if (!loadFile(n, size, rows, startMatrix, endMatrix, matrixList, &numPairsFile, fileName)) {
            printf("File does not exist.\n");
            break;
        }
        // check user input validity
        if (numPairsUser > numPairsFile) {
            printf("The file doesn't have %d pairs. It only has %d.\n", numPairsUser, numPairsFile);
            break;
        }
        // run matrix multiplication
        if (algorithm == 0) {
            printf("Running Brute Force on pair %d...\n", i);
            runBruteForce(i, size, rows, matrixList, result);
        } else if (algorithm == 1) {
            printf("Running Strassen's on pair %d...\n", i);
            runStrassens(i, cutoff, n, size, rows, matrixList, result);
        } else {
            printf("Running Both on pair %d with cutoff %d...\n", i, cutoff);
            runStrassens(i, cutoff, n, size, rows, matrixList, result);
        }
        // make output look nice
        printf("-----\n");
    }
    // print finished
    printf("FINISHED\n-----\n");
    // free matrices
    free(matrixList);
    free(result);
    return 0;
}
