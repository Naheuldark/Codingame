import sys
import math


n = int(input())
for i in range(n):
    card = input().replace(' ', '')[::-1]

    tot = 0
    odd = True
    for c in card:
        if odd:
            tot += int(c)
        else:
            q = 2*int(c)
            tot += q if q < 10 else q-9
        odd = not odd

    if tot % 10 == 0:
        print("YES")
    else:
        print("NO")
