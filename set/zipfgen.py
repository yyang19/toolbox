import random 
import numpy as np
import math

class ZipfGenerator(object): 
   def __init__(self, n, alpha): 
      self.n=n
      self.alpha=alpha
      return

   def randZipf(self): 
      tmp = [1. / (math.pow(float(i), self.alpha)) for i in range(1, self.n+1)]
      zeta = reduce(lambda sums, x: sums + [sums[-1] + x], tmp, [0])
      return tmp
