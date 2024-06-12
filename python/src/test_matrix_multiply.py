import unittest
from file_loader import FileLoader
import matrix_multiply


class TestMatrixMultiply(unittest.TestCase):
    """
    Matrix multiplication of n-by-n matrices must produce the correct result for both
    brute-force and Strassen's algorithms, and account for the property that matrix
    multiplication is not commutative.
    """
    def __init__(self, methodName: str = "runTest"):
        super().__init__(methodName)
        self.file = FileLoader()

    def setUp(self):
        """Runs before each test."""
        super().setUp()
        self.file.loadFile("../res/example - single matrix pair.csv")

    def test_add_matrices(self):
        """Test that 2 matrices are properly added together."""
        a = [[1, 2], [3, 4]]
        b = [[1, 2], [3, 4]]
        c = [[2, 4], [6, 8]]
        self.assertEqual(c, matrix_multiply.add_matrices(a, b))
        a = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
        b = [[9, 8, 7, 6], [5, 4, 3, 2], [9, 8 , 7, 6], [5, 4, 3, 2]]
        caa = [[2, 4, 6, 8], [10, 12, 14, 16], [18, 20, 22, 24], [26, 28, 30, 32]]
        self.assertEqual(caa, matrix_multiply.add_matrices(a, a))

    def test_sub_matrices(self):
        """Test that 2 matrices are properly subtracted."""
        a = [[1, 2], [3, 4]]
        b = [[1, 2], [3, 4]]
        c = [[0, 0], [0, 0]]
        self.assertEqual(c, matrix_multiply.sub_matrices(a, b))
        a = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
        b = [[9, 8, 7, 6], [5, 4, 3, 2], [9, 8 , 7, 6], [5, 4, 3, 2]]
        caa = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
        self.assertEqual(caa, matrix_multiply.sub_matrices(a, a))

    def test_add_matrices_by_index(self):
        """Test that 2 submatrices are added properly."""
        a = [[1, 2], [3, 4]]
        b = [[1, 2], [3, 4]]
        c = [[2, 4], [6, 8]]
        self.assertEqual(c, matrix_multiply.add_matrices_by_index(a, b, 0, 0, 0, 0, 2))
        self.assertEqual([[8]], matrix_multiply.add_matrices_by_index(a, b, 1, 1, 1, 1, 1))
        a = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
        b = [[9, 8, 7, 6], [5, 4, 3, 2], [9, 8 , 7, 6], [5, 4, 3, 2]]
        c22 = [[18, 18], [18, 18]]
        c02 = [[8, 8], [8, 8]]
        caa = [[2, 4, 6, 8], [10, 12, 14, 16], [18, 20, 22, 24], [26, 28, 30, 32]]
        self.assertEqual(c22, matrix_multiply.add_matrices_by_index(a, b, 2, 2, 2, 2, 2))
        self.assertEqual(c02, matrix_multiply.add_matrices_by_index(a, b, 0, 0, 2, 2, 2))
        self.assertEqual(caa, matrix_multiply.add_matrices_by_index(a, a, 0, 0, 0, 0, 4))

    def test_sub_matrices_by_index(self):
        """Test that 2 submatrices are subtracted properly."""
        a = [[1, 2], [3, 4]]
        b = [[1, 2], [3, 4]]
        c = [[0, 0], [0, 0]]
        self.assertEqual(c, matrix_multiply.sub_matrices_by_index(a, b, 0, 0, 0, 0, 2))
        self.assertEqual([[0]], matrix_multiply.sub_matrices_by_index(a, b, 1, 1, 1, 1, 1))
        a = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
        b = [[9, 8, 7, 6], [5, 4, 3, 2], [9, 8 , 7, 6], [5, 4, 3, 2]]
        c22 = [[4, 6], [12, 14]]
        c02 = [[-6, -4], [2, 4]]
        caa = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
        self.assertEqual(c22, matrix_multiply.sub_matrices_by_index(a, b, 2, 2, 2, 2, 2))
        self.assertEqual(c02, matrix_multiply.sub_matrices_by_index(a, b, 0, 0, 2, 2, 2))
        self.assertEqual(caa, matrix_multiply.sub_matrices_by_index(a, a, 0, 0, 0, 0, 4))
    
    def test_brute_force(self):
        """Test brute-force for several n values, including reversing the order of input matrices."""
        a = [[7]]
        b = [[5]]
        c = [[35]]
        self.assertEqual(c, matrix_multiply.multiply_by_brute_force(a, b, 0, 0, 0, 0, 1))
        self.assertEqual(c, matrix_multiply.multiply_by_brute_force(b, a, 0, 0, 0, 0, 1))
        a = [[1, 2], [3, 4]]
        b = [[2, 0], [1, 2]]
        c1 = [[4, 4], [10, 8]]
        c2 = [[2, 4], [7, 10]]
        self.assertEqual(c1, matrix_multiply.multiply_by_brute_force(a, b, 0, 0, 0, 0, 2))
        self.assertEqual(c2, matrix_multiply.multiply_by_brute_force(b, a, 0, 0, 0, 0, 2))
        a = [[5, 3, 4], [2, 5, 3], [1, 6, 9]]
        b = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
        c1 = [[45, 57, 69], [43, 53, 63], [88, 104, 120]]
        c2 = [[12, 31, 37], [36, 73, 85], [60, 115, 133]]
        self.assertEqual(c1, matrix_multiply.multiply_by_brute_force(a, b, 0, 0, 0, 0, 3))
        self.assertEqual(c2, matrix_multiply.multiply_by_brute_force(b, a, 0, 0, 0, 0, 3))

    def test_strassens(self) -> None:
        """Test Strassen's algorithm for several n values, including reversing the order of input matrices."""
        a = [[7]]
        b = [[5]]
        c = [[35]]
        self.assertEqual(c, matrix_multiply.multiply_by_strassens(a, b, 0, 0, 0, 0, 1, 0))
        self.assertEqual(c, matrix_multiply.multiply_by_strassens(b, a, 0, 0, 0, 0, 1, 0))
        # 2-by-2 matrix
        a = [[1, 2], [3, 4]]
        b = [[2, 0], [1, 2]]
        c1 = [[4, 4], [10, 8]]
        c2 = [[2, 4], [7, 10]]
        self.assertEqual(c1, matrix_multiply.multiply_by_strassens(a, b, 0, 0, 0, 0, 2, 1))
        self.assertEqual(c2, matrix_multiply.multiply_by_strassens(b, a, 0, 0, 0, 0, 2, 1))
        # 4-by-4 matrix
        a = [[5, 3, 4, 2], [3, 0, 9, 9], [1, 1, 2, 3], [4, 5, 9, 7]]
        b = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
        c1 = [[82, 96, 110, 124], [201, 222, 243, 264], [63, 70, 77, 84], [201, 226, 251, 276]]
        c2 = [[30, 26, 64, 57], [82, 62, 160, 141], [134, 98, 256, 225], [186, 134, 352, 309]]
        self.assertEqual(c1, matrix_multiply.multiply_by_strassens(a, b, 0, 0, 0, 0, 4, 2))
        self.assertEqual(c2, matrix_multiply.multiply_by_strassens(b, a, 0, 0, 0, 0, 4, 2))
        # 8-by-8 matrix
        a = [[9, 6, 6, 9, 7, 6, 3, 1],
             [9, 4, 2, 9, 1, 7, 5, 4],
             [8, 6, 7, 4, 8, 0, 4, 0],
             [6, 5, 2, 5, 2, 0, 4, 2],
             [4, 2, 6, 2, 9, 0, 3, 2],
             [0, 0, 1, 5, 2, 8, 8, 3],
             [2, 1, 8, 4, 1, 0, 7, 2],
             [2, 5, 5, 6, 9, 8, 0, 2]]
        b = [[7, 0, 8, 5, 7, 7, 3, 8],
             [9, 8, 0, 5, 0, 4, 9, 2],
             [4, 5, 1, 6, 0, 2, 1, 0],
             [0, 0, 2, 9, 3, 5, 9, 9],
             [5, 1, 9, 5, 9, 5, 4, 6],
             [3, 2, 8, 7, 4, 7, 7, 1],
             [2, 5, 4, 1, 9, 2, 8, 8],
             [5, 4, 0, 8, 6, 8, 5, 1]]
        c = [[205, 116, 219, 280, 210, 235, 267, 238],
             [163, 98, 177, 249, 196, 224, 259, 218],
             [186, 111, 167, 192, 176, 162, 185, 192],
             [123, 80, 94, 142, 123, 125, 160, 149],
             [131, 78, 135, 148, 154, 125, 124, 134],
             [69, 75, 125, 149, 155, 133, 189, 132],
             [84, 92, 69, 127, 110, 89, 129, 118],
             [158, 98, 178, 236, 157, 191, 212, 144]]
        self.assertEqual(c, matrix_multiply.multiply_by_strassens(a, b, 0, 0, 0, 0, 8, 3))
    
    def test_strassens_and_brute_force(self) -> None:
        """
        Test Strassen's algorithm (with a cutoff that starts brute force) for several n values, including reversing
        the order of input matrices. Also test for different cutoffs.
        """
        a = [[7]]
        b = [[5]]
        c = [[35]]
        self.assertEqual(c, matrix_multiply.multiply_by_strassens_and_brute_force(a, b, 0, 0, 0, 0, 1, 0, 1))
        self.assertEqual(c, matrix_multiply.multiply_by_strassens_and_brute_force(b, a, 0, 0, 0, 0, 1, 0, 0))
        # 2-by-2 matrix
        a = [[1, 2], [3, 4]]
        b = [[2, 0], [1, 2]]
        c1 = [[4, 4], [10, 8]]
        c2 = [[2, 4], [7, 10]]
        self.assertEqual(c2, matrix_multiply.multiply_by_strassens_and_brute_force(b, a, 0, 0, 0, 0, 2, 1, 2))
        self.assertEqual(c2, matrix_multiply.multiply_by_strassens_and_brute_force(b, a, 0, 0, 0, 0, 2, 1, 1))
        self.assertEqual(c2, matrix_multiply.multiply_by_strassens_and_brute_force(b, a, 0, 0, 0, 0, 2, 1, 0))
        # 4-by-4 matrix
        a = [[5, 3, 4, 2], [3, 0, 9, 9], [1, 1, 2, 3], [4, 5, 9, 7]]
        b = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]
        c1 = [[82, 96, 110, 124], [201, 222, 243, 264], [63, 70, 77, 84], [201, 226, 251, 276]]
        c2 = [[30, 26, 64, 57], [82, 62, 160, 141], [134, 98, 256, 225], [186, 134, 352, 309]]
        self.assertEqual(c2, matrix_multiply.multiply_by_strassens_and_brute_force(b, a, 0, 0, 0, 0, 4, 2, 4))
        self.assertEqual(c1, matrix_multiply.multiply_by_strassens_and_brute_force(a, b, 0, 0, 0, 0, 4, 2, 2))
        self.assertEqual(c1, matrix_multiply.multiply_by_strassens_and_brute_force(a, b, 0, 0, 0, 0, 4, 2, 1))
        self.assertEqual(c1, matrix_multiply.multiply_by_strassens_and_brute_force(a, b, 0, 0, 0, 0, 4, 2, 0))
        # 8-by-8 matrix
        a = [[9, 6, 6, 9, 7, 6, 3, 1],
             [9, 4, 2, 9, 1, 7, 5, 4],
             [8, 6, 7, 4, 8, 0, 4, 0],
             [6, 5, 2, 5, 2, 0, 4, 2],
             [4, 2, 6, 2, 9, 0, 3, 2],
             [0, 0, 1, 5, 2, 8, 8, 3],
             [2, 1, 8, 4, 1, 0, 7, 2],
             [2, 5, 5, 6, 9, 8, 0, 2]]
        b = [[7, 0, 8, 5, 7, 7, 3, 8],
             [9, 8, 0, 5, 0, 4, 9, 2],
             [4, 5, 1, 6, 0, 2, 1, 0],
             [0, 0, 2, 9, 3, 5, 9, 9],
             [5, 1, 9, 5, 9, 5, 4, 6],
             [3, 2, 8, 7, 4, 7, 7, 1],
             [2, 5, 4, 1, 9, 2, 8, 8],
             [5, 4, 0, 8, 6, 8, 5, 1]]
        c = [[205, 116, 219, 280, 210, 235, 267, 238],
             [163, 98, 177, 249, 196, 224, 259, 218],
             [186, 111, 167, 192, 176, 162, 185, 192],
             [123, 80, 94, 142, 123, 125, 160, 149],
             [131, 78, 135, 148, 154, 125, 124, 134],
             [69, 75, 125, 149, 155, 133, 189, 132],
             [84, 92, 69, 127, 110, 89, 129, 118],
             [158, 98, 178, 236, 157, 191, 212, 144]]
        # Test various cutoffs
        self.assertEqual(c, matrix_multiply.multiply_by_strassens_and_brute_force(a, b, 0, 0, 0, 0, 8, 3, 8))
        self.assertEqual(c, matrix_multiply.multiply_by_strassens_and_brute_force(a, b, 0, 0, 0, 0, 8, 3, 4))
        self.assertEqual(c, matrix_multiply.multiply_by_strassens_and_brute_force(a, b, 0, 0, 0, 0, 8, 3, 2))
        self.assertEqual(c, matrix_multiply.multiply_by_strassens_and_brute_force(a, b, 0, 0, 0, 0, 8, 3, 1))
        self.assertEqual(c, matrix_multiply.multiply_by_strassens_and_brute_force(a, b, 0, 0, 0, 0, 8, 3, 0))
