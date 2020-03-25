// ReSharper disable CppCStyleCast
#include "manual_vf_table_lookup.hpp"

#include <iostream>


typedef int(*first_type)();
typedef int(*second_type)(b*, int);

void print_manual_vf_table_lookup_result()
{
	b* b_ptr = new d;

	print_manual_vf_table_lookup_result(b_ptr);

	delete b_ptr;  // NOLINT(clang-diagnostic-delete-abstract-non-virtual-dtor)
}

void print_manual_vf_table_lookup_result(b* b_ptr)
{
	const auto vf_table_ptr = (void**)b_ptr;

	const auto first_ptr = (void**)*vf_table_ptr;
	const auto first = (first_type)*first_ptr;

	const auto second_ptr = (void**)(first_ptr + 1);
	const auto second = (second_type)*second_ptr;

	std::cout << "First result: " << first() << std::endl;

	const auto x = 3;
	printf("Second result (x = %d): %d\n", x, second(b_ptr, x));
}
