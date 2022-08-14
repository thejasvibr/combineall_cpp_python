# -*- coding: utf-8 -*-
"""
Create a common input CC graph and compare across implementations
=================================================================
Created on Sun Aug 14 18:17:45 2022

@author: theja
"""

#%%
# Also create a 40x40 compatibility-conflict graph randomly and test 
# for performance.
import numpy as np
import pandas as pd

np.random.seed(300)
n_nodes = 200
big_A_values = np.random.choice([-1,1],int((n_nodes*n_nodes-1)/2))
big_A = np.zeros((n_nodes,n_nodes))
rows_lowertri, cols_lowertri = np.tril_indices(n_nodes)
counter = 0
for i,j in zip(rows_lowertri, cols_lowertri):
    if not i==j:
        big_A[i,j] = big_A_values[counter]
        counter += 1
big_A += big_A.T # make symmetrical
flat_A = big_A.flatten()
# try reconstructing to understand. 
np.savetxt('flatA.txt', flat_A, delimiter=',', fmt='%i')
np.savetxt('bigA.txt',big_A,  delimiter=',', fmt='%i')
np.savetxt('../combineall_python/bigA.txt',big_A, delimiter=',', fmt='%i')
np.savetxt('../combineall_cpp/flatA.txt', flat_A, delimiter=',', fmt='%i')
np.savetxt('../martin_kreisssig_cpp/flatA.txt', flat_A, delimiter=',', fmt='%i')
pd.DataFrame(big_A).to_csv('../comparing_implementations/big_A.csv')