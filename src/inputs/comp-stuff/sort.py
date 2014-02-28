a = []
f = open("comp-out","r")
for i in range(30):
    line = f.readline()
    if not line: break
    a.append(int(line))
f.close()
a.sort()
for i in range(30):
    print a[i]

