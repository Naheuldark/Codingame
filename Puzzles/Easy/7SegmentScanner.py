import sys
import math

line_1 = list(input())
line_2 = list(input())
line_3 = list(input())

number = []
for i in range(0, len(line_1), 3):
    if line_1[i:i+3] == [' ', '_', ' ']:
        if line_2[i:i+3] == ['|', ' ', '|']:  # 0
            number.append('0')
        elif line_2[i:i+3] == [' ', '_', '|']:  # 2 3
            if line_3[i:i+3] == ['|', '_', ' ']:
                number.append('2')
            else:
                number.append('3')
        elif line_2[i:i+3] == ['|', '_', ' ']:  # 5 6
            if line_3[i:i+3] == [' ', '_', '|']:
                number.append('5')
            else:
                number.append('6')
        elif line_2[i:i+3] == [' ', ' ', '|']:  # 7
            number.append('7')
        elif line_2[i:i+3] == ['|', '_', '|']:  # 8 9
            if line_3[i:i+3] == ['|', '_', '|']:
                number.append('8')
            else:
                number.append('9')
    else:
        if line_2[i:i+3] == [' ', ' ', '|']:
            number.append('1')
        else:
            number.append('4')

print(''.join(number))
