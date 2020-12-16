import sys
import math

rotations = input().split()
face_1 = input()
face_2 = input()

default = [['R', 'L'], ['U', 'D'], ['F', 'B']]
rubik = [['R', 'L'], ['U', 'D'], ['F', 'B']]
counter_clockwise = "'"
lock_R_L = 'x'
lock_U_D = 'y'
lock_F_B = 'z'


def rotate(rotation):
    [[x, y], k] = [[1, 2], 1] if rotation[0] == lock_R_L else \
        ([[0, 2], 2] if rotation[0] == lock_U_D else [[0, 1], 0])

    if len(rotation) == 2 and rotation[1] == counter_clockwise:
        k = 2 if rotation[0] == lock_R_L else \
            (0 if rotation[0] == lock_U_D else 1)

    [X, Y] = rubik[k]
    rubik[k] = [Y, X]
    [rubik[x], rubik[y]] = [rubik[y], rubik[x]]


for r in rotations:
    rotate(r)


def flatten(ll):
    res = []
    for x in ll:
        res.append(x[0])
        res.append(x[1])
    return res


def findFace(f):
    return flatten(default)[flatten(rubik).index(f)]


print(findFace(face_1))
print(findFace(face_2))
