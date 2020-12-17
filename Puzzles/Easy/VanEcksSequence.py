import sys
import math
from itertools import islice


def van_eck(a1):
    n, seen, val = 0, {}, a1
    while True:
        yield val
        last = {val: n}
        val = n - seen.get(val, n)
        seen.update(last)
        n += 1


a1 = int(input())
n = int(input())
print(list(islice(van_eck(a1), n))[-1])
