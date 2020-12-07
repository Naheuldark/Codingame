import sys
import math

def neigh(m, row, col):
    res = 0

    if row > 0 and m[row-1][col] == '0': res += 1
    if col < len(m[row])-1 and m[row][col+1] == '0': res += 1
    if row < len(m)-1 and m[row+1][col] == '0': res += 1
    if col > 0 and m[row][col-1] == '0': res += 1

    return str(res)

width, height = [int(i) for i in input().split()]
m = []
for i in range(height):
    line = input()
    m.append(line)


for row in range(height):
    for col in range(width):
        if m[row][col] == '0':
            print(neigh(m, row, col), end='')
        else:
            print('#', end='')
    print()
