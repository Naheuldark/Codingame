import sys
import math

n = int(input())


def p(c, n):
    res = ''
    for _ in range(n):
        res += c
    return res


print('.' + p(' ', 2*n-2) + p('*', 1))

for i in range(1, n):
    stars = p('*', 2*i+1)
    spaces = p(' ', 2*n-i-1)
    print(spaces + stars)

for i in range(n):
    stars = p('*', 2*i+1)
    spaces = p(' ', n-i-1)
    print(spaces + stars + spaces + ' ' + spaces + stars)