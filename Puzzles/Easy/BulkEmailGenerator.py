import sys
import math
import re

emails = []

n = int(input())
for i in range(n):
    emails.append(input())

emailTemplate = '\n'.join(emails)
choicesCpt = -1


def choiceReplace(match):
    global choicesCpt
    choicesCpt += 1
    choices = match.group()[1:-1].split('|')
    return choices[choicesCpt % len(choices)]


email = re.sub('\\([^)]*\\)', choiceReplace, emailTemplate)
print(email)
