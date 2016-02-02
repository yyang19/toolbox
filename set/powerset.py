from itertools import chain, combinations

import ctypes
from ctypes import cdll

cstlib=cdll.LoadLibrary('/home/yyang/workspace/github/toolbox/lib/libpsvv.so')

class Cst(object):
	def __init__(self, n):
		self.obj = cstlib.psvv_init(n)

	def get(self,t,m,n):
	 	return cstlib.psvv_cst2(self.obj,t,m,n)

        def __del__(self):
                cstlib.psvv_destroy(self.obj)



def P_sum( s ):
    return sum(s)

def P_hit( i, t, s ):
    if i>= len(s):
        print "Incorrect element index ", i, "set length ", len(s)
        return -1
    else:
        s_i = set([0.2])
        s_diff = s-s_i
        print P_sum(s_diff)
        for z in chain.from_iterable( combinations(s_diff,r) for r in range(len(s_diff)+1)):
	    print len(z),z


n=4
c=Cst(n)

S_prob=set([0.1,0.2,0.3,0.4])

print P_hit(2,3,S_prob)

#result = c.get(t,m,n)
#print "c=cst(",t,",",m,",",n,")=",result
