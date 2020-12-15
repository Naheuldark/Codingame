import sys
import math


x = int(input())
n = int(input())
m = sorted(map(int, input().split()), reverse=True)

work = 0
for i in range(n):
    l = i // x
    work += l * 0.65 * m[i]
print('%.3f' % round(work, 3))