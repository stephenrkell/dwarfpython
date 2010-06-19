from entrypoint import entrypoint,withfile
from collections import defaultdict
import re
import math

@entrypoint
@withfile(inp='r', htt='w', httg='w') # No, I don't know where those names come from either.
def main(inp='os.c', htt='/0/ii/report/diagrams/htt', httg='/0/ii/report/diagrams/httg'):

    funcs = {}

    for line in inp:
        m = re.match(r".* ([^ ]*)\(.*//(.*):(.*):(.*)", line)
        if m:
            funcs[m.group(1)] = float(m.group(3)), float(m.group(4))
            print m.group(1), " && ", m.group(2), " && ", m.group(3), " && ", m.group(4)

    aggrs = defaultdict(lambda: 0)

    for f,(m,t) in funcs.iteritems():
        aggrs[m/t] += 1

    histoplot = {}
    sum = 0
    total = 0
    for f in sorted(aggrs,reverse=True):
        sum += aggrs[f]
        total += aggrs[f] * (1-f)
        histoplot[f] = sum

    print "Mean improvement:", total/sum

    stdev = 0
    for f in aggrs:
        stdev += (aggrs[f] * ((1-f) - (total/sum))) ** 2

    print "Stdev:", math.sqrt(stdev/sum)

    for f in aggrs:
        print >>htt, (1-f)*100 , aggrs[f]

    for f in sorted(histoplot):
       print >>httg, (1-f)*100, histoplot[f]

    
