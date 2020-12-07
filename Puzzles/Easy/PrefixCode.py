import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())

dec = {}
for i in range(n):
    inputs = input().split()
    b = inputs[0]
    c = chr(int(inputs[1]))
    dec[b] = c
s = input()

i = 0
msg = ""
while i < len(s):
    found = False
    for k,v in dec.items():
        if s.find(k,i) == i:
            msg += v
            i += len(k)
            found = True
            break
    if not found:
        print("DECODE FAIL AT INDEX " + str(i))
        exit(0)

print(msg)