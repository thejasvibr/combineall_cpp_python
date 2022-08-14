# -*- coding: utf-8 -*-
"""
CombineAll implementation - Python version
============================================

References
----------
* Kreissig & Yang 2013, Fast & reliable ...., ICASSP 
Created on Tue Jun 14 11:59:03 2022

@author: thejasvi
"""
import numpy as np 
from copy import deepcopy
from itertools import chain, product
import time

#%%
def get_Nvl(Acc, V_t, l):
    '''
    Parameters
    ----------
    Acc : (N_cfl,N_cfl) np.array
        The compatibility-conflict graph.
    V_t : set
        V_tilda. The currently considered vertices (a sub-set of V, all vertices)
    l : set
        The solution consisting of the currently compatible vertices.        

    Returns
    -------
    Nvl : set
        Solution of vertices that are compatible to at least one other vertex
        and not in conflict with any of the other vertices.
    '''
    Nvl = set([])
    if len(l)>0:
        for v in V_t:
            for u in l:
                if Acc[v,u]==1:
                    Nvl.add(v)
                elif Acc[v,u]==-1:
                    try:
                        Nvl.discard(v)
                    except:
                        pass
        return Nvl
    else:
        return V_t

def get_NOT_Nvl(Acc:np.array, V:set, l:set):
    N_not_vl = set([])
    if len(l)>0:
        for v in V:
            for u in l:
                if Acc[v,u]==-1:
                    N_not_vl.add(v)
                elif Acc[v,u]==1:
                        try:
                            N_not_vl.discard(v)
                        except:
                            pass
    return N_not_vl

def get_Nvl_and_Nnotvl(Acc:np.array, V:set, l:set):
    '''Function which performs the Nvl and N_not_vl calculation
    together.
    '''
    Nvl, Nnotvl = set([]), set([])
    if len(l)<1:
        return V, Nnotvl
    else:
        for v in V:
            compatible = False
            conflict = False
            for u in l:
                if Acc[v,u]==-1:
                    conflict = True
                elif Acc[v,u]==1:
                    compatible = True
            if conflict:
                Nnotvl.add(v)
            elif compatible:
                Nvl.add(v)
                    
    return Nvl, Nnotvl
            

def combine_all(Acc, V, l, X):
    '''
    

    Parameters
    ----------
    Acc : (N_cfl, N_cfl) np.array
        DESCRIPTION.
    V : set
    l : set
    X : set

    Returns
    -------
    None.

    '''
    # determine N_v(l) and !N_v(l)
    # !N_v(l) are the vertices incompatible with the current solution
    #N_vl = get_Nvl(Acc, V, l)
    #N_not_vl = get_NOT_Nvl(Acc, V, l)
    N_vl, N_not_vl = get_Nvl_and_Nnotvl(Acc, V, l)
    # print(f'l:{l}, X:{X}, V:{V}, N_vl:{N_vl}, N_notvl:{N_not_vl}, X:{X}')
    solutions_l = []
    if len(N_vl) == 0:
        solutions_l.append(l)
        #print(l)
    else:
        # remove conflicting neighbour
        V = V.difference(N_not_vl)
        # unvisited compatible neighbours
        Nvl_wo_X = N_vl.difference(X)
        #print(f'   Vdiff: {V}, NvlwoX: {Nvl_wo_X}')
        for n in Nvl_wo_X:
            #print(f'n: {n}')
            Vx = V.difference(set([n]))
            lx = l.union(set([n]))
            solution = combine_all(Acc, Vx, lx, X)
            if solution:
                for each in solution:
                    solutions_l.append(each)
            X = X.union(set([n]))
            #print(f'X:{X}')
    return solutions_l
#%%
if __name__ == '__main__':
    # the known case - expected output is 
    
    A = np.array([[ 0, 1, 0, 0,-1,-1],
                  [ 1, 0, 1, 1, 0, 1],
                  [ 0, 1, 0,-1, 1, 0],
                  [ 0, 1,-1, 0,-1, 0],
                  [-1, 0, 1,-1, 0, 1],
                  [-1, 1, 0, 0, 1, 0]])
    
    qq = combine_all(A, set(range(6)), set([]), set([]))
    expected_output = [{0,1,2}, {0,1,3}, {1,2,4,5}, {1,3,5}]
    # Check the known case from the KY2013 paper
    assert(qq==expected_output)
    
    #%%
    start = time.perf_counter_ns()
    [ combine_all(A, set(range(6)), set([]), set([])) for i in range(10**2)]
    stop = time.perf_counter_ns()
    print(f'Duration per run 6x6 : {(stop-start)/1e9/10**2} s')
    #%%
    # Load the bigA matrix
    big_CC = np.loadtxt('bigA.txt', delimiter=',')
    #%%
    # Now run and test for performance 
    start = time.perf_counter_ns()
    print('\n    Starting big A run....\n')
    n_nodes = big_CC.shape[0]
    for ii in range(1):
        qqr = combine_all(big_CC, set(range(n_nodes)), set([]), set([]))
    stop = time.perf_counter_ns()   
    print(f'Duration per run {n_nodes}x{n_nodes} : {(stop-start)/1e9/1} s')
    print(len(qqr))
    
    # Write solution to csv file
    with open('python_solutions.csv' , 'w') as csvfile:
        for soln in qqr:
            for each in soln:
                csvfile.write(str(each)+',')
            csvfile.write('\n')

            
    
