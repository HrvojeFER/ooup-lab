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

	ooup_lab::exercise2::my_max_main_cpp();
	std::cout << std::endl;

	return EXIT_SUCCESS;
}
