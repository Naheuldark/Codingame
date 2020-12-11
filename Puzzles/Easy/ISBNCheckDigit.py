import re


def isValidISBN10(isbn):
    if not re.fullmatch(r'^\d{9}(\d|X)$', isbn):
        return False

    checkSum = 0
    for i in range(len(isbn) - 1):
        checkSum += int(isbn[i]) * (10 - i)
    checkDigit = (11 - checkSum) % 11
    givenCheckDigit = 10 if isbn[-1] == 'X' else int(isbn[-1])

    return givenCheckDigit == checkDigit


def isValidISBN13(isbn):
    if not re.fullmatch(r'^\d{13}$', isbn):
        return False

    checkSum = 0
    for i in range(len(isbn) - 1):
        checkSum += int(isbn[i]) * (1 if i % 2 == 0 else 3)
    checkDigit = (10 - checkSum) % 10
    givenCheckDigit = 10 if isbn[-1] == 'X' else int(isbn[-1])

    return givenCheckDigit == checkDigit


def isValidISBN(isbn):
    if len(isbn) == 10:  # Check if isbn is ISBN-10.
        return isValidISBN10(isbn)
    elif len(isbn) == 13:  # Check if isbn is ISBN-13.
        return isValidISBN13(isbn)
    return False


n = int(input())
invalid = []

for i in range(n):
    isbn = input()
    if not isValidISBN(isbn):
        invalid.append(isbn)

print(str(len(invalid)) + ' invalid:')
print('\n'.join(invalid))