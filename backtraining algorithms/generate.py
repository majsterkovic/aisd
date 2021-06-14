import random
import time

class AdjencyMatrix():

    def __init__(self, size):
        self.M = [[0]*size]
        for i in range(size):
            self.M.append([0]*size)

    def add_arc(self, A, B):
        self.M[A][B] = 1
        self.M[B][A] = 1

    def are_connected(self, A, B):
        if self.M[A][B] == 1 or self.M[B][A] == 1:
            return True
        return False

def gen_vertices(graph, n):
    pairs = []
    while len(pairs) < 3:
        pairs = []
        lv = random.sample(range(0, n), 3)
        lv.sort()
        #znajdowanie 3 niepolaczonych ze soba wierzcholkow
        for i in range(3):
            if not graph.are_connected(lv[i], lv[(i+1)%3]):
                pairs.append((lv[i], lv[(i+1)%3]))
    return pairs
        
def generate(size, percent):
    graf = AdjencyMatrix(size)
    l = [i for i in range(size)]
    random.shuffle(l)

    #łaczenie wierzcholków w cykl randomowo
    for i in range(size-1):
        graf.add_arc(l[i], l[i+1])
    graf.add_arc(l[size-1], l[0])

    #pozostala liczba krawedzi do stworzenia
    rem = percent*(size*(size-1))//2 - size
    rem = rem - rem%3

    #dodawanie krawedzi do pozostalych wierzcholkow z zachowaniem parzystego stopnia
    while rem > 0:
        connect = gen_vertices(graf, size)
        for i in range(3):
                graf.add_arc(connect[i][0], connect[i][1])
        rem -= 3

    #sprawdzanie, czy działa
    suma = 0
    subsum = [0]*size
    for i in range(size):
            suma += sum(graf.M[i])%2
            for j in range(size):
                subsum[j] += graf.M[i][j]
    for i in range(size):
        suma += subsum[i]%2
    print("{} {}: ".format(size, percent), suma)

    return graf.M

def save_mtrx_as_list(matrix, size, percent):
    f = open('{}_{}_Euler.txt'.format(size, int(100*percent)), 'w')
    for i in range(size):
        for j in range(i+1, size):
            if matrix[i][j] == 1:
                f.write("{} {}\n".format(i+1, j+1))
    f.close()

# start = time.time()
# generate(10, 0.3)
# end = time.time()
# print(end - start)

SIZES = [110, 120, 130, 140, 150, 160, 170, 180, 190, 200]
PERCENTS = [0.3, 0.5, 0.7]

for s in SIZES:
    for p in PERCENTS:
        generated = generate(s, p)
        save_mtrx_as_list(generated, s, p)

