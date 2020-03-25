#ifndef UNARY_FUNCTIONS_H
#define UNARY_FUNCTIONS_H


void test_unary_functions(void);


/*
 * Answer for task 2:
 *
 * Unary_Function is abstract because value_at is a pure virtual function.
 * Unary_Function virtual table contains a null pointer for value_at and Unary_Function::negative_value_at.
 *
 * Square is derived from Unary_Function and it overrides value_at, so its virtual table contains
 * Square::value_at and Unary_Function::negative_value_at.
 *
 * Linear is derived from Unary_Function and it overrides value_at, so its virtual table contains
 * Linear::value_at and Unary_Function::negative_value_at.
 */
struct unary_function;

struct unary_function* create_square(int lower_bound, int upper_bound);
struct unary_function* create_linear(int lower_bound, int upper_bound, double a, double b);

void destroy_unary_function(struct unary_function*);

double value_at(const struct unary_function* unary_function, double x);
double negative_value_at(const struct unary_function* unary_function, double x);
void tabulate(const struct unary_function* unary_function);
short same_function(
	const struct unary_function* f1,
	const struct unary_function* f2,
	double tolerance);


#endif
