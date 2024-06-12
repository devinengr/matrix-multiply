

def multiply_by_brute_force(a, b, qar, qac, qbr, qbc, n):
    """
    Multiply the given matrices a and b.
    """
    # initialize c with all 0's using list comprehension
    c = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(n):
            c[i][j] = 0
            for k in range(n):
                c[i][j] = c[i][j] + a[qar+i][qac+k] * b[qbr+k][qbc+j]
    return c


def add_matrices(a, b):
    """
    Add the given matrices a and b.
    """
    n = len(a[0])
    c = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(n):
            c[i][j] = a[i][j] + b[i][j]
    return c


def sub_matrices(a, b):
    """
    Add the given matrices a and b.
    """
    n = len(a[0])
    c = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(n):
            c[i][j] = a[i][j] - b[i][j]
    return c


def add_matrices_by_index(a, b, qar, qac, qbr, qbc, n):
    """
    Add the given matrices a and b.
    a: 1st matrix
    b: 2nd matrix
    q_a: list of row and column index of quadrant from a
    q_b: list of row and column index of quadrant from b
    """
    c = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(n):
            c[i][j] = a[qar+i][qac+j] + b[qbr+i][qbc+j]
    return c


def sub_matrices_by_index(a, b, qar, qac, qbr, qbc, n):
    """
    Subtract the given matrices a and b.
    a: 1st matrix
    b: 2nd matrix
    q_a: list of row and column index of quadrant from a
    q_b: list of row and column index of quadrant from b
    """
    c = [[0 for i in range(n)] for j in range(n)]
    for i in range(n):
        for j in range(n):
            c[i][j] = a[qar+i][qac+j] - b[qbr+i][qbc+j]
    return c



