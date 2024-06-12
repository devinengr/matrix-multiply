#pragma once

#include <stdbool.h>

void outputResults(int rows, int *a, int *b, int *c, char *fileName);

bool loadFile(int n, int size, int rows,
              int startMatrix, int endMatrix,
              int *matrixList,
              int *numPairs,
              char *fileName);
