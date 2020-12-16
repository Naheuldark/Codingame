import sys
import math

score = int(input())
for tries in range(score // 5 + 1):
    if tries * 5 == score:
        print('{} 0 0'.format(tries))
        continue

    for trans in range(tries + 1):
        if tries * 5 + trans * 2 > score: break
        if (score - tries * 5 - trans * 2) % 3 == 0:
            penalty = (score - tries * 5 - trans * 2) // 3
            print('{} {} {}'.format(tries, trans, penalty))
