import sys
import math

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

n = int(input())
resdict = {}
for i in range(n):
    inputs = input().split()
    name = inputs[0]
    r = int(inputs[1])
    resdict[name] = r
circuit = input().split(' ')
print(circuit, file=sys.stderr, flush=True)
print(resdict, file=sys.stderr, flush=True)

# Write an answer using print
# To debug: print("Debug messages...", file=sys.stderr, flush=True)

def process(circuit):
    s = []
    i = 0
    while i < len(circuit):
        op = circuit[i]
        if op == ')':
            res = 0.0
            op2 = s.pop()
            while op2 != '(':
                if op2 in resdict:
                    res += float(resdict[op2])
                else:
                    res += float(op2)
                op2 = s.pop()
            s.append(res)
        elif op == ']':
            res = 0.0
            op2 = s.pop()
            while op2 != '[':
                if op2 in resdict:
                    res += 1.0 / float(resdict[op2])
                else:
                    res += 1.0 / float(op2)
                op2 = s.pop()
            res = 1.0 / res
            s.append(res)
        else:
            s.append(op)
        print(s, file=sys.stderr, flush=True)
        i += 1
    return str(round(s[0], 1))

print(process(circuit))
