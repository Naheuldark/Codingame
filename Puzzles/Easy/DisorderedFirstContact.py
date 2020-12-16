import sys
import math


def define_list_num_char(message):
    sum_j, j = 1, 1
    list_j = []
    while sum_j <= len(message):
        list_j.append(j)
        j += 1
        sum_j += j
    list_j.append(len(message) - sum(list_j))
    return list_j


def encode(message, n):
    list_j = define_list_num_char(message)

    for i in range(n):
        encoded = ''
        begin = False
        for j in list_j:
            encoded = message[:j] + encoded if begin else encoded + message[:j]
            message = message[j:]
            begin = not begin
        message = encoded
    return message


def decode(message, n):
    list_j = define_list_num_char(message)

    for i in range(n):
        decoded = ''
        begin = len(list_j) % 2 == 0
        for j in reversed(list_j):
            if begin:
                decoded = message[:j] + decoded
                message = message[j:]
            else:
                decoded = message[len(message)-j:] + decoded
                message = message[:len(message)-j]
            begin = not begin
        message = decoded
    return message


n = int(input())
message = input()

print(decode(message, n) if n > 0 else encode(message, abs(n)))
