#include "pch.hpp"

#include "geometry.hpp"

extern "C"
{
#include "my_max_c.h"
}

#include "my_max_cpp.hpp"

int main()  // NOLINT(bugprone-exception-escape)
{
	// This implementation is brittle because
	// we have to change all methods which use shape to add any additional shapes
	// It violates the open-closed principle.
	ooup_lab::exercise2::geo_main();
	std::cout << std::endl;
	
	my_max_main_c();
	std::cout << std::endl;

	// This approach is very good in terms of respecting SOLID principles, however
	// the compiler creates a new function for each combination of types we are using
	// for the template function my_max_cpp
	// (in our case we are using it with six different type combinations and
	// that results in the creation of six different functions -
	// not to mention the functions that get generated for the STL to work) and
	// since we are using iterators and predicates and not straight up pointers,
	// we are adding overhead to calls for accessing elements of containers and
	// the predicate which results in higher execution times.
	// The higher execution time is negligible on a small scale, but
	// it might not be on a large scale where performance is critical.
	ooup_lab::exercise2::my_max_main_cpp();
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
