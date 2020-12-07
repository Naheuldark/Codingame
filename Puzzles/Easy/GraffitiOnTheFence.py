import sys
import math

l = int(input())
n = int(input())
a = []
for i in range(n):
    st, ed = [int(j) for j in input().split()]
    a.append((st, ed))

b = []
for begin, end in sorted(a):
    if b and b[-1][1] > begin - 1:
        b[-1][1] = max(b[-1][1], end)
    else:
        b.append([begin, end])

if len(b) == 1 and b[0][0] == 0 and b[0][1] == l:
    print("All painted")
    exit(0)

if b[0][0] > 0:
    print("0", end=' ')

for i in range(len(b)):
    if b[i][0] > 0: print(b[i][0])
    if b[i][1] < l: print(b[i][1], end=' ')

if b[len(b)-1][1] < l:
    print(l)