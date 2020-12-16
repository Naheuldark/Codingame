import sys
import math


def compute_commands(cmds):
    commands = []
    for cmd in cmds:
        n, d = int(cmd[:-1]), cmd[-1]
        for _ in range(n):
            if d == 'L': commands.append(-1)
            elif d == 'R': commands.append(1)
            else: commands.append(0)
    return commands


n = int(input())
xthen_commands = input().split(';')
pos = int(xthen_commands[0])
commands = compute_commands(xthen_commands[1:])

cpos = 0
cur = pos-1
for _ in range(n):
    rthen_roadpattern = input().split(';')
    rep = int(rthen_roadpattern[0])

    for _ in range(rep):
        road = list(rthen_roadpattern[1])
        cur += commands[cpos]
        road[cur] = '#'
        cpos += 1
        print(''.join(road))
