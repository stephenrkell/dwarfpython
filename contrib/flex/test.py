# Basic input...
1 == 1
1.0 == 1.0
"1" == "1"
'1' == '1'
r"1" == r"1"
r'1' == r'1'
"1" + '1' == "11"
int.__add__(1, 0)
(0).__add__(1)
0 < 1 < 3 > 2
"a" < "c" > "b"
(9.0 < 11.0 < 10.0) == 0
import levenshtein
# This comment should not be necessary :S :S :S FIXME
levenshtein.distance("1", "b")
if 1:
    print 1
else:
    print 0

x = 5; a = ""
while x:
    x = 0

while x:
    x = 5

print "\n"

x == 0

def f(x):
    if x:
        return f(x-1)*x
    else:
        return 1

f(5) == 120

import os
a = os.open("/tmp/rar", 64)
os.close(a)

os.strerror(0) == "Success"
