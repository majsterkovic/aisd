import EulerGenerator as eg
import HamiltonGenerator as hg

def save_mtrx_as_list(matrix, size, percent, typ):
    f = open('cmake-build-debug/{}_{}_{}.txt'.format(size, int(100*percent), typ), 'w')
    for i in range(len(matrix)):
        for j in range(i+1, len(matrix[i])):
            if matrix[i][j] == 1:
                f.write("{} {}\n".format(i+1, j+1))
    f.close()

def create_tests(SIZES, PERCENTS):
    for s in SIZES:
        for p in PERCENTS:
            generated1 = hg.generate(s, p, hamilton=True)
            save_mtrx_as_list(generated1, s, p, "Hamilton")
            generated2 = eg.generate(s-1, p, euler=False)
            save_mtrx_as_list(generated2, s, p, "Euler")

SIZES = [110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
PERCENTS = [0.3, 0.5, 0.7]

create_tests(SIZES, PERCENTS)