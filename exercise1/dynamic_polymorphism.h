#ifndef DYNAMIC_POLYMORPHISM_H
#define DYNAMIC_POLYMORPHISM_H

#define MALLOC_FAILED 10
#define NULL_ARGUMENT 11


struct animal;

struct animal* create_dog(char* name);
struct animal* create_cat(char* name);

void print_greeting(struct animal*);
void print_menu(struct animal*);

void test_animal_on_stack(void);


#endif
