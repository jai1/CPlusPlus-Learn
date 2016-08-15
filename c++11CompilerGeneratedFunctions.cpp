
/*
 * All compiler functions are public and inline and generated only if needed.
 * 
 * Compiler provides these 4 functions by default:-
 * 1, Default Constructor (only if no other constructor is declared)
 * 2. Copy constructor [ A(const A& other) ] - (generated only if no 3, 4, 5, 6 declared by user)
 * 3. Copy Assignment Operator [ A& operator=(const A& other) ] - (generated only if no 2, 3, 5, 6 declared by user)
 * 4. Destructor
 * 
 * 5. move constructor (only if 2,3,4,6 are not declared by user)
 * 6. move assignment operator (only if 2,3,4,5 are not declared by user)
 * Note: in the above statements, delete is considered as user declaration
 * 
 * Compiler functions are not generated if:-
 * a. base class doesn't have a default constructor
 * b. base class destructor or constructor is provate
 * c. class has a reference member or a const member or if any of 
 *    it's members don't have a default constructor.
 * d. explicitly delete the operation ( C++11 )
 */