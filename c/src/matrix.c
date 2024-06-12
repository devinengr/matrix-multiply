#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"

// Fill the given matrices with random integers.
void fillRandMatrices(int size, int *a, int *b) {
    // seed the RNG
    srand(time(NULL));
    // fill matrices with random integers
    for (int i = 0; i < size; i++) {
            a[i] = rand() % 10;
            b[i] = rand() % 10;
    }
}

// Add the given matrices.
void add(int rowsA, int rowsB, int rowsC,
         int *a, int *b, int *c,
         int aRowOffset, int aColOffset,
         int bRowOffset, int bColOffset) {
    for (int i = 0; i < rowsC; i++) {
        for (int j = 0; j < rowsC; j++) {
            M(c, rowsC, i, j) = M(a, rowsA, aRowOffset + i, aColOffset + j)
                              + M(b, rowsB, bRowOffset + i, bColOffset + j);
        }
    }
}

// Subtract the given matrices.
void sub(int rowsA, int rowsB, int rowsC,
         int *a, int *b, int *c,
         int aRowOffset, int aColOffset,
         int bRowOffset, int bColOffset) {
    for (int i = 0; i < rowsC; i++) {
        for (int j = 0; j < rowsC; j++) {
            M(c, rowsC, i, j) = M(a, rowsA, aRowOffset + i, aColOffset + j)
                              - M(b, rowsB, bRowOffset + i, bColOffset + j);
        }
    }
}

// Multiply the given matrices using the brute force algorithm.
void matrixMultiplyBruteForce(int rowsA, int rowsB, int rowsC,
                              int *a, int *b, int *c,
                              int aRowOffset, int aColOffset,
                              int bRowOffset, int bColOffset) {
    for (int i = 0; i < rowsC; i++) {
        for (int j = 0; j < rowsC; j++) {
            M(c,rowsC,i,j) = 0;
            for (int k = 0; k < rowsC; k++) {
                M(c, rowsC, i, j) = M(c, rowsC, i, j)
                                  + M(a, rowsA, i+aRowOffset, k+aColOffset)
                                  * M(b, rowsB, k+bRowOffset, j+bColOffset);
            }
        }
    }
}