def multiply_by_strassens(a, b, qar, qac, qbr, qbc, two_pow_n, n):
    """
    Multiply 2 matrices together.
    a: 1st matrix
    b: 2nd matrix
    q_a: list of row and column index of quadrant from a
    q_b: list of row and column index of quadrant from b
    n: number of rows in matrices a and b
    """
    # bit shift for better efficiency. i think the cpu was doing that anyway though
    n_div_2 = 1
    if n > 1:
        n_div_2 = 1 << (n-1)
    # get the length of the first row, as its length can be n
    if two_pow_n == 1:
        # just 2 numbers, so multiply them
        return [[a[0][0] * b[0][0]]]
    if two_pow_n == 2:
        # 2-by-2 matrices. we can now grab integers and operate on them
        # if a large matrix was passed in, grab the correct quadrant first
        m1 = (a[qar+0][qac+0] + a[qar+n_div_2][qac+n_div_2]) * (b[qbr+0][qbc+0] + b[qbr+n_div_2][qbc+n_div_2])
        m2 = (a[qar+n_div_2][qac+0] + a[qar+n_div_2][qac+n_div_2]) * b[qbr+0][qbc+0]
        m3 = a[qar+0][qac+0] * (b[qbr+0][qbc+n_div_2] - b[qbr+n_div_2][qbc+n_div_2])
        m4 = a[qar+n_div_2][qac+n_div_2] * (b[qbr+n_div_2][qbc+0] - b[qbr+0][qbc+0])
        m5 = (a[qar+0][qac+0] + a[qar+0][qac+n_div_2]) * b[qbr+n_div_2][qbc+n_div_2]
        m6 = (a[qar+n_div_2][qac+0] - a[qar+0][qac+0]) * (b[qbr+0][qbc+0] + b[qbr+0][qbc+n_div_2])
        m7 = (a[qar+0][qac+n_div_2] - a[qar+n_div_2][qac+n_div_2]) * (b[qbr+n_div_2][qbc+0] + b[qbr+n_div_2][qbc+n_div_2])
       # build the resulting matrix and return it
        return [[m1+m4-m5+m7, m3+m5],
                [m2+m4, m1+m3-m2+m6]]
    # get the weird m values
    # define size for quadrants
    # pass a as both arguments since we need to add 2 quadrants from the same matrix.
    m1 = multiply_by_strassens(
        add_matrices_by_index(a, a, qar+0, qac+0, qar+n_div_2, qac+n_div_2, n_div_2),
        add_matrices_by_index(b, b, qbr+0, qbc+0, qbr+n_div_2, qbc+n_div_2, n_div_2),
        0, 0, # passing in an individual matrix, so just start at its 0, 0
        0, 0, # passing in an individual matrix, so just start at its 0, 0
        n_div_2,
        n-1
    )
    m2 = multiply_by_strassens(
        add_matrices_by_index(a, a, qar+n_div_2, qac+0, qar+n_div_2, qac+n_div_2, n_div_2),
        b,
        0, 0, # passing in an individual matrix, so just start at its 0, 0
        qbr+0, qbc+0, # passing in the entire matrix, so specify the correct quadrant
        n_div_2,
        n-1
    )
    m3 = multiply_by_strassens(
        a,
        sub_matrices_by_index(b, b, qbr+0, qbc+n_div_2, qbr+n_div_2, qbc+n_div_2, n_div_2),
        qar+0, qac+0,
        0, 0,
        n_div_2,
        n-1
    )
    m4 = multiply_by_strassens(
        a,
        sub_matrices_by_index(b, b, qbr+n_div_2, qbc+0, qbr+0, qbc+0, n_div_2),
        qar+n_div_2, qac+n_div_2,
        0, 0,
        n_div_2,
        n-1
    )
    m5 = multiply_by_strassens(
        add_matrices_by_index(a, a, qar+0, qac+0, qar+0, qac+n_div_2, n_div_2),
        b,
        0, 0,
        qbr+n_div_2, qbc+n_div_2,
        n_div_2,
        n-1
    )
    m6 = multiply_by_strassens(
        sub_matrices_by_index(a, a, qar+n_div_2, qac+0, qar+0, qac+0, n_div_2),
        add_matrices_by_index(b, b, qbr+0, qbc+0, qbr+0, qbc+n_div_2, n_div_2),
        0, 0,
        0, 0,
        n_div_2,
        n-1
    )
    m7 = multiply_by_strassens(
        sub_matrices_by_index(a, a, qar+0, qac+n_div_2, qar+n_div_2, qac+n_div_2, n_div_2),
        add_matrices_by_index(b, b, qbr+n_div_2, qbc+0, qbr+n_div_2, qbc+n_div_2, n_div_2),
        0, 0,
        0, 0,
        n_div_2,
        n-1
    )
    # build the resulting matrix and return it
    c1 = add_matrices(sub_matrices(add_matrices(m1, m4), m5), m7)
    c2 = add_matrices(m3, m5)
    c3 = add_matrices(m2, m4)
    c4 = add_matrices(sub_matrices(add_matrices(m1, m3), m2), m6)
    result = [[0 for i in range(two_pow_n)] for j in range(two_pow_n)]
    # merge all quadrants c1-c4 into one matrix
    for i in range(n_div_2):
        result[i] = c1[i] + c2[i]
        result[i+n_div_2] = c3[i] + c4[i]
    return result


