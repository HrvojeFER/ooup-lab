#include <iostream>


#include "memory_cost.hpp"

extern "C"
{
	#include "animals.h"
	#include "unary_functions.h"
}


int main()
{
	test_animals();
	std::cout << std::endl << std::endl;

	/*
	 * Unary_Function is abstract because value_at is a pure virtual function.
	 * Unary_Function virtual table contains a null pointer for value_at and Unary_Function::negative_value_at.
	 * 
	 * Square is derived from Unary_Function and it overrides value_at, so its virtual table contains
	 * Square::value_at and Unary_Function::negative_value_at.
	 *
	 * Linear is derived from Unary_Function and it overrides value_at, so its virtual table contains
	 * Linear::value_at and Unary_Function::negative_value_at.
	 */
	test_unary_functions();
	std::cout << std::endl << std::endl;

	/*
	 * CoolClass contains a virtual table pointer,
	 * so in a 32-bit environment it is 4 bytes larger than the PlainOldClass.
	 * In a 64-bit environment it is 12 bytes larger
	 * which could be because the virtual table pointer is 8 bytes long
	 * and one of the classes is not properly aligned, so the compiler leaves out 4 bytes of extra space.
	 * Compiler used: MSVC v142
	 */
	print_virtual_tables_memory_cost();
	std::cout << std::endl;
	
	return EXIT_SUCCESS;
}
