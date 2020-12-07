import sys
import math
import collections

wall, clear, goal = "#", ".", "M"
width, height = 10, 10

def bfs(grid, start):
    queue = collections.deque([[start]])
    seen = set([start])
    while queue:
        path = queue.popleft()
        x, y = path[-1]
        if grid[y][x] == goal:
            return path
        for x2, y2 in ((x+1,y), (x-1,y), (x,y+1), (x,y-1)):
            if 0 <= x2 < width and 0 <= y2 < height and grid[y2][x2] != wall and (x2, y2) not in seen:
                queue.append(path + [(x2, y2)])
                seen.add((x2, y2))

m = []
for i in range(10):
    line = input()
    m.append(line)
    print(line, file=sys.stderr, flush=True)
    if 'C' in line:
        start = (line.index('C'), i)

path = bfs(m, start)
print(str((len(path)-1)*10) + "km")