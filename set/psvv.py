from itertools import chain, combinations

import numpy as np
from classes.container import Container

# Randomly generate a game set
N = 6
#L_prob = np.random.random((N,))
L_prob = np.array([0.3305,0.035,0.04995,0.0831,0.1503,0.3509])
L_prob /= sum(L_prob)
S_prob = set(L_prob)
c=Container(N)

for e in S_prob:
    for X in range(1,len(S_prob)+1):
        p1 = c.psvv( S_prob, e, X )
        print "e=",e, "X=",X, "p1=",p1
