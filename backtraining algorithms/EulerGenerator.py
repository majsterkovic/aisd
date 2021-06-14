import random
import time

class AdjencyMatrix():

    def __init__(self, size):
        self.M = [[0]*size]
        for _ in range(size-1):
            self.M.append([0]*size)
        self.n = size

    def add_edge(self, A, B):
        if A!=B:
            self.M[A][B] = 1
            self.M[B][A] = 1

    def are_connected(self, A, B):
        if self.M[A][B] == 1 or self.M[B][A] == 1:
            return True
        return False

    def delete_edge(self, A, B):
        self.M[A][B] = 0
        self.M[B][A] = 0


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
        
def generate(size, percent, euler=True):
    graf = AdjencyMatrix(size)
    l = [i for i in range(size)]
    random.shuffle(l)

    #łaczenie wierzcholków w cykl randomowo
    for i in range(size-1):
        graf.add_edge(l[i], l[i+1])
    graf.add_edge(l[size-1], l[0])

    #pozostala liczba krawedzi do stworzenia
    rem = percent*(size*(size-1))//2 - size
    rem = rem - rem%3

    #dodawanie krawedzi do pozostalych wierzcholkow z zachowaniem parzystego stopnia
    while rem > 0:
        connect = gen_vertices(graf, size)
        for i in range(3):
                graf.add_edge(connect[i][0], connect[i][1])
        rem -= 3

    if not euler:
        a = random.randint(0, size-1)
        b = random.randint(0, size-1)
        while not graf.are_connected(a, b):
            a = random.randint(0, size-1)
            b = random.randint(0, size-1)
        graf.delete_edge(a,b)

    # #sprawdzanie, czy działa
    # suma = 0
    # subsum = [0]*size
    # for i in range(size):
    #         suma += sum(graf.M[i])%2
    #         for j in range(size):
    #             subsum[j] += graf.M[i][j]
    # for i in range(size):
    #     suma += subsum[i]%2
    # print("{} {}: ".format(size, percent), suma)

    return graf.M



# start = time.time()
# print(generate(10, 0.7))
# end = time.time()
# print(end - start)



