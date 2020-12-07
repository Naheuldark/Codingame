import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())

# Write an answer using print
# To debug: print("Debug messages...", file=sys.stderr, flush=True)

for x in range(n+1, 2*n+1):
    if (n * x)%(x - n) == 0:
        y = int((n * x) / (x - n))
        print("1/{} = 1/{} + 1/{}".format(n, y, x))