#ifndef OOUP_LAB_EXERCISE2_MY_MAX_H
#define OOUP_LAB_EXERCISE2_MY_MAX_H

// ReSharper disable once CppUnusedIncludeDirective
#include <stdio.h>
#include <string.h>

typedef int (*compare)(const void*, const void*);

const void* my_max_c(const void* base, size_t n_items, size_t size, compare compare);

int gt_int_c(const void* first, const void* second);
int gt_char_c(const void* first, const void* second);
int gt_str_c(const void* first, const void* second);

void my_max_main_c();

#endif
