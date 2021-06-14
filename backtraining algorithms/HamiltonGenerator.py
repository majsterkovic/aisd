import random
import time
import math

class AdjencyMatrix():

    def __init__(self, size):
        self.M = [[0]*size]
        for i in range(size):
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

def generate(size, percent, hamilton=True):
    n = math.ceil(size*(size-1)/2)
    #print(n)
    if hamilton:
        graf = AdjencyMatrix(size)
    else:
        graf = AdjencyMatrix(size+1)
    h = [i for i in range(size)]
    random.shuffle(h)

    for i in range(size):
        graf.add_edge(h[i], h[(i+1)%size])

    l = [0]*n
    

    goal = math.ceil(n*percent)-size
    #print("ile ma byc:", goal+size)

    while goal > 0:
        a = random.randint(0, size-1)
        b = random.randint(0, size-1)
        while graf.are_connected(a, b) or a==b:
            a = random.randint(0, size-1)
            b = random.randint(0, size-1)
        graf.add_edge(a, b)
        goal -= 1


    if not hamilton:
        graf.add_edge(random.randint(0, size-1), size)
    
    return graf.M

    # v = 0
    # for i in range(size+1):
    #     for j in range(i+1):
    #         print(graf.M[i][j], end=" ")
    #         if(graf.M[i][j]==1):
    #             v+=1
    #     print("")

    # print("ile jest:", v)
    
generate(100, 0.5, hamilton=False)
