#include <time.h>
#include <stdio.h>
#include <stdlib.h>


#include "dynamic_polymorphism.h"


void test_animals(void)
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

void test_n_animals(const int* n)
{
	if (n != NULL)
	{
		const int size_of_name_container = 20;
		char* name = (char*)calloc(size_of_name_container, sizeof(char));


		for (int i = 0; i < *n; ++i)
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
	else
	{
		exit(NULL_ARGUMENT);
	}
}


int main()
{
	const unsigned int seed = time(0);
	srand(seed);
	
	test_animals();
	printf("\n");
	
	test_animal_on_stack();
	printf("\n");
	
	const int n = 5;
	test_n_animals(&n);
	
	return EXIT_SUCCESS;
}
