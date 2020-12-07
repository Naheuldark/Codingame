import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

orb_size_min, orb_size_max = [int(i) for i in input().split()]
glowing_size_1, glowing_size_2 = [int(i) for i in input().split()]

surface = math.pow(glowing_size_1 * 0.5, 3) + math.pow(glowing_size_2 * 0.5, 3)
low = orb_size_min
high = orb_size_max
i = glowing_size_1
j = glowing_size_2

found = False

while high >= low:
    cal = math.pow(high * 0.5, 3) + math.pow(low * 0.5, 3)

    if cal == surface:
        i = high
        j = low
        if i != glowing_size_2 or j != glowing_size_1:
            found = True
            break
        high-=1
    elif cal > surface:
        high-=1
    else:
        low+=1

print(str(j) + " " + str(i) if found else "VALID")