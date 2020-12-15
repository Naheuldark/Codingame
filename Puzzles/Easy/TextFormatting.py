import sys
import math
import re

text = input().lower().strip()

# Remove excessive spaces
text = re.sub(r'\s{2,}', ' ', text)

# Remove spaces before and after punctuations
text = re.sub(r'\s?[^\s\w\d]\s?', lambda match: match.group().strip(), text)

# Remove duplicated punctuations
text = re.sub(r'[^\s\w\d]+', lambda match: match.group().strip()[0], text)

# Convert to Pascal case
def toPascalCase(s):
    if not s:
        return ''
    chars = list(s)
    chars[0] = chars[0].upper()
    return ''.join(chars)
text = '.'.join(toPascalCase(s) for s in text.split('.'))

# Add spaces after punctuation
text = re.sub(r'[^\s\w\d]', lambda match: match.group() + ' ', text)

print(text.strip())