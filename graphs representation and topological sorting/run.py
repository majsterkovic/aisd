import operator

with open('cmake-build-debug/res.csv', 'r') as file:
    lines = file.readlines()

data = []
names = set()
Kahn = {}
DFS = {}

for el in lines:
    data.append(el.strip().split(";"))

for i in range(len(data)):
    data[i][2] = int(data[i][2])
    

s = sorted(data, key=operator.itemgetter(0, 2))

for el in s:
    print(el)

for el in s:
    names.add(el[0])
    if el[1] == "DFS":
        DFS.setdefault(el[2], []).append(el[3])
    if el[1] == "Kahn":
        Kahn.setdefault(el[2], []).append(el[3])

with open('Kahn.csv', 'w') as o:
    o.write("rzad_grafu" + ";")
    for name in list(sorted(names)):
        o.write(name + ";")
    o.write("\n")
    for key in Kahn.items():
        o.write(str(key[0]) + ";")
        for val in key[1]:
            o.write(str(val) + ";")
        o.write("\n")

with open('DFS.csv', 'w') as o:
    o.write("rzad_grafu" + ";")
    for name in list(sorted(names)):
        o.write(name + ";")
    o.write("\n")
    for key in DFS.items():
        o.write(str(key[0]) + ";")
        for val in key[1]:
            o.write(str(val) + ";")
        o.write("\n")

