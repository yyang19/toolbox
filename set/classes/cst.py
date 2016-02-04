from itertools import chain, combinations

import ctypes
from ctypes import cdll
import numpy as np

cstlib=cdll.LoadLibrary('/home/yyang/workspace/github/toolbox/lib/libpsvv_cst.so')

class Cst(object):
	def __init__(self, n):
		self.obj = cstlib.psvv_cst_init(n)

	def get(self,t,m,n):
	 	return cstlib.psvv_cst_get(self.obj,t,m,n)

        def __del__(self):
            cstlib.psvv_cst_destroy(self.obj)
 
