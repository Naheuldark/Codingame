import sys
import math


def happy(n: int) -> bool:
    s = set()
    while(n not in s):
        s.add(n)
        v = 0
        while (n > 0):
            v += pow(n % 10, 2)
            n = n // 10
        n = v
    return n == 1


for _ in range(int(input())):
    n = int(input())
    print(n, end=' ')
    print(':)' if happy(n) else ':(')