import sys
import math

size = int(input())
angle = int(input())
shape = [input()[::2] for _ in range(size)]

for _ in range(4 - ((angle % 360 // 90 + 1) % 4)):
    shape = list(zip(*reversed(shape)))

for i in range(size):
    print('{0}{1}{0}'.format(
        ' ' * (size - i - 1),
        ' '.join([shape[i - j][j] for j in range(i + 1)])
    ))

for i in range(1, size):
    print('{0}{1}{0}'.format(
        ' ' * i,
        ' '.join([shape[size - j - 1][i + j] for j in range(size - i)])
    ))
