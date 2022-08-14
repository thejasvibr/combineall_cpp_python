# -*- coding: utf-8 -*-
"""
Comparing the CombineAll solutions from C++ and Python
======================================================
Created on Thu Aug 11 15:49:27 2022

@author: theja
"""
import csv
import pandas as pd

cpp_file = '..\\combineall_cpp\\cpp_solutions.csv'
kreissig_file = '..\\martin_kreisssig_cpp\\kreissig_cpp_solutions.csv'
python_file = '..\\combineall_python\\python_solutions.csv'

def read_solution_csv(filepath):
    solution_sets = set()
    with open(filepath, 'r') as filesol:
        filecontents = csv.reader(filesol)
        for lines in filecontents:
            lines.pop(lines.index(''))
            solution_sets.add(tuple(sorted(lines)))
    return solution_sets

test_mat = pd.read_csv('big_A.csv').loc[:,'0':]
test_mat.columns = range(test_mat.shape[0])

cpp_solutions = read_solution_csv(cpp_file)
python_solutions = read_solution_csv(python_file)
kreissig_solutions = read_solution_csv(kreissig_file)

try:
    assert len(cpp_solutions) == len(python_solutions)
except AssertionError:
    print(f'There is a difference of {len(cpp_solutions) - len(python_solutions)} sets in length')
    raise AssertionError

assert cpp_solutions == python_solutions

assert cpp_solutions == kreissig_solutions
