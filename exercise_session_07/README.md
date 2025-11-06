Exercise 1
--------------------
a) int*
b) int
c) int**
d)  10
e)  10
f)  40
g) 60
h)  15
i) p[-1] is same as *(p-1) and that is one element before the array. It is undefined behavior.
j) Same as previous, value of q[0] is *(p-1); undefined behavior.
k) *(q+10) is *(p+9) = p[9] = 100 
l) *(q+11)  is *(p+10) so it is also undefined behavior.

Exercise 2
---------------------
a) M is a pointer to pointer to int, so int**.

b) 
M has type int**. Value is the address of M[0].
*M has type int*. Value is M[0].
**M has type int. Value is M[0][0].

c)
M[1][3] and *(*(M+1)+3) are equal  to 8.
*(M[0]+1) is 1.

d) Each new int[5] allocates a separate block  and they need not be contiguous.
So *(M[0]+5) will  be an undefined behavior for that reason.

Files: exercise_2.cpp

Exercise 3
----------------------
a) Rows are y  and columns are x.
b) 14 × 6 = 84.

c) It depends on layout, either row-major or column-major. If  it is row-major, then (1,3) and (1,4) are adjacent.
With column-major, (1,3) and (2,3) are adjacent.

d)  Row-major is better when you iterate by rows, for example in C/C++.
Column-major is better when you iterate by columns, for  example Fortran.

e) 1 element.
f) 14 elements.
g) index = y * 14 + x,  0*14 + 10 = 10 is A[10].
h) 3*14 + 0 = 42 is A[42].
i) y = 7 is out of bounds so the element doesn’t exist.

Files: exercise_3.cpp