// Multiply the given matrices using Strassen's algorithm.
void matrixMultiplyStrassens(int cutoff, int n,
                             int rowsCurrent,
                             int rowsA, int rowsB,
                             int *a, int *b, int *c,
                             int aRowOffset, int aColOffset,
                             int bRowOffset, int bColOffset) {
    // if a cutoff is specified, switch to brute force
    if (n == cutoff) {
        matrixMultiplyBruteForce(rowsA, rowsB, rowsCurrent,
                                 a, b, c,
                                 aRowOffset, aColOffset,
                                 bRowOffset, bColOffset);
        return;
    }
    // get the quadrant size fast
    int quadRows = rowsCurrent >> 1;
    // 1x1 matrix
    if (rowsCurrent == 1) {
        M(c, rowsCurrent, 0, 0) = M(a, rowsA, aRowOffset, aColOffset)
                                * M(b, rowsB, bRowOffset, bColOffset);
    // 2x2 matrix
    } else if (rowsCurrent == 2) {
        // get each quadrant
        int a00 = M(a, rowsA, aRowOffset, aColOffset);
        int a01 = M(a, rowsA, aRowOffset, aColOffset + quadRows);
        int a10 = M(a, rowsA, aRowOffset + quadRows, aColOffset);
        int a11 = M(a, rowsA, aRowOffset + quadRows, aColOffset + quadRows);
        int b00 = M(b, rowsB, bRowOffset, bColOffset);
        int b01 = M(b, rowsB, bRowOffset, bColOffset + quadRows);
        int b10 = M(b, rowsB, bRowOffset + quadRows, bColOffset);
        int b11 = M(b, rowsB, bRowOffset + quadRows, bColOffset + quadRows);
        // get m values
        int m1 = (a00 + a11) * (b00 + b11);
        int m2 = (a10 + a11) * b00;
        int m3 = a00 * (b01 - b11);
        int m4 = a11 * (b10 - b00);
        int m5 = (a00 + a01) * b11;
        int m6 = (a10 - a00) * (b00 + b01);
        int m7 = (a01 - a11) * (b10 + b11);
        // build the result matrix (2x2)
        M(c, rowsCurrent, 0, 0) = m1 + m4 - m5 + m7;
        M(c, rowsCurrent, 0, 1) = m3 + m5;
        M(c, rowsCurrent, 1, 0) = m2 + m4;
        M(c, rowsCurrent, 1, 1) = m1 + m3 - m2 + m6;
    // 4x4+ matrix
    } else {
        // get offsets to each quadrant
        int a00_RowOffset = 0        + aRowOffset;
        int a00_ColOffset = 0        + aColOffset;
        int a01_RowOffset = 0        + aRowOffset;
        int a01_ColOffset = quadRows + aColOffset;
        int a10_RowOffset = quadRows + aRowOffset;
        int a10_ColOffset = 0        + aColOffset;
        int a11_RowOffset = quadRows + aRowOffset;
        int a11_ColOffset = quadRows + aColOffset;
        int b00_RowOffset = 0        + bRowOffset;
        int b00_ColOffset = 0        + bColOffset;
        int b01_RowOffset = 0        + bRowOffset;
        int b01_ColOffset = quadRows + bColOffset;
        int b10_RowOffset = quadRows + bRowOffset;
        int b10_ColOffset = 0        + bColOffset;
        int b11_RowOffset = quadRows + bRowOffset;
        int b11_ColOffset = quadRows + bColOffset;
        // get m values
        int quadSize = quadRows * quadRows;
        // 21 heap allocations needed in one recursive call
        // let's instead make it 1 to save time
        int *m1 = malloc(sizeof(int) * quadSize * 21);
        int *m2 = m1 + quadSize;
        int *m3 = m2 + quadSize;
        int *m4 = m3 + quadSize;
        int *m5 = m4 + quadSize;
        int *m6 = m5 + quadSize;
        int *m7 = m6 + quadSize;
        // get pointers to memory space to hold additions/subtractions
        int *m1_addA = m7 + quadSize;
        int *m1_addB = m1_addA + quadSize;
        int *m2_addA = m1_addB + quadSize;
        int *m3_subB = m2_addA + quadSize;
        int *m4_subB = m3_subB + quadSize;
        int *m5_addA = m4_subB + quadSize;
        int *m6_subA = m5_addA + quadSize;
        int *m6_addB = m6_subA + quadSize;
        int *m7_subA = m6_addB + quadSize;
        int *m7_addB = m7_subA + quadSize;
        // grab pointers to rebuild the matrix
        int *c1 = m7_addB + quadSize;
        int *c2 = c1 + quadSize;
        int *c3 = c2 + quadSize;
        int *c4 = c3 + quadSize;
        // additions / subtractions
        add(rowsA, rowsA, quadRows, a, a, m1_addA,
            a00_RowOffset, a00_ColOffset,
            a11_RowOffset, a11_ColOffset);
        add(rowsB, rowsB, quadRows, b, b, m1_addB,
            b00_RowOffset, b00_ColOffset,
            b11_RowOffset, b11_ColOffset);
        add(rowsA, rowsA, quadRows, a, a, m2_addA,
            a10_RowOffset, a10_ColOffset,
            a11_RowOffset, a11_ColOffset);
        sub(rowsB, rowsB, quadRows, b, b, m3_subB,
            b01_RowOffset, b01_ColOffset,
            b11_RowOffset, b11_ColOffset);
        sub(rowsB, rowsB, quadRows, b, b, m4_subB,
            b10_RowOffset, b10_ColOffset,
            b00_RowOffset, b00_ColOffset);
        add(rowsA, rowsA, quadRows, a, a, m5_addA,
            a00_RowOffset, a00_ColOffset,
            a01_RowOffset, a01_ColOffset);
        sub(rowsA, rowsA, quadRows, a, a, m6_subA,
            a10_RowOffset, a10_ColOffset,
            a00_RowOffset, a00_ColOffset);
        add(rowsB, rowsB, quadRows, b, b, m6_addB,
            b00_RowOffset, b00_ColOffset,
            b01_RowOffset, b01_ColOffset);
        sub(rowsA, rowsA, quadRows, a, a, m7_subA,
            a01_RowOffset, a01_ColOffset,
            a11_RowOffset, a11_ColOffset);
        add(rowsB, rowsB, quadRows, b, b, m7_addB,
            b10_RowOffset, b10_ColOffset,
            b11_RowOffset, b11_ColOffset);
        // recursive calls
        // m1
        matrixMultiplyStrassens(
            cutoff, n-1,
            quadRows,
            quadRows, quadRows,
            m1_addA, m1_addB, m1,
            0, 0,
            0, 0);
        // m2
        matrixMultiplyStrassens(
            cutoff, n-1,
            quadRows,
            quadRows, rowsB,
            m2_addA, b, m2,
            0, 0,
            b00_RowOffset, b00_ColOffset);
        // m3
        matrixMultiplyStrassens(
            cutoff, n-1,
            quadRows,
            rowsA, quadRows,
            a, m3_subB, m3,
            a00_RowOffset, a00_ColOffset,
            0, 0);
        // m4
        matrixMultiplyStrassens(
            cutoff, n-1,
            quadRows,
            rowsA, quadRows,
            a, m4_subB, m4,
            a11_RowOffset, a11_ColOffset,
            0, 0);
        // m5
        matrixMultiplyStrassens(
            cutoff, n-1,
            quadRows,
            quadRows, rowsB,
            m5_addA, b, m5,
            0, 0,
            b11_RowOffset, b11_ColOffset);
        // m6
        matrixMultiplyStrassens(
            cutoff, n-1,
            quadRows,
            quadRows, quadRows,
            m6_subA, m6_addB, m6,
            0, 0,
            0, 0);
        // m7
        matrixMultiplyStrassens(
            cutoff, n-1,
            quadRows,
            quadRows, quadRows,
            m7_subA, m7_addB, m7,
            0, 0,
            0, 0);
        // calculate c1-c4
        // c1
        add(quadRows, quadRows, quadRows, m1, m4, c1, 0, 0, 0, 0);
        sub(quadRows, quadRows, quadRows, c1, m5, c1, 0, 0, 0, 0);
        add(quadRows, quadRows, quadRows, c1, m7, c1, 0, 0, 0, 0);
        // c2
        add(quadRows, quadRows, quadRows, m3, m5, c2, 0, 0, 0, 0);
        // c3
        add(quadRows, quadRows, quadRows, m2, m4, c3, 0, 0, 0, 0);
        // c4
        add(quadRows, quadRows, quadRows, m1, m3, c4, 0, 0, 0, 0);
        sub(quadRows, quadRows, quadRows, c4, m2, c4, 0, 0, 0, 0);
        add(quadRows, quadRows, quadRows, c4, m6, c4, 0, 0, 0, 0);
        // build the matrix
        for (int i = 0; i < quadRows; i++) {
            for (int j = 0; j < quadRows; j++) {
                M(c, rowsCurrent, i, j)                     = M(c1, quadRows, i, j);
                M(c, rowsCurrent, i, j+quadRows)            = M(c2, quadRows, i, j);
                M(c, rowsCurrent, i+quadRows, j)            = M(c3, quadRows, i, j);
                M(c, rowsCurrent, i+quadRows, j+quadRows)   = M(c4, quadRows, i, j);
            }
        }
        // Free memory
        free(m1);
    }
}