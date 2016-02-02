from itertools import chain, combinations

import ctypes
from ctypes import cdll
import numpy as np

cstlib=cdll.LoadLibrary('/home/yyang/workspace/github/toolbox/lib/libpsvv.so')

class Cst(object):
	def __init__(self, n):
		self.obj = cstlib.psvv_init(n)

	def get(self,t,m,n):
	 	return cstlib.psvv_cst2(self.obj,t,m,n)

        def __del__(self):
                cstlib.psvv_destroy(self.obj)

        def P_sum( self, s ):
            return sum(s)

        def P_hit( self, e, t, s, c ):
            if e not in s:
                print "element ", e, "not in set", s
                return 0
            elif t==0:
                return 0
            elif t==len(s):
                return 1
            else:
                s_i = set([e])
                s_diff = s-s_i
                sum=0
                s_len = len(s)
                for z in chain.from_iterable( combinations(s_diff,r) for r in range(len(s_diff)+1)):
                    sum += c.get( t, len(z), s_len ) * e / (self.P_sum(set(z)|s_i)) 
                
                return sum

        def P_dev( self, e, t, s, c ):
            if e not in s:
                print "element ", e, "not in set", s
                return 0
            elif t==0:
                return 0
            elif t==len(s):
                return 1
            else:
                s_i = set([e])
                s_diff = s-s_i
                s_len = len(s)
                sum=e/self.P_sum(s)
                for item in s_diff:
                    sum += item*self.P_dev(e,t-1,s-set([item]),c)/self.P_sum(s)
                    
                return sum

# Randomly generate a game set
N = 9
L_prob = np.random.random((N,))
L_prob /= sum(L_prob)
S_prob = set(L_prob)
c=Cst(N)

for e in S_prob:
    for X in range(1,len(S_prob)+1):
        p1 = c.P_hit( e, X, S_prob, c )
        p2 = c.P_dev( e, X, S_prob, c )
        print "e=",e, "X=",X, "p1=",p1, "p2=", p2
#print "c=cst(",t,",",m,",",n,")=",result
