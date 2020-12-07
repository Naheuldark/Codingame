import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

cpt = 0
m = []
for i in range(16):
    line = input()
    print(line, file=sys.stderr)
    m.append(line)

for line in m:
    garden = []
    i = 0
    while i < len(line):
        if line[i] in ['|', '+']:
            while i < len(line) and line[i] in ['|', '+']:
                garden.append(i)
                i += 1
        i += 1
    print(garden, file=sys.stderr)

    i = 0
    while i < len(garden)-1:
        if line.count('.', garden[i], garden[i+1]) == 0 and garden[i+1]-garden[i] > 1:
            cpt += line.count('o', garden[i], garden[i+1])
            print("Between", garden[i], garden[i+1], cpt, file=sys.stderr)
        i += 1

print(cpt)