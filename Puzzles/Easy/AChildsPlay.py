import sys
import numpy as np


def is_obstacle(m, pos):
    return m[pos[0]][pos[1]] == '#'


w, h = [int(i) for i in input().split()]
n = int(input())

m = []
for i in range(h):
    line = input()
    m.append(line)
    if 'O' in line:
        # Found initial pos
        pos = np.array([i, line.index('O')])

# Initial direction
direction = np.array([-1,0])

# Rotation matrix
turn_clockwise = np.array([[0,-1],[1,0]])

# Walk m and remember
walks = []
first_loop = True
leftout = 0
for i in range(n):
    while is_obstacle(m, pos + direction):
        direction = direction @ turn_clockwise

    for x in walks:
        #print(x[0], pos, x[1], direction)
        if (x[0] == pos).all() and (x[1] == direction).all():
            if first_loop:
                first_loop = False
                leftout = len(walks)
                walks = []
            else:
                pos = walks[(n-leftout)%len(walks)][0]
                print( "%(x)d %(y)d" %{"x": pos[1], "y": pos[0]} )
                exit(0)

    walks.append([pos, direction])
    pos = pos + direction

print( "%(x)d %(y)d" %{"x": pos[1], "y": pos[0]} )