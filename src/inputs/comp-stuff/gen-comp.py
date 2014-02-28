a = []
f = open("comp-out-sort","r")
for i in range(30):
    line = f.readline()
    if not line: break
    a.append(int(line))
f.close()
for i in range(1, 28):
    print a[i-1] * a[i] * a[i+1]

