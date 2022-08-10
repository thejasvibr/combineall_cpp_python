# Combine All implementation in C++ and Python 

## What this routine does
```Comebine All``` is a routine described in Kreissig & Yang 2013 which finds
all possible combinations of compatible nodes in a 'compatibility-conflict' matrix/graph. 
Essentially, if there are 5 nodes ```nodes=[0,1,2,3,4]```, and for example node 1 is 
incompatible with all others and 2 is compatible with 3, then the possible outputs
are ``` [0,2,4]``` and ```[0,3,4]```. 

The compatibility-conflict graph holds the pair-wise in/compatibility with entries of
+/- 1. +1 indicates compatibility and -1 indicated incompatibility. 

## Help with optimisation
```Combine All``` takes ~1 second for 40x40 matrices already. The final use-case is 
to have matrices of ~200-300 rows and columns. Previous experiments showed that 
200-300 rows could take ~12 hours to run - which is infeasible. 

As of now both the Cpp and Python implementations run at around the same speed. 
The Cpp can be sped up about 1.5-2 X the Python one using compiler flags - but this
doesn't really change timing a lot for larger matrices. 

## Questions
* Can you think of data structures and operations that could be optimised?
* ```Combine All``` is a recursive function, which I've read tend to do poorly performance-wise. 
	Is it worth the effort of re-factoring the recursive function into an iterative one? 
	
	
## Dependencies

* Python : only external dependency is ```nump```
* C++ : No external dependency. 

All code has been run on a Win 10. Python 3.8 installation. C++ code compiled with 
MinGW.