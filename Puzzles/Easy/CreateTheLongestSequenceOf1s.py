import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

b = input()
mes = list(b)
maxi = 0

for i in range(len(b)):
    switch = False
    if mes[i] == '0':
        mes[i] = '1'
        switch = True
    lmaxi = 0
    cpt = 0
    for k in range(len(b)):
        if mes[k] == '1':
            cpt += 1
        else:
            if cpt > lmaxi:
                lmaxi = cpt
            cpt = 0
    if cpt > lmaxi:
        lmaxi = cpt

    if lmaxi > maxi:
        maxi = lmaxi
    if switch:
        mes[i] = '0'

print(maxi)