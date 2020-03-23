// ReSharper disable CppNonReclaimedResourceAcquisition
#include "unary_functions.h"


#include <stdio.h>
#include <stdlib.h>

#include "common.h"


// Test
void test_unary_functions()
{
	printf("x^2: \n");
	struct unary_function* f1 = create_square(-2, 2);
	tabulate(f1);
	printf("\n");

	const int a = 5;
	const int b = -2;
	printf("%d * x + %d: \n", a, b);
	struct unary_function* f2 = create_linear(-2, 2, a, b);
	tabulate(f2);
	printf("\n");

	printf("f1==f2: %s\n", same_function(f1, f2, 1e-6) ? "DA" : "NE");

	destroy_unary_function(f1);
	destroy_unary_function(f2);
}


// Overrides
typedef double(*virtual_unary_function_function)(void*, void*, void*);

double square_value_at(void* args, void* members, void* virtual_functions)
{
	if (args == NULL)
	{
		exit(NULL_ARGUMENT);
	}
	
	double* x = (double*)args;
	
	return *x * *x;
}

const int num_of_double_linear_members = 2;

const int a_index = 0;
const int b_index = 1;

void* get_linear_member(const int index, const void* members)
{
	if (members == NULL)
	{
		exit(NULL_ARGUMENT);
	}
	
	return (void*)((double*)members + index);
}


double linear_value_at(void* args, void* members, void* virtual_functions)
{
	if (args == NULL || members == NULL)
	{
		exit(NULL_ARGUMENT);
	}
	
	double* a = (double*)get_linear_member(a_index, members);
	double* b = (double*)get_linear_member(b_index, members);

	double* x = (double*)args;

	return *a * *x + *b;
}

const int num_of_virtual_unary_function_functions = 2;

const int value_at_index = 0;
const int negative_value_at_index = 1;

virtual_unary_function_function get_virtual_unary_function_function(
	const int index,
	virtual_unary_function_function* virtual_functions)
{
	if (virtual_functions == NULL)
	{
		exit(NULL_ARGUMENT);
	}
	
	return virtual_functions[index];
}


double unary_function_negative_value_at(void* args, void* members, void* virtual_functions)
{
	if (args == NULL || virtual_functions == NULL)
	{
		exit(NULL_ARGUMENT);
	}
	
	return -get_virtual_unary_function_function(
		value_at_index, virtual_functions)
		(args, members, virtual_functions);
}


// Virtual
/*
 * Unary_Function is abstract because value_at is a pure virtual function.
 * Unary_Function virtual table contains a null pointer for value_at and Unary_Function::negative_value_at.
 *
 * Square is derived from Unary_Function and it overrides value_at, so its virtual table contains
 * Square::value_at and Unary_Function::negative_value_at.
 *
 * Linear is derived from Unary_Function and it overrides value_at, so its virtual table contains
 * Linear::value_at and Unary_Function::negative_value_at.
 */
struct unary_function
{
	int lower_bound;
	int upper_bound;

	void* members; // on heap
	void* virtual_table; // on stack
};

double value_at(const struct unary_function* unary_function, double x)
{
	if (unary_function == NULL)
	{
		exit(NULL_ARGUMENT);
	}

	return get_virtual_unary_function_function(value_at_index, unary_function->virtual_table)
		(&x, unary_function->members, unary_function->virtual_table);
}

double negative_value_at(const struct unary_function* unary_function, double x)
{
	if (unary_function == NULL)
	{
		exit(NULL_ARGUMENT);
	}

	return get_virtual_unary_function_function(negative_value_at_index, unary_function->virtual_table)
		(&x, unary_function->members, unary_function->virtual_table);
}

void tabulate(const struct unary_function* unary_function)
{
	if (unary_function == NULL)
	{
		exit(NULL_ARGUMENT);
	}

	const virtual_unary_function_function value_at = 
		get_virtual_unary_function_function(value_at_index, unary_function->virtual_table);

	double x = unary_function->lower_bound;
	while (x <= unary_function->upper_bound)
	{
		printf("f(%d)=%lf\n", (int)x, 
			value_at(&x, unary_function->members, unary_function->virtual_table));
		x += 1;
	}
}

short same_function(
	const struct unary_function* f1,
	const struct unary_function* f2,
	const double tolerance)
{
	if (f1 == NULL || f2 == NULL)
	{
		exit(NULL_ARGUMENT);
	}
	
	if (!(f1->lower_bound == f2->lower_bound &&
		  f1->upper_bound == f2->upper_bound)) return 0;

	const virtual_unary_function_function f1_value_at =
		get_virtual_unary_function_function(value_at_index, f1->virtual_table);
	const virtual_unary_function_function f2_value_at =
		get_virtual_unary_function_function(value_at_index, f2->virtual_table);

	double x = f1->lower_bound;
	while(x <= f1->upper_bound)
	{
		double delta = f1_value_at(&x, f1->members, f1->virtual_table) - 
			f2_value_at(&x, f2->members, f2->virtual_table);

		if (delta < 0) delta = -delta;
		if (delta > tolerance) return 0;

		x += 1;
	}
	
	return  1;
}

virtual_unary_function_function linear_functions[] = { linear_value_at, unary_function_negative_value_at };
void construct_linear(
	struct unary_function* unary_function,
	const int upper_bound,
	const int lower_bound,
	const double a,
	const double b)
{
	if (unary_function == NULL)
	{
		exit(NULL_ARGUMENT);
	}

	unary_function->upper_bound = upper_bound;
	unary_function->lower_bound = lower_bound;

	unary_function->members = malloc(num_of_double_linear_members * sizeof(double));
	if (unary_function->members == NULL)
	{
		exit(MALLOC_FAILED);
	}
	
	((double*)unary_function->members)[a_index] = a;
	((double*)unary_function->members)[b_index] = b;

	unary_function->virtual_table = linear_functions;
}

virtual_unary_function_function square_functions[] = { square_value_at, unary_function_negative_value_at };
void construct_square(struct unary_function* unary_function, const int upper_bound, const int lower_bound)
{
	if (unary_function == NULL)
	{
		exit(NULL_ARGUMENT);
	}

	unary_function->upper_bound = upper_bound;
	unary_function->lower_bound = lower_bound;

	unary_function->members = NULL;

	unary_function->virtual_table = square_functions;
}

struct unary_function* create_linear(const int lower_bound, const int upper_bound, const double a, const double b)
{
	struct unary_function* unary_function = (struct unary_function*)malloc(sizeof(struct unary_function));
	if (unary_function == NULL)
	{
		exit(MALLOC_FAILED);
	}

	construct_linear(unary_function, upper_bound, lower_bound, a, b);

	return unary_function;
}

struct unary_function* create_square(const int lower_bound, const int upper_bound)
{
	struct unary_function* unary_function = (struct unary_function*)malloc(sizeof(struct unary_function));
	if (unary_function == NULL)
	{
		exit(MALLOC_FAILED);
	}

	construct_square(unary_function, upper_bound, lower_bound);

	return unary_function;
}

void destroy_unary_function(struct unary_function* unary_function)
{
	free(unary_function->members);
	free(unary_function);
}
