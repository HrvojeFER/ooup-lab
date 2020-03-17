// ReSharper disable CppNonReclaimedResourceAcquisition
#include "dynamic_polymorphism.h"


#include <stdio.h>
#include <stdlib.h>


const char* dog_greet(void)
{
	return "woof!";
}
const char* dog_menu(void)
{
	return "beef jerky";
}

const char* cat_greet(void)
{
	return "meow!";
}
const char* cat_menu(void)
{
	return "canned tuna";
}


typedef const char* (*animal_function)();

const int num_of_animal_functions = 2;

const int greet_function_index = 0;
const int menu_function_index = 1;

animal_function dog_functions[] = { dog_greet, dog_menu };
animal_function cat_functions[] = { cat_greet, cat_menu };

struct animal
{
	char* name;
	animal_function* functions;
};

void print_greeting(const struct animal* animal)
{
	if (animal != NULL)
	{
		printf("%s\n", animal->functions[greet_function_index]());
	}
	else
	{
		exit(NULL_ARGUMENT);
	}
}

void print_menu(const struct animal* animal)
{
	if (animal != NULL)
	{
		printf("%s\n", animal->functions[menu_function_index]());
	}
	else
	{
		exit(NULL_ARGUMENT);
	}
}

void construct_dog(struct animal* dog, char* name)
{
	if (dog != NULL && name != NULL)
	{
		dog->name = name;
		dog->functions = dog_functions;
	}
	else
	{
		exit(NULL_ARGUMENT);
	}
}

void construct_cat(struct animal* cat, char* name)
{
	if (cat != NULL && name != NULL)
	{
		cat->name = name;
		cat->functions = cat_functions;
	}
	else
	{
		exit(NULL_ARGUMENT);
	}
}

struct animal* create_dog(char* name)
{
	struct animal* dog = (struct animal*)malloc(sizeof(struct animal));
	if (dog != NULL)
	{
		construct_dog(dog, name);
		return dog;
	}

	exit(MALLOC_FAILED);
}

struct animal* create_cat(char* name)
{
	struct animal* cat = (struct animal*)malloc(sizeof(struct animal));
	if (cat != NULL)
	{
		construct_cat(cat, name);
		return cat;
	}
	
	exit(MALLOC_FAILED);
}


void test_animal_on_stack(void)
{
	struct animal richard_the_dog =
	{
		"Richard",
		dog_functions
	};

	print_greeting(&richard_the_dog);
	print_menu(&richard_the_dog);
}
