#include "pch.h"


#include "animal_factory.h"

#include "factory.h"



struct animal* create_animal(const char* const type, const char* const name)
{
	printf("Creating %s the %s...\n", name, type);
	
	return (struct animal*)create(type, name);
}
