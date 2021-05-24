import random
import math

SIZES = [150]

def generate(k):
    L = []
    v = [0 for _ in range(k*(k-1)//2)]
    for i in range(math.ceil(0.5*k*(k-1)/2)):
        v[i] = 1
    random.shuffle(v)


    counter = 0
    for i in range(k):
        for j in range(i):
            if v[counter] == 1:
                L.append((i+1, j+1))
            counter += 1
    return L

def start():
    for s in SIZES:
        f = open('tests/{}.txt'.format(s), 'w')
        f.write('{}'.format('\n'.join([str(x[0]) + ' ' + str(x[1]) for x in generate(s)])))
        f.close()

