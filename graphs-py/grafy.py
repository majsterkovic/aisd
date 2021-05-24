from collections import deque
import copy
import random

import generator


class lista_krawedzi:
    def __init__(self):
        self.E = []

    def dodaj_luk(self, A, B):
        self.E.append((A, B))

    def usun_wierzcholek(self, A):
        for el in reversed(self.E):
            if A in el:
                self.E.remove(el)
    
    def sprawdz_czy_istnieje(self, A, B):
        if (A, B) in self.E:
            return True
        else:
            return False

    def rzad_grafu(self):
        V = set()
        for el in self.E:
            V.add(el[0])
            V.add(el[1])
        return len(V)

    def nastepnicy(self, A):
        return [el[1] for el in self.E if el[0] == A]


class lista_nastepnikow:
    def __init__(self):
        self.L = dict()

    def usun_wierzcholek(self, A):
        self.L[A] = []
        for key in self.L.keys():
            if A in self.L[key]:
                self.L[key].remove(A)

    def dodaj_luk(self, A, B):
        if A not in self.L:
            self.L[A] = []
            self.L[B] = []
        self.L[A].append(B)
        self.L[A].sort()

    def sprawdz_czy_istnieje(self, A, B):
        if A in self.L:
            if B in self.L[A]:
                return True
        else:
            return False

    def rzad_grafu(self):
        V = set()
        for key in self.L.keys():
            V.add(key)
            for el in self.L[key]:
                V.add(el)
        return len(V)

    def nastepnicy(self, A):
        return self.L[A]


class macierz_sasiedztwa:
    def __init__(self):
        self.M = []


    def wypisz(self):
        for i in range(len(self.M)):
            for j in range(len(self.M)):
                print(self.M[i][j], end="\t")
            print() 
        
    def dodaj_luk(self, A, B):
        if max(A,B) > len(self.M):
            N = [[0 for _ in range(max(A,B))] for _ in range(max(A,B))]
            for i in range(len(self.M)):
                for j in range(len(self.M)):
                    N[i][j] = self.M[i][j]
            self.M = copy.deepcopy(N)
        self.M[B-1][A-1] = -1
        self.M[A-1][B-1] = 1

    def sprawdz_czy_istnieje(self, A, B):
        if self.M[A-1][B-1] == 1:
            return True
        else:
            return False

    def rzad_grafu(self):
        return sum([1 for row in self.M if row.count(0) < len(self.M)])
    
    def nastepnicy(self, A):
        return [i+1 for i in range(len(self.M[A-1])) if self.M[A-1][i] == 1]

def Kahn(graf):
    wierzcholki = [v for v in range(1, graf.rzad_grafu()+1)]

    L = []
    # v szukamy o stopniu 0
    while len(wierzcholki) != 0:
        for v in wierzcholki:
            for u in wierzcholki:
                if v == u:
                    continue
                if v in graf.nastepnicy(u):
                    break
            else:
                break
        L.append(v)
        graf.usun_wierzcholek(v)
        wierzcholki.remove(v)
    print(L)

def visit(V, n, graf, L):
    if V[n] == 2:
        return
    V[n] = 1
    for m in graf.nastepnicy(n):
        visit(V, m, graf, L)
    V[n] = 2
    L.appendleft(n)


def DFS(graf):
    L = deque()
    wierzcholki = {}
    for i in range(1, graf.rzad_grafu()+1):
        wierzcholki[i] = 0

    while sum(list(wierzcholki.values())) != 2*len(wierzcholki):
        for el in wierzcholki:
            if wierzcholki[el] == 2:
                continue
            else:
                break
        visit(wierzcholki, el, graf, L)

    print(list(L))

graf1 = lista_nastepnikow()
# graf1.dodaj_luk(1, 2)
# graf1.dodaj_luk(1, 10)
# graf1.dodaj_luk(2, 3)
# graf1.dodaj_luk(2, 7)
# graf1.dodaj_luk(3, 4)
# graf1.dodaj_luk(4, 6)
# graf1.dodaj_luk(6, 9)
# graf1.dodaj_luk(8, 9)
# graf1.dodaj_luk(7, 9)
# graf1.dodaj_luk(8, 4)
# graf1.dodaj_luk(10, 5)
# graf1.dodaj_luk(10, 6)
# graf1.dodaj_luk(8, 6)
# graf1.dodaj_luk(5, 7)
# graf1.dodaj_luk(5, 2)
# graf1.dodaj_luk(7, 6)
# graf1.dodaj_luk(7, 8)

generator.start()

dane = []
f = open('tests/150.txt', 'r')
for line in f:
    dane.append((int(line.split()[0]), int(line.split()[1])))

#print(dane)

for i in range(len(dane)):
    graf1.dodaj_luk(dane[i][0], dane[i][1])

#print(graf1.E)

Kahn(graf1)