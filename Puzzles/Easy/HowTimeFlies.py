import sys
import math
from dateutil.relativedelta import relativedelta
import datetime

# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

begin = datetime.datetime.strptime(input(), '%d.%m.%Y')
end = datetime.datetime.strptime(input(), '%d.%m.%Y')

diff = relativedelta(end, begin)

if diff.years != 0:
    print(str(diff.years) + " year" + ("s" if diff.years > 1 else "") + ", ", end="")

if diff.months != 0:
    print(str(diff.months) + " month" + ("s" if diff.months > 1 else "") + ", ", end="")

print("total " + str((end - begin).days) + " days")