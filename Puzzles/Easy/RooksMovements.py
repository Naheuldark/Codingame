import math
import sys

BOARD_TRANS = {-1: '-', 1: 'x'}


def chess2ord(a):
    return ord(a[0]) - ord('a'), int(a[1]) - 1


def ord2chess(a):
    return chr(a[0] + ord('a')), str(a[1] + 1)


def check_horizontal(board, ipos, ix, y):
    moves = []
    for x in range(ix - 1, -1, -1):
        px, py = ord2chess((x, y))
        m = board[y][x]
        if m == 0:
            break
        else:
            moves.append('R{}{}{}{}'.format(ipos, BOARD_TRANS[m], px, py))
        if m == 1:
            break

    for x in range(ix + 1, 8):
        px, py = ord2chess((x, y))
        m = board[y][x]
        if m == 0:
            break
        else:
            moves.append('R{}{}{}{}'.format(ipos, BOARD_TRANS[m], px, py))
        if m == 1:
            break

    return moves


def check_vertical(board, ipos, x, iy):
    moves = []
    for y in range(iy - 1, -1, -1):
        px, py = ord2chess((x, y))
        m = board[y][x]
        if m == 0:
            break
        else:
            moves.append('R{}{}{}{}'.format(ipos, BOARD_TRANS[m], px, py))
        if m == 1:
            break

    for y in range(iy + 1, 8):
        px, py = ord2chess((x, y))
        m = board[y][x]
        if m == 0:
            break
        else:
            moves.append('R{}{}{}{}'.format(ipos, BOARD_TRANS[m], px, py))
        if m == 1:
            break

    return moves


rook = input()
rx, ry = chess2ord(rook)
num_pieces = int(input())

board = [[-1] * 8 for _ in range(8)]
for _ in range(num_pieces):
    color, position = input().split()
    px, py = chess2ord(position)
    board[py][px] = int(color)

moves = []
moves.extend(check_horizontal(board, rook, rx, ry))
moves.extend(check_vertical(board, rook, rx, ry))

for move in sorted(moves):
    print(move)
