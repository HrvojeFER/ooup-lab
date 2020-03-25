#include "constructor_polymorphism_behaviour.hpp"


void test_constructor_polymorphism_behaviour()
{
	auto derived_ptr = new derived;

	derived_ptr->method();

	delete derived_ptr;  // NOLINT(clang-diagnostic-delete-non-abstract-non-virtual-dtor)
}
