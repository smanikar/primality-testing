a = []
f = open("col-1.txt","r")
for i in range(1, 30):
    line = f.readline()
    if not line: break
    a.append(int(line))
f.close()
for i in range(2, 25):
    print a[i-1] * a[i] * a[i+1]

