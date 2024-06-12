import os


class FileLoader():
    def __init__(self):
        self.n = None
        self.n_squared = None
        self.pair_count = None
        self.matrix_list = []

    def load_file(self, file_name: str):
        # reset everything so loadFile can safely be called multiple times
        self.__init__()
        # open the file
        abs_path = os.path.dirname(__file__) + "/" + file_name
        with open(abs_path, 'r') as file:
            i = 0
            matrix_data = []
            for line in file:
                # header data
                if i == 0:
                    # header info, disregard
                    i += 1
                    continue
                elif i == 1:
                    # matrix metadata
                    i += 1
                    row_list = line.split(",")
                    self.n = int(row_list[0])
                    self.n_squared = int(row_list[1])
                    self.pair_count = int(row_list[2])
                # matrix data
                else:
                    if line[0] == ',' or line[0] == '~':
                        # end of matrix. add the local 2D array to the instance 3D array, then move on
                        self.matrix_list.append(matrix_data.copy())
                        matrix_data.clear()
                        continue
                    elif line[0] == '#':
                        # reached end of file, finish
                        return
                    else:
                        # matrix data, add the row to the local 2D array
                        row_list = [int(i) for i in line.split(",")]
                        matrix_data.append(row_list)

    def get_n(self):
        return self.n
    
    def get_n_squared(self):
        return self.n_squared

    def get_pair_count(self):
        return self.pair_count

    def get_matrix_list(self):
        return self.matrix_list
