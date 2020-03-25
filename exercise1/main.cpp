#include <iostream>


#include "memory_cost.hpp"
#include "manual_vf_table_lookup.hpp"

// runs with abort on MSVC v142 compiler
// #include "constructor_polymorphism_behaviour.hpp"


extern "C"
{
	#include "animals.h"
	#include "unary_functions.h"
}


int main()
{
	// Task 1
	// 
	// Code in: animals.hpp/.cpp
	test_animals();
	std::cout << std::endl << std::endl;

	/*
	 * Answer for task 2:
	 * 
	 * Unary_Function is abstract because value_at is a pure virtual function.
	 * Unary_Function virtual table contains a null pointer for value_at and Unary_Function::negative_value_at.
	 * 
	 * Square is derived from Unary_Function and it overrides value_at, so its virtual table contains
	 * Square::value_at and Unary_Function::negative_value_at.
	 *
	 * Linear is derived from Unary_Function and it overrides value_at, so its virtual table contains
	 * Linear::value_at and Unary_Function::negative_value_at.
	 *
	 *
	 * Code in: unary_functions.hpp/.cpp
	 */
	test_unary_functions();
	std::cout << std::endl << std::endl;

	/*
	 * Answer for task 3:
	 * 
	 * CoolClass contains a virtual table pointer,
	 * so in a 32-bit environment it is 4 bytes larger than the PlainOldClass.
	 * In a 64-bit environment it is 12 bytes larger
	 * which could be because the virtual table pointer is 8 bytes long
	 * and one of the classes is not properly aligned, so the compiler leaves out 4 bytes of extra space.
	 * Compiler used: MSVC v142
	 *
	 *
	 * Code in: memory_cost.hpp/.cpp
	 */
	print_virtual_tables_memory_cost();
	std::cout << std::endl << std::endl;

	/*
	 * Answers for task 4:
	 *
	 * 2.) cool constructor call line calls new and has additional operations for checking allocation success.
	 *	   plain_old_class constructor call line just calls its constructor.
	 *
	 * 3.) call ??plain_old_class@@QAE@XZ
	 *
	 * 4.) call ??cool_class@@QAE@XZ
	 *	   The constructor calls the base constructor and then it sets the vf_table.
	 *
	 * 5.) plain_old_class::set puts 42 on the stack and calls the function, whereas the base::set had to find
	 *	   the pointer to the function before doing what plain_old_class::set had done.
	 *
	 * 6.) The cool_class vf_table definition has functions get and set. It is initialized at the top of the
	 *     assembler file.
	 *
	 *
	 * Code in: time_cost.hpp/.cpp
	 */

	// Task
	print_manual_vf_table_lookup_result();
	std::cout << std::endl << std::endl;

	/*
	 * Answer for task 6:
	 *
	 * derived constructor:
	 * 1.) calls base constructor
	 * 2.) base constructor sets base vf table
	 * 3.) method() called using base vf table
	 * 4.) derived constructor sets derived vf table
	 * 5.) method() called using derived vf table
	 *
	 *
	 * Code in: constructor_polymorphism_behaviour.hpp/.cpp
	 */
	// runs with abort on MSVC v142 compiler
	// test_constructor_polymorphism_behaviour();
	// std::cout << std::endl;
	
	return EXIT_SUCCESS;
}
