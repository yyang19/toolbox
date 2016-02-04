from itertools import chain, combinations

import numpy as np
from classes.container import Container
from zipfgen import ZipfGenerator

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
          p_sum += c_psvv

      result = p_sum/len(set(combinations(S_diff, self.B-1)))
      return result

N=10
B=6
X=3

zg=ZipfGenerator(N,0.6)
zipf_array=zg.randZipf()
print zipf_array

psvv_obj=psvv(N,B,zipf_array)
p=psvv_obj.get( zipf_array[0], X)
print p

