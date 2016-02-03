from itertools import chain, combinations

import numpy as np
from cst import Cst

class Container(object):
	def __init__(self, B):
            self.cst = Cst(B)
            return;

        def __del__(self):
            return;
        
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

	def psvv(self,set_p, e, X):
            if e not in set_p:
                return 1;
            else:
                return 1- self.P_hit( e, X, set_p, self.cst )
                
#        def P_dev( e, t, s, c ):
#            if e not in s:
#                print "element ", e, "not in set", s
#                return 0
#            elif t==0:
#                return 0
#            elif t==len(s):
#                return 1
#            else:
#                s_i = set([e])
#                s_diff = s-s_i
#                s_len = len(s)
#                ps=P_sum(s)
#                sum=e/ps
#                for item in s_diff:
#                    sum += item*P_dev(e,t-1,s-set([item]),c)/ps
#                    
#                return sum

