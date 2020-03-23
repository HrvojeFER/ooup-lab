#ifndef DYNAMIC_POLYMORPHISM_H
#define DYNAMIC_POLYMORPHISM_H


void test_animals(void);

void test_three_animals(void);
void test_n_animals(int n);
void test_animal_on_stack(void);


struct animal;

struct animal* create_dog(char* name);
struct animal* create_cat(char* name);

void print_greeting(const struct animal* animal);
void print_menu(const struct animal* animal);


#endif
