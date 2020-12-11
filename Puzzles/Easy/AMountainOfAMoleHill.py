import sys
import math

cpt = []


def printMap(m):
    for line in m:
        print(line, file=sys.stderr)
    print(file=sys.stderr)


def floodFillUtil(m, x, y, count):
    # Base cases
    if (x < 0 or x > 15 or y < 0 or y > 15 or m[x][y] == 1):
        return

    if (count and m[x][y] == 2):
        cpt.append(1)

    m[x][y] = 1

    floodFillUtil(m, x + 1, y, count)
    floodFillUtil(m, x + 1, y + 1, count)
    floodFillUtil(m, x, y + 1, count)
    floodFillUtil(m, x - 1, y + 1, count)
    floodFillUtil(m, x - 1, y, count)
    floodFillUtil(m, x - 1, y - 1, count)
    floodFillUtil(m, x, y - 1, count)
    floodFillUtil(m, x + 1, y - 1, count)


m = []
for i in range(16):
    r = []
    line = input()
    print(line, file=sys.stderr)
    for c in line:
        if (c in ['|', '+', '-']):
            r.append(1)
        elif (c in [' ', '.']):
            r.append(0)
        else:
            r.append(2)
    m.append(r)

for i in range(16):
    for j in range(16):
        if m[i][j] == 1:
            if j == 0:
                if m[i][1] != 1:
                    print(i, j, file=sys.stderr)
                    floodFillUtil(m, i, 1, True)
                    printMap(m)
            elif j < 15:
                if m[i][j+1] != 1 and m[i][j-1] != 1:
                    print(i, j, file=sys.stderr)
                    floodFillUtil(m, i, j+1, True)
                    printMap(m)
        elif m[i][j] == 2:
            m[i][j] = 0
    print(len(cpt), file=sys.stderr)

print(len(cpt))
