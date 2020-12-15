import sys
import math


def get_dist(a, b):
    return math.hypot(a[0]-b[0], a[1]-b[1])


def shortest_path(G, c):
    minDist = math.inf
    mini = None
    for i in range(len(G)):
        dist = get_dist(c, G[i])
        if (minDist > dist):
            minDist = dist
            mini = i
    return (mini, minDist)


G = []
n = int(input())
for i in range(n):
    G.append([int(j) for j in input().split()])

first = G.pop(0)
tot = 0
cur = first

while len(G) > 0:
    ndx, dist = shortest_path(G, cur)
    tot += dist
    cur = G.pop(ndx)

print(round(tot + get_dist(cur, first)))