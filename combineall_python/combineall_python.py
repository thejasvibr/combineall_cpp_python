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
    Nvl = []
    if len(l)>0:
        for v in V_t:
            for u in l:
                if Acc[v,u]==1:
                    Nvl.append(v)
                elif Acc[v,u]==-1:
                    if v in Nvl:
                        Nvl.pop(Nvl.index(v))
        return set(Nvl)
    else:
        return V_t

def get_Nvl_fast(Acc, V_t, l):
    '''version based on - Reinderien: 
        https://codereview.stackexchange.com/a/278680/263672
    '''
    if len(l) < 1:
        return V_t

    Nvl = set()
    for v in V_t:
        for u in l:
            a = Acc[v, u]
            if a == 1:
                Nvl.add(v)
            elif a == -1:
                Nvl.discard(v)
    return Nvl


def get_NOT_Nvl(Acc:np.array, V:set, l:set):
    N_not_vl = []
    if len(l)>0:
        for v in V:
            for u in l:
                if Acc[v,u]==-1:
                    N_not_vl.append(v)
                elif Acc[v,u]==1:
                    if v in N_not_vl:
                        N_not_vl.pop(N_not_vl.index(v))
    else:
        N_not_vl = []
    return set(N_not_vl)

def flatten_combine_all(entry):
    if isinstance(entry, list):
        if len(entry)==1:
            return flatten_combine_all(entry[0])
        else:
            return list(map(flatten_combine_all, entry))
    elif isinstance(entry, set):
        return entry
    else:
        raise ValueError(f'{entry} can only be set or list')

def format_combineall(output):
    semiflat = flatten_combine_all(output)
    only_sets = []
    for each in semiflat:
        if isinstance(each, list):
            for every in each:
                if isinstance(every, set):
                    only_sets.append(every)
        elif isinstance(each, set):
            only_sets.append(each)
    return only_sets

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
    N_vl = get_Nvl_fast(Acc, V, l)
    N_not_vl = get_NOT_Nvl(Acc, V, l)
    #print(f'l:{l}, X:{X}, V:{V}, N_vl:{N_vl}, N_notvl:{N_not_vl}')
    solutions_l = []
    if len(N_vl) == 0:
        solutions_l.append(l)
    else:
        # remove conflicting neighbour
        V = V.difference(N_not_vl)
        # unvisited compatible neighbours
        Nvl_wo_X = N_vl.difference(X)
        for n in Nvl_wo_X:
            Vx = V.difference(set([n]))
            lx = l.union(set([n]))
            solution = combine_all(Acc, Vx, lx, X)
            if solution:
                for each in solution:
                    solutions_l.append(each)
            X = X.union(set([n]))
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
    print(f'Duration per run: {(stop-start)/1e9/10**2} s')
    
    #%%
    # Also create a 40x40 compatibility-conflict graph randomly and test 
    # for performance.
    np.random.seed(78464)
    n_nodes = 40
    big_A_values = np.random.choice([-1,1],int((n_nodes*n_nodes-1)/2))
    big_A = np.zeros((n_nodes,n_nodes))
    rows_lowertri, cols_lowertri = np.tril_indices(n_nodes)
    counter = 0
    for i,j in zip(rows_lowertri, cols_lowertri):
        if not i==j:
            big_A[i,j] = big_A_values[counter]
            counter += 1
    big_A += big_A.T # make symmetrical
    # Now run and test for performance 
    start = time.perf_counter_ns()
    [combine_all(big_A, set(range(n_nodes)), set([]), set([])) for ii in range(2)]
    stop = time.perf_counter_ns()
    print(f'Duration per run: {(stop-start)/1e9/2} s')
    
