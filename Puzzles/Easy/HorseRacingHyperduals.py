import sys
import math

horses = []
mindist = math.inf

n = int(input())
for i in range(n):
    vi, ei = [int(j) for j in input().split()]
    for vj, ej in horses:
        dist = abs(vi - vj) + abs(ei - ej)
        mindist = min(mindist, dist)
    horses.append((vi, ei))
print(mindist)
