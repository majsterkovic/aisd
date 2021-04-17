import matplotlib.pyplot as plt

res = open('cmake-build-debug/res.txt', 'r')

fig = plt.figure()
fig.set_size_inches(20, 16)

data = res.readlines()
methods = ["push", "remove"]
types = ["random", "sorted", "rev_sorted", "A", "V"]
d = {}
for m in methods:
    d[m] = {}
    for t in types:
        d[m][t] = []

n = 0
m = 0

for line in data:
    struct, method, typ, size, time = line.split(';')
    time = int(time)
    d[method][typ].append(time)

res.close()

print(d)