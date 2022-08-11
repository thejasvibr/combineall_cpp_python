# Is it worth switching languages to get faster code?

I've been trying to implement the 'Combine All' algorithm described in Kreissig & Yang 2013 (ICASSP). 
The simplest way to explain the algorithm is that it mimics a table seating problem with N people. 
Person A can sit with everyone, but B can only sit with D and E, and F can sit only with G,H and I. The others (J..N) are pretty flexible. How many ways can we seat groups of people in compatible ways? 

'Combine All' solves this problem using a compatibility-conflict (CC) matrix. The CC matrix is a 
symmetric matrix where -1 indicates an incompatible pair, and +1 indicates a compatible pair. The
algorithm looks through all possible combinations of 'people' (or nodes as described in the paper), 
and generates compatible combinations. 

After implementing the algorithm in Python, it ran fairly fast for the 6 node problem - with a 
6x6 CC matrix (~93 microseconds/run). However, with increasing matrix sizes the run-time began
to get progressively worse. After doing some simple and rough linear regressions, I figured out 
for every 10X increase in number of nodes, there was a 10^5.5 increase in run-time. This means
moving from 6 -> 60 nodes means a predicted run-time of 294 seconds. Moving from 60 -> 600 then 
means an expected run-time of a few hours at least - not really feasible. 

## Optimising in Python - minimal luck and not fast enough...
I tried the usual things of changing container types (switching between using lists and sets), using 
Numpy and its associated array operations, changing two simultaneous loops (```for i in index1``` with ```for j in index2```) to one simultaneous loop (```for (i,j) in combination(index1, index2)```) - with minimal or worse change in performance. The Numba error messages turned out too cryptic for me to use as a new user. Putting my code into a .pyx file and running it through Cython did reduce run-times by half - but this too was too slow too be of use. 

The one change which did reduce run-time was when I eliminated the use of ```deepcopy``` of a return variable. This lead to a 15% decrease in run-time. In the larger picture though, this isn't much. Ideally I'd like to run a 300 x 300 matrix within a few minutes. The best achieved optimisation would have brought down 12 hours to about 10 hours if I'm being optimistic. 

Ultimately of course, after about a day and a half of optimising attempts - I began to feel the brunt 
of decreasing returns. 

## C++ : steep learning curve with a surprise
My programming experience has largely been limited to dynamically typed languages like Matlab, R and Python. I've *never* dealt with a statically typed language, and C++ definitely felt like a huge uphill struggle from the start. I still remain surprised that C++ allows you to 'assign' values to indices that don't exist in a container object (e.g. if you initiate an array of 10 items, you can happily assign and access the 11th item!). 

The one advantage I did have was my Python background. Many things about C++ seemed oddly familiar (the ```main``` keyword, the presence of sets, and lists). However, I knew C++ was a 'close to metal' language, the compiler optimised stuff - and that C++ code often ran two to three orders of magnitude faster than the equivalent Python code. 12 hours would become 43 seconds in case of a three orders of magnitude reduction! The excitement was high. The nice thing I had going for me was a working piece of Python code, which I could quickly refer and translate into C++. After about two days of intense C++ diving, I had a working version. Time to test it out! 

Now the anticipation was high, I ran my implementation and timed it. To my utter surprise, it worked - and it was also just 1.5-2 times faster than the Python implementation! My C++ implemenation took 50ish microseconds instead of nanoseconds!!! What happened to the multiple orders of magnitude I'd been dreaming of. My code was in dire need of optimisation - and I hadn't the faintest idea of where to start.

## Experienced colleague to the rescure: pass by reference vs pass by value, and other tricks
Now knowing where to begin, I of course reached out on our lab's Slack channel. Tristan Walter agreed to take a look, and made a couple of changes that changed the speed quite a bit. For starters, he noticed that most of the input parameters were not being changed anyway. 

My naive implementation's functions were written so. 
```
std::vector<std::vector<int> > some_function(std::vector<std::vector<int> > A, std::set B, std::set C){

	\\ stuff that happens in the function 
	}
```
Where's the problem you ask? Well, in Python, when you pass the list ```a```  into a function, you are actually passing the original object into the function. 
```

def insert_11(V):
    V.append(11)
    pass 

>>> k = [9]
>>> miaow(k)
>>> print(k)
the output you'll get
>>> [9, 11]
```
This style of argument passing is called pass by reference. In C++ however, the language doesn't pass by reference, but instead passes by *value*. Let's take a look at the same ```insert_11``` function in C++. 

```
#include <iostream>
#include <vector>

# the literal Python implementation 
void insert_11(std::vector<int> input_vector){
	input_vector.push_back(11);
}

# the C++ aware implementation - the '&' makes all the difference!!
std::vector<int> insert_11_byref(std::vector<int> &input_vector){
	input_vector.push_back(11);
	return input_vector;
}

	

int main(){
	std::vector<int> V{10};
	std::vector<int> U{10};
	std::cout << V[0] << "\n";
	insert_11(V);
	std::cout << V[1]<< "\n";
	
	std::cout <<  U[0]<< "\n";
	insert_11_byref(U);
	std::cout <<  U[1]<< "\n";
	return 0;
}

// After compiling and calling the executable you get the following outputs
// V[0] before function call
>>> 10
//  V[1] after function call. If Python-like then we expect V[1] to be 11
>>> 499 // A 'nonsense' value that just shows that 11 wasn't appended to the original vector

// U[0] before function call
>>> 10
// U[1] after function call. We expect value to be 11.
>>> 11 
```
We see that in C++, unless you specifically pass-by-reference, each function creates an extra copy of the input and performs actions on it. This is nice maybe, but creates a lot of work for the computer. My initial implementation was all pass-by-value, which meant *all* of my parameters were getting copied afresh each time. Tristan's alterations converted them to pass-by-reference, which meant, once the parameter was fed in, it wasn't copied - but the original object was passed around in the function. Less work for the computer.

Another aspect that Tristan stressed upon was the compiler optimisation - using the ```-O3``` flag and compiling in 'release mode', e.g. ```-std=c++20``` flag. 









