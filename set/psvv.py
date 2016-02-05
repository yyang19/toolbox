from itertools import chain, combinations

import numpy as np
from classes.container import Container
from zipfgen import ZipfGenerator
import cProfile

class psvv(object):
   def __init__(self,N,B,arr_p):
      self.c=Container(B)
      self.N=N
      self.B=B
      self.arr_p=arr_p
      return

   def __del__(self):
      return

   def get(self, e, X):
      #arr_p = np.random.random((N,))
      #arr_p /= sum(L_prob)
      S_prob = set(self.arr_p)
      S_e = set([e])
      S_diff = S_prob-S_e
      p_sum = 0
      for L_X in set(combinations(S_diff, self.B-1)):
          S_X=set(L_X)
          c_psvv = self.c.psvv( S_X|S_e, e, X )
          p_sum += ( c_psvv * sum(S_X)/(1-e) )

      result = p_sum/len(set(combinations(S_diff, self.B-1)))
      return result

N=14
B=8
X=4

zg=ZipfGenerator(N,0.6)
za=zg.randZipf()
za = [float(i)/sum(za) for i in za]
print za, sum(za)

psvv_obj=psvv(N,B,za)
#p=psvv_obj.get( za[0], X)
cProfile.run('psvv_obj.get( za[0], X)')
#print p

