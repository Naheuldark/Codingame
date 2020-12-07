import sys
import math

def followPath(start_row, start_col, map_n, current, mem):
    #print(start_row, start_col,current, mem)
    row, col = start_row, start_col

    if (row, col) not in mem:
        mem.append((row, col))
    else:
        return -1

    if not 0 <= row < len(map_n):
        return -1
    if not 0 <= col < len(map_n[0]):
        return -1
    
    if map_n[row][col] == '.':
        return -1
    elif map_n[row][col] == '#':
        return -1
    elif map_n[row][col] == '^':
        return followPath(row-1, col, map_n, current+1, mem)
    elif map_n[row][col] == 'v':
        return followPath(row+1, col, map_n, current+1, mem)
    elif map_n[row][col] == '<':
        return followPath(row, col-1, map_n, current+1, mem)
    elif map_n[row][col] == '>':
        return followPath(row, col+1, map_n, current+1, mem)
    elif map_n[row][col] == 'T':
        return current + 1

w, h = [int(i) for i in input().split()]
start_row, start_col = [int(i) for i in input().split()]
n = int(input())

shortest = math.inf
shortest_idx = -1

for i in range(n):
    map_n = []
    for j in range(h):
        map_row = input()
        map_n.append(map_row)
        #print(map_row)

    count = followPath(start_row, start_col, map_n, 1, [])
    if 0 < count < shortest:
        shortest = count
        shortest_idx = i

print(shortest_idx if shortest_idx != -1 else "TRAP")
