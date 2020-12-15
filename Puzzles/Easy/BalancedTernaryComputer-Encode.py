import sys
import math

n = int(input())
res = ''

if n == 0:
    print(0)
else:
    while n != 0:
        r = (n + 30000) % 3
        n -= [0, 1, -1][r]
        n = int(n / 3) | 0
        res = '01T'[r] + res

    print(res)