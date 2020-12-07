import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

s = 0
g = []
for i in range(9):
    r = []
    for j in input().split():
        n = int(j)
        s += n
        r.append(n)
    g.append(r)

for i in range(9):
    row = set()
    for j in range(9):
        row.add(g[i][j])
    if len(row) != 9: 
        print("false")
        exit(0)

for j in range(9):
    col = set()
    for i in range(9):
        col.add(g[i][j])
    if len(col) != 9: 
        print("false")
        exit(0)

for i in range(3):
    for j in range(3):
        sub = set()
        for ii in range(3):
            for jj in range(3):
                sub.add(g[3*i+ii][3*j+jj])
        if len(sub) != 9:
            print("false")
            exit(0)

res = True if s == 405 else False
print("true" if res else "false")