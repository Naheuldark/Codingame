import sys
import math


def inside(px, py, poly):
    flag = 0
    for i in range(len(poly)):
        j = (i + 1) % len(poly)

        # Current point A
        ax = poly[i][0]
        ay = poly[i][1]

        # Successive point B
        bx = poly[j][0]
        by = poly[j][1]

        # 2D cross product
        d = (px - ax) * (by - ay) - (py - ay) * (bx - ax)
        flag |= 1 << (d <= 0)

        if (flag == 3):
            return False
    return True


poly = []
n = int(input())
for i in range(n):
    poly.append([int(j) for j in input().split()])

m = int(input())
for i in range(m):
    x, y = [int(j) for j in input().split()]
    print("hit" if inside(x, y, poly) else "miss")