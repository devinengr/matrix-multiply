#pragma once


// m = matrix #
// i = row
// j = column
#define ML(m, i, j) matrixList[((m)*size) + ((i)*rows)+(j)]

// i = row
// j = column
// rows = # of rows
#define M(name, rows, i, j) name[((i)*(rows))+(j)]


void fillRandMatrices(int size, int *a, int *b);

void add(int rowsA, int rowsB, int quadRows,
         int *a, int *b, int *c,
         int aRowOffset, int aColOffset,
         int bRowOffset, int bColOffset);

void sub(int rowsA, int rowsB, int quadRows,
         int *a, int *b, int *c,
         int aRowOffset, int aColOffset,
         int bRowOffset, int bColOffset);

void matrixMultiplyBruteForce(int rowsA, int rowsB, int rowsC,
                              int *a, int *b, int *c,
                              int aRowOffset, int aColOffset,
                              int bRowOffset, int bColOffset);

void matrixMultiplyStrassens(int cutoff, int n,
                             int rowsCurrent,
                             int rowsA, int rowsB,
                             int *a, int *b, int *c,
                             int aRowOffset, int aColOffset,
                             int bRowOffset, int bColOffset);
