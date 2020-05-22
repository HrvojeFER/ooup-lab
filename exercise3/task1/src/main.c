#include "pch.h"

#include "animal_test.h"


const int animal_count = 4;
const char* animal_types[] = { "parrot", "tiger", "parrot", "tiger" };
const char* animal_names[] = { "George", "Peter", "Rhonda", "Stewart" };
const int create_on_heap[] = { 1, 0, 0, 1 };

int main()  // NOLINT(bugprone-exception-escape)
{
	test_animals(animal_count, animal_types, animal_names, create_on_heap);
}
