

/* 
STL containers and algorithm functions use either of the following to perform search:
a. (!(x<y) && !(y<x)) -- equivalence
b. x==y -- equality

Mathematically they are both the same BUT programatically the following are called:-
a. bool operator<(const Class& obj) -- equivalence 
b. bool operator==(const Class& obj) -- equality

Equivalence is generally used by:-
a. Associative containers - sorted data (sets)
b. Algorithms on sorted data
- binary_search
- includes
- lower_bound
- upper_bound

Equality is generally used by:-
a. Un sorted STL
b. Algorithms that work on sorted and unsorted STLs
- search
- find
- find_first_of
- find_end
- adjacent_search
*/


