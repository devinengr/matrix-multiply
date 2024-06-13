from file_loader import FileLoader
import matrix_multiply
import time


def run_brute_force(two_pow_n, f, pair_index_start):
    print("Multiplying " + str(two_pow_n) + "-by-" + str(two_pow_n) + " matrix by the brute force algorithm...")
    # start timer
    time_start = time.time()
    matrix_multiply.multiply_by_brute_force(
        f.get_matrix_list()[pair_index_start],
        f.get_matrix_list()[pair_index_start + 1],
        0, 0,
        0, 0,
        two_pow_n)
    # end timer
    time_end = time.time()
    return (time_end - time_start)


def run_strassens(two_pow_n, f, n, pair_index_start):
    print("Multiplying " + str(two_pow_n) + "-by-" + str(two_pow_n) + " matrix by Strassen's algorithm...")
    # start timer
    time_start = time.time()
    matrix_multiply.multiply_by_strassens(
        f.get_matrix_list()[pair_index_start],
        f.get_matrix_list()[pair_index_start + 1],
        0, 0,
        0, 0,
        two_pow_n,
        n)
    # end timer
    time_end = time.time()
    return (time_end - time_start)


def run_both(two_pow_n, f, n, pair_index_start):
    cutoff = int(input("Please specify a cutoff: "))
    print("Multiplying " + str(two_pow_n) + "-by-" + str(two_pow_n) + " matrix by Strassen's + brute force algorithms with cutoff " + str(cutoff) + "...")
    # start timer
    time_start = time.time()
    matrix_multiply.multiply_by_strassens_and_brute_force(
        f.get_matrix_list()[pair_index_start],
        f.get_matrix_list()[pair_index_start + 1],
        0, 0,
        0, 0,
        two_pow_n,
        n,
        cutoff)
    # end timer
    time_end = time.time()
    return (time_end - time_start)


if __name__ == "__main__":
    # get input from user
    n = int(input("Please enter a value for n: "))
    alg = int(input("Type...\t'0' for brute force\n\t'1' for strassen's\n\t'2' for both\n"))
    two_pow_n = pow(2, n)
    # load file, get data
    f = FileLoader()
    f.load_file("../res/matrices of n " + str(n) + ".csv")
    pair_count = f.get_pair_count()
    # declare start time (but don't start it yet; user will be prompted for input if they pick both algorithms with a cutoff)
    time_elapsed = 0
    print("-----")
    # begin algorithms. do this for every pair in the file
    for i in range(pair_count):
        if alg == 0:
            time_elapsed = run_brute_force(two_pow_n, f, i)
        elif alg == 1:
            time_elapsed = run_strassens(two_pow_n, f, n, i)
        elif alg == 2:
            time_elapsed = run_both(two_pow_n, f, n, i)
        # print time elapsed
        print("Pair " + str(i) + " complete. Time taken: " + str(time_elapsed) + " seconds")
        print("-----")
    # done
    print("!!! FINISHED ALL PAIRS !!!")
 