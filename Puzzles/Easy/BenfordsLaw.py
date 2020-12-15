import sys
import math
import re

transactions = {
    0: 0,
    1: 0,
    2: 0,
    3: 0,
    4: 0,
    5: 0,
    6: 0,
    7: 0,
    8: 0,
    9: 0
}
fraudulent = False

freq = [.0, .301, .176, .125, .097, .079, .067, .058, .051, .046]

n = int(input())
for i in range(n):
    key = int(re.search('\\d', input()).group(0))
    transactions[key] += 1

for i in range(len(freq)):
    if (abs(freq[i] - transactions[i] / n) > .1):
        print("true")
        exit(0)

print("false")
