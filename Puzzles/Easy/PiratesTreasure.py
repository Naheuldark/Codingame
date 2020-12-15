import sys
import math


w = int(input())
h = int(input())


def isObstacle(m, x, y):
    return m[x][y] == 1 if 0 <= x < h and 0 <= y < w else True


m = []
for i in range(h):
    m.append([int(j) for j in input().split()])

for x in range(h):
    for y in range(w):
        if m[x][y] == 0 and \
            isObstacle(m, x-1, y-1) and isObstacle(m, x-1, y) and isObstacle(m, x-1, y+1) and \
            isObstacle(m, x, y-1) and isObstacle(m, x, y+1) and \
            isObstacle(m, x+1, y-1) and isObstacle(m, x+1, y) and isObstacle(m, x+1, y+1):
            print(y, x)
            exit(0)