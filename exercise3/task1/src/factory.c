#include "pch.h"

#include "factory.h"



const char* const current_folder_relative_path = "./";
const size_t current_folder_relative_path_length = 2;
const char* const dll_extension = ".dll";
const size_t dll_extension_length = 4;
// current_folder_relative_path_length + dll_extension_length
const size_t library_name_added_chars_length = 6;

int fill_with_library_file_path(
	char* const to_fill, 
	const int to_fill_size,
	const char* const library_name)
{
	// Tells strcat_s to concatenate from the beginning of the string.
	to_fill[0] = '\0';

	int error_code = strcat_s(to_fill, to_fill_size, current_folder_relative_path);
	if (error_code) return error_code;
	error_code = strcat_s(to_fill, to_fill_size, library_name);
	if (error_code) return error_code;
	error_code = strcat_s(to_fill, to_fill_size, dll_extension);

	return error_code;
}


const char* const factory_function_name_prefix = "create_";
const size_t factory_function_name_prefix_length = 7;

int fill_with_create_function_name(
	char* const to_fill, 
	const int to_fill_size, 
	const char* const library_name)
{
	// Tells strcat_s to concatenate from the beginning of the string.
	to_fill[0] = '\0';

	int error_code = strcat_s(to_fill, to_fill_size, factory_function_name_prefix);
	if (error_code) return error_code;
	error_code = strcat_s(to_fill, to_fill_size, library_name);

	return error_code;
}


const char* const get_size_function_name_prefix = "get_";
const size_t get_size_function_name_prefix_length = 4;
const char* const get_size_function_name_suffix = "_size";
const size_t get_size_function_name_suffix_length = 5;
// get_size_function_name_prefix_length + get_size_function_name_suffix_length
const size_t get_size_function_added_chars_length = 9;

int fill_with_get_size_function_name(
	char* const to_fill,
	const int to_fill_size,
	const char* const library_name)
{
	// Tells strcat_s to concatenate from the beginning of the string.
	to_fill[0] = '\0';
	
	int error_code = strcat_s(to_fill, to_fill_size, get_size_function_name_prefix);
	if (error_code) return error_code;
	error_code = strcat_s(to_fill, to_fill_size, library_name);
	if (error_code) return error_code;
	error_code = strcat_s(to_fill, to_fill_size, get_size_function_name_suffix);

	return error_code;
}


const char* const construct_function_name_prefix = "construct_";
const size_t construct_function_name_prefix_length = 10;
// For consistency.
const size_t construct_function_name_added_chars_length = 10;

int fill_with_construct_function_name(
	char* const to_fill,
	const int to_fill_size,
	const char* const library_name)
{
	// Tells strcat_s to concatenate from the beginning of the string.
	to_fill[0] = '\0';

	int error_code = strcat_s(to_fill, to_fill_size, construct_function_name_prefix);
	if (error_code) return error_code;
	error_code = strcat_s(to_fill, to_fill_size, library_name);
	if (error_code) return error_code;

	return error_code;
}


typedef int(*fill_string_function)(char*, int, const char*);

void fill_string(
	char* to_fill, 
	const int to_fill_size, 
	const char* fill_argument,
	const fill_string_function fill)
{
	const int error_code = fill(to_fill, to_fill_size, fill_argument);
	if (error_code)
	{
		exit(error_code);
	}
}



HMODULE get_library_handle(const char* const library_name, const size_t library_name_array_size)
{
	const size_t library_file_path_array_size =
		library_name_array_size + library_name_added_chars_length;
	// + 1 for null-terminator
	char* library_file_path = (char*)malloc(library_file_path_array_size + 1);

	fill_string(
		library_file_path, 
		library_file_path_array_size, 
		library_name, 
		fill_with_library_file_path);

	printf("Loading library %s from file %s...\n", library_name, library_file_path);

	const HMODULE library_handle = LoadLibraryA((LPCSTR)library_file_path);
	free(library_file_path);

	if (!library_handle)
	{
		exit(LIBRARY_NOT_FOUND);
	}
	
	return library_handle;
}



typedef fill_string_function fill_function_name_function;

void* get_library_function(
	const HMODULE library_handle,
	const char* const library_name,
	const size_t function_name_length,
	const fill_function_name_function fill)
{
	char* library_function_name = (char*)malloc(function_name_length + 1);

	fill_string(
		library_function_name,
		function_name_length,
		library_name,
		fill);

	printf("Reading %s function address...\n", library_function_name);

	// ReSharper disable once CppLocalVariableMayBeConst
	void* requested_function = (void*)GetProcAddress(library_handle, library_function_name);
	free(library_function_name);

	if (!requested_function)
	{
		exit(FUNCTION_NOT_FOUND);
	}

	return requested_function;
}


typedef void* (__cdecl *library_create_function)(const char*);

library_create_function get_library_create_function(
	const HMODULE library_handle, 
	const char* const library_name, 
	const size_t library_name_array_size)
{
	const size_t library_create_method_name_length =
		library_name_array_size + factory_function_name_prefix_length;

	return get_library_function(
		library_handle, 
		library_name,
		library_create_method_name_length,
		fill_with_create_function_name);
}


typedef size_t(__cdecl *library_get_size_function)(void);

library_get_size_function get_library_get_size_function(
	const HMODULE library_handle, 
	const char* const library_name, 
	const size_t library_name_array_size)
{
	const size_t library_get_size_function_name_length =
		library_name_array_size + get_size_function_added_chars_length;

	return get_library_function(
		library_handle, 
		library_name,
		library_get_size_function_name_length,
		fill_with_get_size_function_name);
}


typedef int(__cdecl* library_construct_function)(void*, const char*);

library_construct_function get_library_construct_function(
	const HMODULE library_handle,
	const char* const library_name,
	const size_t library_name_array_size)
{
	const size_t library_construct_function_name_length =
		library_name_array_size + construct_function_name_added_chars_length;

	return get_library_function(
		library_handle,
		library_name,
		library_construct_function_name_length,
		fill_with_construct_function_name);
}



size_t get_required_size(const char* library_name)
{
	const size_t library_name_array_size = strlen(library_name) + 1;

	const HMODULE library_handle = get_library_handle(library_name, library_name_array_size);
	// ReSharper disable once CppLocalVariableMayBeConst


	library_get_size_function library_get_size = get_library_get_size_function(
		library_handle, library_name, library_name_array_size);

	return library_get_size();
}

int construct(const char* library_name, void* object, const char* constructor_argument)
{
	const size_t library_name_array_size = strlen(library_name) + 1;

	const HMODULE library_handle = get_library_handle(library_name, library_name_array_size);

	// ReSharper disable once CppLocalVariableMayBeConst
	library_construct_function library_construct = get_library_construct_function(
		library_handle, library_name, library_name_array_size);

	return library_construct(object, constructor_argument);
}


void* create(const char* const library_name, const char* const constructor_argument)
{
	const size_t library_name_array_size = strlen(library_name) + 1;

	const HMODULE library_handle = get_library_handle(library_name, library_name_array_size);

	
	// ReSharper disable once CppLocalVariableMayBeConst
	library_create_function library_create = get_library_create_function(
		library_handle, library_name, library_name_array_size);

	return library_create(constructor_argument);
}
