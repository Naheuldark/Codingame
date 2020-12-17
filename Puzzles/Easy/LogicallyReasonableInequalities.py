import sys
import math

n = int(input())
eq = {}
val = n
for i in range(n):
    row = input().replace(' ', '').split('>')

    if row[0] not in eq:
        eq[row[0]] = n-i
    if row[1] not in eq:
        eq[row[1]] = n-i-1

    if eq[row[0]] < eq[row[1]]:
        print("contradiction")
        exit(0)

print("consistent")