def multiply_by_strassens_and_brute_force(a, b, qar, qac, qbr, qbc, two_pow_n, n, cutoff):
    """
    Multiply 2 matrices together.
    a: 1st matrix
    b: 2nd matrix
    q_a: list of row and column index of quadrant from a
    q_b: list of row and column index of quadrant from b
    n: number of rows in matrices a and b
    """
    if n == cutoff:
        return multiply_by_brute_force(a, b, qar, qac, qbr, qbc, two_pow_n)
    # bit shift for better efficiency. i think the cpu was doing that anyway though
    n_div_2 = 1
    if n > 1:
        n_div_2 = 1 << (n-1)
    # get the length of the first row, as its length can be n
    if two_pow_n == 1:
        # just 2 numbers, so multiply them
        return [[a[0][0] * b[0][0]]]
    if two_pow_n == 2:
        # 2-by-2 matrices. we can now grab integers and operate on them
        # if a large matrix was passed in, grab the correct quadrant first
        m1 = (a[qar+0][qac+0] + a[qar+n_div_2][qac+n_div_2]) * (b[qbr+0][qbc+0] + b[qbr+n_div_2][qbc+n_div_2])
        m2 = (a[qar+n_div_2][qac+0] + a[qar+n_div_2][qac+n_div_2]) * b[qbr+0][qbc+0]
        m3 = a[qar+0][qac+0] * (b[qbr+0][qbc+n_div_2] - b[qbr+n_div_2][qbc+n_div_2])
        m4 = a[qar+n_div_2][qac+n_div_2] * (b[qbr+n_div_2][qbc+0] - b[qbr+0][qbc+0])
        m5 = (a[qar+0][qac+0] + a[qar+0][qac+n_div_2]) * b[qbr+n_div_2][qbc+n_div_2]
        m6 = (a[qar+n_div_2][qac+0] - a[qar+0][qac+0]) * (b[qbr+0][qbc+0] + b[qbr+0][qbc+n_div_2])
        m7 = (a[qar+0][qac+n_div_2] - a[qar+n_div_2][qac+n_div_2]) * (b[qbr+n_div_2][qbc+0] + b[qbr+n_div_2][qbc+n_div_2])
       # build the resulting matrix and return it
        return [[m1+m4-m5+m7, m3+m5],
                [m2+m4, m1+m3-m2+m6]]
    # get the weird m values
    # define size for quadrants
    # pass a as both arguments since we need to add 2 quadrants from the same matrix.
    m1 = multiply_by_strassens_and_brute_force(
        add_matrices_by_index(a, a, qar+0, qac+0, qar+n_div_2, qac+n_div_2, n_div_2),
        add_matrices_by_index(b, b, qbr+0, qbc+0, qbr+n_div_2, qbc+n_div_2, n_div_2),
        0, 0, # passing in an individual matrix, so just start at its 0, 0
        0, 0, # passing in an individual matrix, so just start at its 0, 0
        n_div_2,
        n-1,
        cutoff
    )
    m2 = multiply_by_strassens_and_brute_force(
        add_matrices_by_index(a, a, qar+n_div_2, qac+0, qar+n_div_2, qac+n_div_2, n_div_2),
        b,
        0, 0, # passing in an individual matrix, so just start at its 0, 0
        qbr+0, qbc+0, # passing in the entire matrix, so specify the correct quadrant
        n_div_2,
        n-1,
        cutoff
    )
    m3 = multiply_by_strassens_and_brute_force(
        a,
        sub_matrices_by_index(b, b, qbr+0, qbc+n_div_2, qbr+n_div_2, qbc+n_div_2, n_div_2),
        qar+0, qac+0,
        0, 0,
        n_div_2,
        n-1,
        cutoff
    )
    m4 = multiply_by_strassens_and_brute_force(
        a,
        sub_matrices_by_index(b, b, qbr+n_div_2, qbc+0, qbr+0, qbc+0, n_div_2),
        qar+n_div_2, qac+n_div_2,
        0, 0,
        n_div_2,
        n-1,
        cutoff
    )
    m5 = multiply_by_strassens_and_brute_force(
        add_matrices_by_index(a, a, qar+0, qac+0, qar+0, qac+n_div_2, n_div_2),
        b,
        0, 0,
        qbr+n_div_2, qbc+n_div_2,
        n_div_2,
        n-1,
        cutoff
    )
    m6 = multiply_by_strassens_and_brute_force(
        sub_matrices_by_index(a, a, qar+n_div_2, qac+0, qar+0, qac+0, n_div_2),
        add_matrices_by_index(b, b, qbr+0, qbc+0, qbr+0, qbc+n_div_2, n_div_2),
        0, 0,
        0, 0,
        n_div_2,
        n-1,
        cutoff
    )
    m7 = multiply_by_strassens_and_brute_force(
        sub_matrices_by_index(a, a, qar+0, qac+n_div_2, qar+n_div_2, qac+n_div_2, n_div_2),
        add_matrices_by_index(b, b, qbr+n_div_2, qbc+0, qbr+n_div_2, qbc+n_div_2, n_div_2),
        0, 0,
        0, 0,
        n_div_2,
        n-1,
        cutoff
    )
    # build the resulting matrix and return it
    c1 = add_matrices(sub_matrices(add_matrices(m1, m4), m5), m7)
    c2 = add_matrices(m3, m5)
    c3 = add_matrices(m2, m4)
    c4 = add_matrices(sub_matrices(add_matrices(m1, m3), m2), m6)
    result = [[0 for i in range(two_pow_n)] for j in range(two_pow_n)]
    # merge all quadrants c1-c4 into one matrix
    for i in range(n_div_2):
        result[i] = c1[i] + c2[i]
        result[i+n_div_2] = c3[i] + c4[i]
    return result
