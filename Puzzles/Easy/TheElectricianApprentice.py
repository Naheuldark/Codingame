import sys
import math


def process(circuit, switch):
    res = True
    serie = False
    i = 0
    while i < len(circuit):
        op = circuit[i]
        temp = True
        if op == '-':
            print("SERIE", file=sys.stderr)
            i += 1
            while i < len(circuit) and circuit[i] != '=':
                temp = temp and (switch[circuit[i]] if circuit[i] in switch else False)
                print(circuit[i], temp, file=sys.stderr)
                i += 1
            i -= 1
            print("END SERIE", i, circuit[i], file=sys.stderr)
        elif op == '=':
            print("PARALLEL", file=sys.stderr)
            i += 1
            while i < len(circuit) and circuit[i] != '-':
                temp = temp or (switch[circuit[i]] if circuit[i] in switch else False)
                print(circuit[i], temp, file=sys.stderr)
                i += 1
            i -= 1
            print("END PARALLEL", i, circuit[i], file=sys.stderr)

        res = res and temp
        i += 1
    return "ON" if res else "OFF"


circuit = {}
switch = {}
c = int(input())
for _ in range(c):
    cir = input().split(' ')
    circuit[cir[0]] = cir[1:]
a = int(input())
for i in range(a):
    s = input()
    if s in switch:
        switch[s] = not switch[s]
    else:
        switch[s] = True

print(circuit, file=sys.stderr)
print(switch, file=sys.stderr)

for c in circuit:
    print(c + " is " + process(circuit[c], switch))
