#include "pch.h"


#include "animal_factory.h"

#include "factory.h"



size_t get_animal_type_size(const char* const type)
{
	return get_required_size(type);
}

void construct_animal(const char* const type, struct animal* animal, const char* const name)
{
	const int error_code = construct(type, animal, name);
	if (error_code)
	{
		exit(error_code);
	}
}


struct animal* create_animal(const char* const type, const char* const name)
{
	printf("Creating %s the %s...\n", name, type);

	struct animal* result = (struct animal*)create(type, name);
	if(!result)
	{
		exit(ANIMAL_CAST_FAILED);
	}
	
	return result;
}
