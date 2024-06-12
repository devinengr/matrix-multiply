#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include "matrix.h"
#include "csv.h"


//
// Assert functions
//


// Assert if 2 matrices have equal content.
bool assertMatrix(int size, int *a, int *b) {
    for (int i = 0; i < size; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

// Assert if 2 integers are equal.
bool assertInt(int expected, int actual) {
    return expected == actual;
}


//
// Test functions
//


// Test that all data in the CSV file is parsed.
bool testCSV() {
    bool passed = true;
    // smaller n
    {
        int n = 5;
        int rows = 1 << n;
        int size = rows * rows;
        int startMatrix = 0;
        int endMatrix = 1;
        // both startMatrix and endMatrix are inclusive, so add 1
        int numMatrices = (endMatrix - startMatrix) + 1;
        int *matrixList = malloc(sizeof(int) * size * numMatrices);
        int numPairs = 0;
        loadFile(n, size, rows, startMatrix, endMatrix, matrixList, &numPairs, "res/n5.csv");
        // asserts
        if (!assertInt(3, numPairs))                passed = false;
        if (!assertInt(2, ML(0, 0, 0)))             passed = false;
        if (!assertInt(4, ML(0, 0, rows-1)))        passed = false;
        if (!assertInt(1, ML(0, rows-1, 0)))        passed = false;
        if (!assertInt(8, ML(0, rows-1, rows-1)))   passed = false;
        if (!assertInt(3, ML(1, 0, 0)))             passed = false;
        if (!assertInt(8, ML(1, 0, rows-1)))        passed = false;
        if (!assertInt(4, ML(1, rows-1, 0)))        passed = false;
        if (!assertInt(5, ML(1, rows-1, rows-1)))   passed = false;
        // free memory
        free(matrixList);
    }
    // larger n
    {
        int n = 9;
        int rows = 1 << n;
        int size = rows * rows;
        int startMatrix = 0;
        int endMatrix = 1;
        // both startMatrix and endMatrix are inclusive, so add 1
        int numMatrices = (endMatrix - startMatrix) + 1;
        int *matrixList = malloc(sizeof(int) * size * numMatrices);
        int numPairs = 0;
        loadFile(n, size, rows, startMatrix, endMatrix, matrixList, &numPairs, "res/n9.csv");
        // asserts
        if (!assertInt(1, numPairs))                passed = false;
        if (!assertInt(2, ML(0, 0, 0)))             passed = false;
        if (!assertInt(6, ML(0, 0, rows-1)))        passed = false;
        if (!assertInt(4, ML(0, rows-1, 0)))        passed = false;
        if (!assertInt(0, ML(0, rows-1, rows-1)))   passed = false;
        if (!assertInt(5, ML(1, 0, 0)))             passed = false;
        if (!assertInt(7, ML(1, 0, rows-1)))        passed = false;
        if (!assertInt(4, ML(1, rows-1, 0)))        passed = false;
        if (!assertInt(2, ML(1, rows-1, rows-1)))   passed = false;
        // free memory
        free(matrixList);
    }
    // test reading a pair starting from the middle of the file
    {
        int n = 5;
        int rows = 1 << n;
        int size = rows * rows;
        int startMatrix = 2;
        int endMatrix = 3;
        // both startMatrix and endMatrix are inclusive, so add 1
        int numMatrices = (endMatrix - startMatrix) + 1;
        int *matrixList = malloc(sizeof(int) * size * numMatrices);
        int numPairs = 0;
        loadFile(n, size, rows, startMatrix, endMatrix, matrixList, &numPairs, "res/n5.csv");
        // asserts
        if (!assertInt(3, numPairs))                passed = false;
        if (!assertInt(2, ML(0, 0, 0)))             passed = false;
        if (!assertInt(1, ML(0, 0, rows-1)))        passed = false;
        if (!assertInt(5, ML(0, rows-1, 0)))        passed = false;
        if (!assertInt(1, ML(0, rows-1, rows-1)))   passed = false;
        if (!assertInt(1, ML(1, 0, 0)))             passed = false;
        if (!assertInt(2, ML(1, 0, rows-1)))        passed = false;
        if (!assertInt(5, ML(1, rows-1, 0)))        passed = false;
        if (!assertInt(8, ML(1, rows-1, rows-1)))   passed = false;
        // free memory
        free(matrixList);
    }
    return passed;
}

// Test addition of 2 matrices.
bool testAdd() {
    // 1x1
    {
        int a[1] = {1};
        int b[1] = {2};
        int c[1] = {0};
        int d[1] = {3};
        add(1, 1, 1, a, b, c, 0, 0, 0, 0);
        if (!assertMatrix(1, c, d)) return false;
    }
    // 2x2
    {
        int a[4] = {1, 2,
                    3, 4};
        int b[4] = {1, 2,
                    3, 4};
        int c1[4] = {0, 0,
                     0, 0};
        int d1[4] = {2, 4,
                     6, 8};
        int c2[1] = {0};
        int d2[1] = {6};
        add(2, 2, 2, a, b, c1, 0, 0, 0, 0);
        add(2, 2, 1, a, b, c2, 1, 0, 1, 0);
        if (!assertMatrix(4, c1, d1)) return false;
        if (!assertMatrix(1, c2, d2)) return false;
    }
    // 3x3
    {
        int a[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int b[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        int c1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int d1[9] = {10, 10, 10, 10, 10, 10, 10, 10, 10};
        int c2[4] = {0, 0, 0, 0};
        int d2[4] = {10, 10, 10, 10};
        add(3, 3, 3, a, b, c1, 0, 0, 0, 0);
        add(3, 3, 2, a, b, c2, 1, 1, 1, 1);
        if (!assertMatrix(9, c1, d1)) return false;
        if (!assertMatrix(4, c2, d2)) return false;
    }
    // 4x4 quadrant tests
    {
        int a[16] = {1, 2, 3, 4,
                     5, 6, 7, 8,
                     9, 7, 0, 3,
                     7, 5, 1, 0};
        int b[16] = {7, 8, 5, 9,
                     8, 7, 6, 5,
                     3, 9, 7, 2,
                     0, 1, 9, 7};
        int c1[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int d1[16] = {8, 10, 8, 13,
                      13, 13, 13, 13,
                      12, 16, 7, 5,
                      7, 6, 10, 7};
        // Q3
        int c2[4] = {0, 0, 0, 0};
        int d2[4] = {12, 16, 7, 6};
        // Q1
        int c3[4] = {0, 0, 0, 0};
        int d3[4] = {8, 10, 13, 13};
        // Q2
        int c4[4] = {0, 0, 0, 0};
        int d4[4] = {8, 13, 13, 13};
        // Q4
        int c5[4] = {0, 0, 0, 0};
        int d5[4] = {7, 5, 10, 7};
        // different quadrants of a and b
        int c6[4] = {0, 0, 0, 0};
        int d6[4] = {8, 4, 14, 13};
        add(4, 4, 4, a, b, c1, 0, 0, 0, 0);
        add(4, 4, 2, a, b, c2, 2, 0, 2, 0);
        add(4, 4, 2, a, b, c3, 0, 0, 0, 0);
        add(4, 4, 2, a, b, c4, 0, 2, 0, 2);
        add(4, 4, 2, a, b, c5, 2, 2, 2, 2);
        add(4, 4, 2, a, b, c6, 0, 0, 2, 2);
        if (!assertMatrix(16, c1, d1)) return false;
        if (!assertMatrix(4, c2, d2)) return false;
        if (!assertMatrix(4, c3, d3)) return false;
        if (!assertMatrix(4, c4, d4)) return false;
        if (!assertMatrix(4, c5, d5)) return false;
        if (!assertMatrix(4, c6, d6)) return false;
    }
    return true;
}

// Test subtraction of 2 matrices.
bool testSub() {
    // 1x1
    {
        int a[1] = {1};
        int b[1] = {2};
        int c[1] = {0};
        int d[1] = {-1};
        sub(1, 1, 1, a, b, c, 0, 0, 0, 0);
        if (!assertMatrix(1, c, d)) return false;
    }
    // 2x2
    {
        int a[4] = {1, 2,
                    3, 4};
        int b[4] = {1, 2,
                    3, 4};
        int c1[4] = {0, 0,
                     0, 0};
        int d1[4] = {0, 0,
                     0, 0};
        int c2[1] = {0};
        int d2[1] = {0};
        sub(2, 2, 2, a, b, c1, 0, 0, 0, 0);
        sub(2, 2, 1, a, b, c2, 1, 0, 1, 0);
        if (!assertMatrix(4, c1, d1)) return false;
        if (!assertMatrix(1, c2, d2)) return false;
    }
    // 3x3
    {
        int a[9] = {1, 2, 3,
                    4, 5, 6,
                    7, 8, 9};
        int b[9] = {9, 8, 7,
                    6, 5, 4,
                    3, 2, 1};
        int c1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int d1[9] = {-8, -6, -4,
                     -2,  0,  2,
                      4,  6,  8};
        int c2[4] = {0, 0, 0, 0};
        int d2[4] = {0, 2,
                     6, 8};
        sub(3, 3, 3, a, b, c1, 0, 0, 0, 0);
        sub(3, 3, 2, a, b, c2, 1, 1, 1, 1);
        if (!assertMatrix(9, c1, d1)) return false;
        if (!assertMatrix(4, c2, d2)) return false;
    }
    // 4x4 quadrant tests
    {
        int a[16] = {1, 2, 3, 4,
                     5, 6, 7, 8,
                     9, 7, 0, 3,
                     7, 5, 1, 0};
        int b[16] = {7, 8, 5, 9,
                     8, 7, 6, 5,
                     3, 9, 7, 2,
                     0, 1, 9, 7};
        int c1[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int d1[16] = {-6, -6, -2, -5,
                      -3, -1, 1, 3,
                      6, -2, -7, 1,
                      7, 4, -8, -7};
        // Q3
        int c2[4] = {0, 0, 0, 0};
        int d2[4] = {6, -2, 7, 4};
        // Q1
        int c3[4] = {0, 0, 0, 0};
        int d3[4] = {-6, -6, -3, -1};
        // Q2
        int c4[4] = {0, 0, 0, 0};
        int d4[4] = {-2, -5, 1, 3};
        // Q4
        int c5[4] = {0, 0, 0, 0};
        int d5[4] = {-7, 1, -8, -7};
        // Q1 of a, Q4 of b
        int c6[4] = {0, 0, 0, 0};
        int d6[4] = {-6, 0, -4, -1};
        sub(4, 4, 4, a, b, c1, 0, 0, 0, 0);
        sub(4, 4, 2, a, b, c2, 2, 0, 2, 0);
        sub(4, 4, 2, a, b, c3, 0, 0, 0, 0);
        sub(4, 4, 2, a, b, c4, 0, 2, 0, 2);
        sub(4, 4, 2, a, b, c5, 2, 2, 2, 2);
        sub(4, 4, 2, a, b, c6, 0, 0, 2, 2);
        if (!assertMatrix(16, c1, d1)) return false;
        if (!assertMatrix(4, c2, d2)) return false;
        if (!assertMatrix(4, c3, d3)) return false;
        if (!assertMatrix(4, c4, d4)) return false;
        if (!assertMatrix(4, c5, d5)) return false;
        if (!assertMatrix(4, c6, d6)) return false;
    }
    return true;
}

// Test multiplication of 2 matrices.
bool testMultiplyBruteForce() {
    // 1x1
    {
        int a[1] = {7};
        int b[1] = {5};
        int c[1] = {0};
        int d[1] = {35};
        matrixMultiplyBruteForce(1, 1, 1, a, b, c, 0, 0, 0, 0);
        if (!assertMatrix(1, c, d)) return false;
    }
    // 2x2
    {
        int a[4] = {1, 2, 3, 4};
        int b[4] = {2, 0, 1, 2};
        int c1[4] = {0, 0, 0, 0};
        int c2[4] = {0, 0, 0, 0};
        int d1[4] = {4, 4, 10, 8};
        int d2[4] = {2, 4, 7, 10};
        matrixMultiplyBruteForce(2, 2, 2, a, b, c1, 0, 0, 0, 0);
        matrixMultiplyBruteForce(2, 2, 2, b, a, c2, 0, 0, 0, 0);
        if (!assertMatrix(4, c1, d1)) return false;
        if (!assertMatrix(4, c2, d2)) return false;
    }
    // 3x3
    {
        int a[9] = {5, 3, 4, 2, 5, 3, 1, 6, 9};
        int b[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int c1[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int c2[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
        int d1[9] = {45, 57, 69, 43, 53, 63, 88, 104, 120};
        int d2[9] = {12, 31, 37, 36, 73, 85, 60, 115, 133};
        matrixMultiplyBruteForce(3, 3, 3, a, b, c1, 0, 0, 0, 0);
        matrixMultiplyBruteForce(3, 3, 3, b, a, c2, 0, 0, 0, 0);
        if (!assertMatrix(9, c1, d1)) return false;
        if (!assertMatrix(9, c2, d2)) return false;
    }
    return true;
}

// Test multiplication of 2 matrices.
bool testMultiplyStrassens() {
    // 1x1
    {
        int a[1] = {7};
        int b[1] = {5};
        int c[1] = {0};
        int d[1] = {35};
        matrixMultiplyStrassens(0, 0, 1, 1, 1, a, b, c, 0, 0, 0, 0);
        if (!assertMatrix(1, c, d)) return false;
        printf("STRASSEN 1ST PASSED\n");
    }
    // 2x2
    {
        int a[4] = {1, 2, 3, 4};
        int b[4] = {2, 0, 1, 2};
        int c1[4] = {0, 0, 0, 0};
        int c2[4] = {0, 0, 0, 0};
        int d1[4] = {4, 4, 10, 8};
        int d2[4] = {2, 4, 7, 10};
        matrixMultiplyStrassens(0, 1, 2, 2, 2, a, b, c1, 0, 0, 0, 0);
        matrixMultiplyStrassens(0, 1, 2, 2, 2, b, a, c2, 0, 0, 0, 0);
        if (!assertMatrix(4, c1, d1)) return false;
        if (!assertMatrix(4, c2, d2)) return false;
        printf("STRASSEN 2ND PASSED\n");
    }
    // 4x4
    {
        int a[16] = {5, 3, 4, 3,
                     2, 5, 3, 2,
                     1, 6, 9, 1,
                     1, 2, 3, 4};
        int b[16] = {1, 2, 3, 3,
                     4, 5, 6, 2,
                     7, 8, 9, 1,
                     1, 2, 3, 4};
        int c1[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int c2[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int c3[4] = {0, 0, 0, 0};
        int c4[4] = {0, 0, 0, 0};
        matrixMultiplyStrassens(0, 2, 4, 4, 4, a, b, c1, 0, 0, 0, 0);
        matrixMultiplyStrassens(0, 2, 4, 4, 4, b, a, c2, 0, 0, 0, 0);
        matrixMultiplyStrassens(0, 2, 2, 4, 4, a, b, c3, 2, 2, 2, 2);
        matrixMultiplyStrassens(0, 2, 2, 4, 4, a, b, c4, 1, 1, 1, 1);
        int d1[16] = {48, 63, 78, 37,
                      45, 57, 69, 27,
                      89, 106, 123, 28,
                      34, 44, 54, 26};
        int d2[16] = {15, 37, 46, 22,
                      38, 77, 91, 36,
                      61, 117, 136, 50,
                      16, 39, 49, 26};
        int d3[4] = {84, 13, 39, 19};
        int d4[4] = {49, 57, 102, 117};
        if (!assertMatrix(16, c1, d1)) return false;
        if (!assertMatrix(16, c2, d2)) return false;
        if (!assertMatrix(4, c3, d3)) return false;
        if (!assertMatrix(4, c4, d4)) return false;
        printf("STRASSEN 3RD PASSED\n");
    }
    // 8x8
    {
        int a[64] = {9, 6, 6, 9, 7, 6, 3, 1,
                     9, 4, 2, 9, 1, 7, 5, 4,
                     8, 6, 7, 4, 8, 0, 4, 0,
                     6, 5, 2, 5, 2, 0, 4, 2,
                     4, 2, 6, 2, 9, 0, 3, 2,
                     0, 0, 1, 5, 2, 8, 8, 3,
                     2, 1, 8, 4, 1, 0, 7, 2,
                     2, 5, 5, 6, 9, 8, 0, 2};
        int b[64] = {7, 0, 8, 5, 7, 7, 3, 8,
                     9, 8, 0, 5, 0, 4, 9, 2,
                     4, 5, 1, 6, 0, 2, 1, 0,
                     0, 0, 2, 9, 3, 5, 9, 9,
                     5, 1, 9, 5, 9, 5, 4, 6,
                     3, 2, 8, 7, 4, 7, 7, 1,
                     2, 5, 4, 1, 9, 2, 8, 8,
                     5, 4, 0, 8, 6, 8, 5, 1};
        int c[64] = {0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0};
        int d[64] = {205, 116, 219, 280, 210, 235, 267, 238,
                     163, 98, 177, 249, 196, 224, 259, 218,
                     186, 111, 167, 192, 176, 162, 185, 192,
                     123, 80, 94, 142, 123, 125, 160, 149,
                     131, 78, 135, 148, 154, 125, 124, 134,
                     69, 75, 125, 149, 155, 133, 189, 132,
                     84, 92, 69, 127, 110, 89, 129, 118,
                     158, 98, 178, 236, 157, 191, 212, 144};
        matrixMultiplyStrassens(0, 3, 8, 8, 8, a, b, c, 0, 0, 0, 0);
        if (!assertMatrix(64, c, d)) return false;
        printf("STRASSEN 4TH PASSED\n");
    }
    return true;
}

// Test multiplication of 2 matrices.
bool testMultiplyBoth() {
    // 1x1
    {
        int a[1] = {7};
        int b[1] = {5};
        int c[1] = {0};
        int d[1] = {35};
        matrixMultiplyStrassens(0, 0, 1, 1, 1, a, b, c, 0, 0, 0, 0);
        if (!assertMatrix(1, c, d)) return false;
        printf("BOTH 1ST PASSED\n");
    }
    // 2x2
    {
        int a[4] = {1, 2, 3, 4};
        int b[4] = {2, 0, 1, 2};
        int c1[4] = {0, 0, 0, 0};
        int c2[4] = {0, 0, 0, 0};
        int d1[4] = {4, 4, 10, 8};
        int d2[4] = {2, 4, 7, 10};
        matrixMultiplyStrassens(0, 1, 2, 2, 2, a, b, c1, 0, 0, 0, 0);
        matrixMultiplyStrassens(0, 1, 2, 2, 2, b, a, c2, 0, 0, 0, 0);
        if (!assertMatrix(4, c1, d1)) return false;
        if (!assertMatrix(4, c2, d2)) return false;
        printf("BOTH 2ND PASSED\n");
    }
    // 4x4
    {
        int a[16] = {5, 3, 4, 3,
                     2, 5, 3, 2,
                     1, 6, 9, 1,
                     1, 2, 3, 4};
        int b[16] = {1, 2, 3, 3,
                     4, 5, 6, 2,
                     7, 8, 9, 1,
                     1, 2, 3, 4};
        int c1[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int c2[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int c3[4] = {0, 0, 0, 0};
        int c4[4] = {0, 0, 0, 0};
        matrixMultiplyStrassens(1, 2, 4, 4, 4, a, b, c1, 0, 0, 0, 0);
        matrixMultiplyStrassens(0, 2, 4, 4, 4, b, a, c2, 0, 0, 0, 0);
        matrixMultiplyStrassens(1, 2, 2, 4, 4, a, b, c3, 2, 2, 2, 2);
        matrixMultiplyStrassens(0, 2, 2, 4, 4, a, b, c4, 1, 1, 1, 1);
        int d1[16] = {48, 63, 78, 37,
                      45, 57, 69, 27,
                      89, 106, 123, 28,
                      34, 44, 54, 26};
        int d2[16] = {15, 37, 46, 22,
                      38, 77, 91, 36,
                      61, 117, 136, 50,
                      16, 39, 49, 26};
        int d3[4] = {84, 13, 39, 19};
        int d4[4] = {49, 57, 102, 117};
        if (!assertMatrix(16, c1, d1)) return false;
        if (!assertMatrix(16, c2, d2)) return false;
        if (!assertMatrix(4, c3, d3)) return false;
        if (!assertMatrix(4, c4, d4)) return false;
        printf("BOTH 3RD PASSED\n");
    }
    // 8x8
    {
        int a[64] = {9, 6, 6, 9, 7, 6, 3, 1,
                     9, 4, 2, 9, 1, 7, 5, 4,
                     8, 6, 7, 4, 8, 0, 4, 0,
                     6, 5, 2, 5, 2, 0, 4, 2,
                     4, 2, 6, 2, 9, 0, 3, 2,
                     0, 0, 1, 5, 2, 8, 8, 3,
                     2, 1, 8, 4, 1, 0, 7, 2,
                     2, 5, 5, 6, 9, 8, 0, 2};
        int b[64] = {7, 0, 8, 5, 7, 7, 3, 8,
                     9, 8, 0, 5, 0, 4, 9, 2,
                     4, 5, 1, 6, 0, 2, 1, 0,
                     0, 0, 2, 9, 3, 5, 9, 9,
                     5, 1, 9, 5, 9, 5, 4, 6,
                     3, 2, 8, 7, 4, 7, 7, 1,
                     2, 5, 4, 1, 9, 2, 8, 8,
                     5, 4, 0, 8, 6, 8, 5, 1};
        int c[64] = {0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0,
                     0, 0, 0, 0, 0, 0, 0, 0};
        int d[64] = {205, 116, 219, 280, 210, 235, 267, 238,
                     163, 98, 177, 249, 196, 224, 259, 218,
                     186, 111, 167, 192, 176, 162, 185, 192,
                     123, 80, 94, 142, 123, 125, 160, 149,
                     131, 78, 135, 148, 154, 125, 124, 134,
                     69, 75, 125, 149, 155, 133, 189, 132,
                     84, 92, 69, 127, 110, 89, 129, 118,
                     158, 98, 178, 236, 157, 191, 212, 144};
        matrixMultiplyStrassens(2, 3, 8, 8, 8, a, b, c, 0, 0, 0, 0);
        if (!assertMatrix(64, c, d)) return false;
        printf("BOTH 4TH PASSED\n");
    }
    return true;
}


//
// Runner functions
//


// Test runner.
void testRun() {
    // run tests
    printf("-----\n");
    bool resultCSV = testCSV();
    bool resultAdd = testAdd();
    bool resultSub = testSub();
    bool resultMultiplyBruteForce = testMultiplyBruteForce();
    bool resultMultiplyStrassens = testMultiplyStrassens();
    bool resultMultiplyBoth = testMultiplyBoth();
    printf("-----\n");
    // print results
    int testsTotal = 6;
    int testsFailed = 0;
    if (!resultCSV) {
        testsFailed++;
        printf("FAIL: csv\n");
    } else { printf("PASS: csv\n"); }
    // add
    if (!resultAdd) {
        testsFailed++;
        printf("FAIL: add\n");
    } else { printf("PASS: add\n"); }
    // subtract
    if (!resultSub) {
        testsFailed++;
        printf("FAIL: sub\n");
    } else { printf("PASS: sub\n"); }
    // brute-force
    if (!resultMultiplyBruteForce) {
        testsFailed++;
        printf("FAIL: multiply_brute_force\n");
    } else { printf("PASS: multiply_brute_force\n"); }
    // strassen's
    if (!resultMultiplyStrassens) {
        testsFailed++;
        printf("FAIL: multiply_strassens\n");
    } else { printf("PASS: multiply_strassens\n"); }
    // both
    if (!resultMultiplyBoth) {
        testsFailed++;
        printf("FAIL: multiply_both\n");
    } else { printf("PASS: multiply_both\n"); }
    // print totals
    printf("-----\n");
    printf("TOTAL: %d\n", testsTotal);
    printf("FAILED: %d\n", testsFailed);
    printf("-----\n");
}
