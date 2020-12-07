import sys
import math
import re

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

splash = [-1, 0, 1]

n = int(input())
for i in range(n):
    line = input()
    print(line, file=sys.stderr)
    drops = re.findall('f.f|f{1,2}', line)
    print(len(drops));  
