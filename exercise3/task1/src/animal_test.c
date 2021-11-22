#include "pch.h"


#include "animal_test.h"

#include "animal_factory.h"



void test_animals(
    const int animal_count, 
    const char** const animal_types,
    const char** const animal_names,
    const int* const create_on_stack)
{
    for (int i = 0 ; i < animal_count ; ++i)
    {
        printf("\n\n");

    	struct animal* animal;

        if (create_on_stack[i])
        {
            printf("Creating %s the %s on the stack...\n", 
                animal_names[i], animal_types[i]);

        	animal = (struct animal*)_malloca(get_animal_type_size(animal_types[i]));
        	if (!animal)
        	{
                exit(ANIMAL_ALLOCATION_FAILED);
        	}

            construct_animal(animal_types[i], animal, animal_names[i]);
        }
        else 
            animal = create_animal(animal_types[i], animal_names[i]);

    	if (!animal)
        {
            printf("Creation of animal type %s failed.\n", animal_types[i]);
            continue;
        }

    	
        printf("\n");

    	printf("This is %s.\n", animal_name(animal));
        animal_print_greeting(animal);
        printf("He likes to eat:\n");
        animal_print_menu(animal);

    	
    	if (!create_on_stack[i]) free(animal);
    }

    printf("\n\n");
}
