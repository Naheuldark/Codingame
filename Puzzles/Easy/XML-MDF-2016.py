import sys
import math
import re

depth = 0
weights = {}
sequence = re.sub('-.', '-', input())
for c in sequence:
    if c not in weights and c != '-':
        weights[c] = 0
    if c == '-':
        depth -= 1
    else:
        depth += 1
        weights[c] += 1 / depth

print(sorted(weights.items(), key=lambda item: item[1])[-1][0])
