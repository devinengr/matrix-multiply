import unittest
from file_loader import FileLoader


class TestFileLoader(unittest.TestCase):
    """
    Files must load successfully and put the data into a 3D array.
    1D arrays represent one matrix row.
    2D arrays reprsent a full matrix (a list of rows).
    3D arrays represent a list of matrices.
    """
    def __init__(self, methodName: str = "runTest") -> None:
        super().__init__(methodName)
        self.file = FileLoader()

    def setUp(self) -> None:
        """Runs before each test."""
        super().setUp()
        self.file.loadFile("../res/example - single matrix pair.csv")

    def test_load_success(self) -> None:
        """A file must be loaded correctly."""
        self.assertIsNotNone(self.file.getN())
        self.assertIsNotNone(self.file.getNSquared())
        self.assertIsNotNone(self.file.getPairCount())
        self.assertTrue(len(self.file.getMatrixList()) != 0)

    def test_first_data_row(self) -> None:
        """The first row of data (5,32,1) should be stored correctly."""
        self.assertEqual(5, self.file.getN())
        self.assertEqual(32, self.file.getNSquared())
        self.assertEqual(1, self.file.getPairCount())

    def test_matrix_count(self) -> None:
        """The number of matrices in the list must match the file."""
        self.assertEqual(2, len(self.file.getMatrixList()))

    def test_row_count(self) -> None:
        """Test that rows=2^n"""
        self.assertEqual(32, len(self.file.getMatrixList()[0]))

    def test_column_count(self) -> None:
        """Test that columns=2^n"""
        self.assertEqual(32, len(self.file.getMatrixList()[0][0]))

    def test_matrix_borders(self) -> None:
        """Test the edges of the matrix."""
        self.assertEqual(2, self.file.getMatrixList()[0][0][0])
        self.assertEqual(4, self.file.getMatrixList()[0][0][31])
        self.assertEqual(1, self.file.getMatrixList()[0][31][0])
        self.assertEqual(8, self.file.getMatrixList()[0][31][31])

    def test_matrix_pairs(self) -> None:
        """Ensure the arrays match up correctly."""
        self.assertEqual(2, self.file.getMatrixList()[0][0][0])
        self.assertEqual(3, self.file.getMatrixList()[1][0][0])
        self.assertEqual(4, self.file.getMatrixList()[0][0][31])
        self.assertEqual(8, self.file.getMatrixList()[1][0][31])
