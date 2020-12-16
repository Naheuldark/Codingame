import sys
import math

c = complex(input().replace('i', 'j'))
fn = 0
for i in range(1, int(input()) + 1):
    fn = fn*fn + c
    if abs(fn) > 2: break
print(i)
