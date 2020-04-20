#include "my_max_c.h"

const void* my_max_c(const void* base, const size_t n_items, const size_t size, const compare compare)
{
	char* my_base = (char*)base;
	size_t max_index = 0;
	
	for (size_t i = 1 ; i < n_items ; ++i)
	{
		if (compare(my_base + i * size, my_base + max_index * size))
		{
			max_index = i;
		}
	}

	return my_base + max_index * size;
}

int gt_int_c(const void* first, const void* second)
{
	return *(int*)first > *(int*)second ? 1 : 0;
}

int gt_char_c(const void* first, const void* second)
{
	return (*(char*)first > *(char*)second) ? 1 : 0;
}

int gt_str_c(const void* first, const void* second)
{
	return strcmp(*(char**)first, *(char**)second) > 0 ? 1 : 0;
}


void my_max_main_c()
{
	int arr_int[] = { 1, 3, 5, 7, 4, 6, 9, 2, 0 };
	// ReSharper disable StringLiteralTypo
	char arr_char[] = "Suncana strana ulice";
	const char* arr_str[] = 
	{
	   "gle", "malu", "vocku", "poslije", "kise",
	   "puna", "je", "kapi", "pa", "ih", "njise"
	};
	// ReSharper enable StringLiteralTypo

	printf("max int: %d \n", 
		*(int*)my_max_c(arr_int, sizeof arr_int / sizeof(int) , sizeof(int), gt_int_c));

	printf("max char: %c \n", 
		*(char*)my_max_c(arr_char, sizeof arr_char / sizeof(char), sizeof(char), gt_char_c));

	printf("max char array: %s \n", 
		*(char**)my_max_c(arr_str, sizeof arr_str / sizeof(char*), sizeof(char*), gt_str_c));
}
