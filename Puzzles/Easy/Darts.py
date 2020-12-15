import sys
import math


def score(x, y, r):
    if (abs(x) + abs(y) <= r):  # Diamond
        return 15
    elif (math.hypot(x, y) <= r):  # Circle
        return 10
    elif (-r <= min(x, y) and max(x, y) <= r):  # Square
        return 5
    else:  # Fail
        return 0


r = int(input()) / 2

players = {}
n = int(input())
for i in range(n):
    name = input()
    players[name] = 0

t = int(input())
for i in range(t):
    inputs = input().split()
    throw_name = inputs[0]
    throw_x = int(inputs[1])
    throw_y = int(inputs[2])
    players[throw_name] += score(throw_x, throw_y, r)

for name, score in sorted(players.items(), key=lambda c: c[1], reverse=True):
    print(name, score)
