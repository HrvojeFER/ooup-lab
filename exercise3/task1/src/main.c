#include "pch.h"

#include "animal_test.h"


const int animal_count = 2;
const char* animal_types[] = { "parrot", "tiger" };
const char* animal_names[] = { "George", "Peter" };

int main()  // NOLINT(bugprone-exception-escape)
{
	test_animals(animal_count, animal_types, animal_names);
}
