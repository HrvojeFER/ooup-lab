// ReSharper disable CppNonReclaimedResourceAcquisition
#include "animals.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"


// Tests
void test_animals()
{
	const unsigned int seed = time(0);
	srand(seed);

	printf("three animals:\n");
	test_three_animals();
	printf("\n");

	printf("animals on stack:\n");
	test_animal_on_stack();
	printf("\n");

	const int n = 5;
	printf("n=%d animals:\n", n);
	test_n_animals(5);
}

void test_three_animals(void)
{
	struct animal* hamlet = create_dog("Hamlet");
	struct animal* ophelia = create_cat("Ophelia");
	struct animal* polonius = create_dog("Polonius");

	print_greeting(hamlet);
	print_greeting(ophelia);
	print_greeting(polonius);

	print_menu(hamlet);
	print_menu(ophelia);
	print_menu(polonius);

	free(hamlet);
	free(ophelia);
	free(polonius);
}

void test_n_animals(const int n)
{
	const int size_of_name_container = 20;
	char* name = (char*)calloc(size_of_name_container, sizeof(char));


	for (int i = 0; i < n; ++i)
	{
		if (name != NULL)
		{
			struct animal* animal;

			sprintf_s(name, size_of_name_container, "animal %d", i);
			switch (rand() % 2)
			{
			case 0:
				animal = create_dog(name);
				break;

			default:
				animal = create_cat(name);
				break;
			}

			if (animal != NULL)
			{
				print_greeting(animal);
				print_menu(animal);

				free(animal);
			}
			else
			{
				exit(MALLOC_FAILED);
			}
		}
		else
		{
			exit(MALLOC_FAILED);
		}
	}

	free(name);
}


// Overrides
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


// Virtual
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


// Stack test
void test_animal_on_stack(void)
{
	struct animal richard_the_stack_guardian =
	{
		"Richard",
		dog_functions
	};

	print_greeting(&richard_the_stack_guardian);
	print_menu(&richard_the_stack_guardian);
}
