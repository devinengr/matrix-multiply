# Matrix Multiply

Use this program to multiply many pairs of matrices very quickly. If speed of multiplication is the goal, use the C version, as the Python version is considerably slower. This program was originally written in Python, then it was rewritten in C due to its expensive operations.

# Requirements

* [Python 3](https://www.python.org/downloads/)
* C/C++ compiler
    * If you're using Windows, you can install gcc through [MinGW-w64](https://www.mingw-w64.org/downloads/#mingw-builds). You may need to add the included bin folder to your PATH depending on which compiler you choose.

# How to run the Python version

Navigate into python/src and then run this command:
* python3 run.py

See the [next section about how to use the program](#using-the-program) to learn how to use the program to multiply matrices.

# How to run the C version

You'll need to compile the code first. Note that the Makefile was designed on Windows and not tested on Linux. It may not work due to using the Windows backslash ( \\ ). This guide assumes you are using the [MinGW-w64 compiler](https://www.mingw-w64.org/downloads/#mingw-builds).

Go into the `c` folder where the Makefile is located, then run this command:
* mingw32-make

Once finished, you'll find an executable in the `bin` folder:
* cd bin
* .\matrix.exe

It's important to run the executable from the directory it's located in, otherwise it will not be able to find the matrices located in the `res` folder.
 
# Using the program

When running the program, you'll be prompted to specify a value for `n`. This is asking how large the matrices are. All matrices have a size of `2^n x 2^n`, so if you specify 5 for `n`, the matrices will be `32x32` in size. Likewise, if you specify 9, the matrices will be `512x512` in size.

Both the Python and C versions of the program have a `res` folder containing CSV files. Each CSV file has a set of matrix pairs that are multiplied together. This repository includes at least 1 matrix for each `n` from 5 to 9. So, by default, if you specify a value for `n` that is outside of that range, the program will not work.

At its current state, the program is limited to multiplying matrices that are powers of 2 in size. Also, the program has only been tested with each number in the matrix being a single-digit number. It should work with multiple-digit numbers, but that is untested.

# Using your own matrices

If you want to multiply your own matrices, you'll need to create a CSV file (or add matrices to an existing file) corresponding to their size that follow the naming convention of the CSV files already in the `res` folder. For instance, the C version of the program uses the name `n5.csv` for 32x32 matrices (2^5=32).

The first line of the CSV file is a header containing information that describes the second line. The first 2 lines may look something like this (pulled from n5.csv):

```
n,2^n,number of pairs,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
5,32,3,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
```

So, n5.csv contains 3 pairs of matrices (or 6 total matrices) that are 32x32 in size. The first pair will be multiplied together, followed by the second pair, and then the third.

Each matrix is separated by a line of commas:

```
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
```

The line of commas separating each matrix *pair*, however, begin with a tilde (~) and a number. The number represents the number of matrix pairs that have been reached by the time this line is seen. For instance, the following line is displayed just after the first 2 matrices:

```
~1,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
```

Finally, the last line of the file will be a line of commas that start with a hash (#) symbol to indicate that the last pair has been reached:

```
###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
```

# Example of using your own matrices

Let's say you want to multiply 3 pairs of 8x8 matrices. To do this, create a file `n3.csv` (2^3=8) inside of `res`. Here's an example of what the file would look like:

```
n,2^n,number of pairs,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
3,8,3,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
1,2,3,4,5,6,7,8
2,3,4,5,6,7,8,9
2,3,4,5,6,7,8,1
3,4,5,6,7,8,1,2
4,5,6,7,8,1,2,3
5,6,7,8,1,2,3,4
6,7,8,1,2,3,4,5
7,8,1,2,3,4,5,6
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
1,2,3,4,5,6,7,8
2,3,4,5,6,7,8,9
2,3,4,5,6,7,8,1
3,4,5,6,7,8,1,2
4,5,6,7,8,1,2,3
5,6,7,8,1,2,3,4
6,7,8,1,2,3,4,5
7,8,1,2,3,4,5,6
~1,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
1,2,3,4,5,6,7,8
2,3,4,5,6,7,8,9
2,3,4,5,6,7,8,1
3,4,5,6,7,8,1,2
4,5,6,7,8,1,2,3
5,6,7,8,1,2,3,4
6,7,8,1,2,3,4,5
7,8,1,2,3,4,5,6
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
1,2,3,4,5,6,7,8
2,3,4,5,6,7,8,9
2,3,4,5,6,7,8,1
3,4,5,6,7,8,1,2
4,5,6,7,8,1,2,3
5,6,7,8,1,2,3,4
6,7,8,1,2,3,4,5
7,8,1,2,3,4,5,6
~2,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
1,2,3,4,5,6,7,8
2,3,4,5,6,7,8,9
2,3,4,5,6,7,8,1
3,4,5,6,7,8,1,2
4,5,6,7,8,1,2,3
5,6,7,8,1,2,3,4
6,7,8,1,2,3,4,5
7,8,1,2,3,4,5,6
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
1,2,3,4,5,6,7,8
2,3,4,5,6,7,8,9
2,3,4,5,6,7,8,1
3,4,5,6,7,8,1,2
4,5,6,7,8,1,2,3
5,6,7,8,1,2,3,4
6,7,8,1,2,3,4,5
7,8,1,2,3,4,5,6
~3,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
###,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
```
