import sys
import math


board = []
for i in range(3):
    board.append(list(input()))


win = -1


def check(line):
    global win
    seq = 0
    dots = 0
    pos = 0
    for i in range(3):
        if line[i] == 'O':
            seq += 1
        elif line[i] == '.':
            dots += 1
            pos = i

    if seq == 2 and dots == 1:
        win = pos
        return True

    return False


for i in range(3):
    if check(board[i]):  # Row
        board[i][win] = 'O'
        break
    if check(board[0][i] + board[1][i] + board[2][i]):  # Column
        board[win][i] = 'O'
        break

if check(board[0][0] + board[1][1] + board[2][2]):  # Down diag
    board[win][win] = 'O'
elif check(board[2][0] + board[1][1] + board[0][2]):  # Up diag
    board[2-win][win] = 'O'

if win == -1:
    print("false")
else:
    for line in board: 
        print(''.join(line))
