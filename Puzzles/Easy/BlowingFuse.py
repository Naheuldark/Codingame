import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n, m, c = [int(i) for i in input().split()]
elec = [int(i) for i in input().split()]
seq = [int(i) for i in input().split()]

tot = 0
maxi = 0

for i in seq:
    tot += elec[i-1]
    elec[i-1] *= -1
    maxi = max(tot, maxi)

if (maxi > c):
    print("Fuse was blown.")
else:
    print("Fuse was not blown.")
    print("Maximal consumed current was " + str(maxi) + " A.")