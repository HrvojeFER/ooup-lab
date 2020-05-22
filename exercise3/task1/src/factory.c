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
	to_fill[0] = '\0';

	int error_number = strcat_s(to_fill, to_fill_size, current_folder_relative_path);
	if (error_number) return error_number;
	error_number = strcat_s(to_fill, to_fill_size, library_name);
	if (error_number) return error_number;
	error_number = strcat_s(to_fill, to_fill_size, dll_extension);
	if (error_number) return error_number;

	return error_number;
}


const char* const factory_method_name_prefix = "create_";
const size_t factory_method_name_prefix_length = 7;

int fill_with_library_create_method_name(
	char* const to_fill, 
	const int to_fill_size, 
	const char* const library_name)
{
	to_fill[0] = '\0';

	int error_number = strcat_s(to_fill, to_fill_size, factory_method_name_prefix);
	if (error_number) return error_number;
	error_number = strcat_s(to_fill, to_fill_size, library_name);
	if (error_number) return error_number;

	return error_number;
}


typedef int(*fill_string_function)(char*, int, const char*);

void fill_string(
	char* to_fill, 
	const int to_fill_size, 
	const char* fill_argument,
	const fill_string_function fill)
{
	const int error_number = fill(to_fill, to_fill_size, fill_argument);
	if (error_number)
	{
		exit(error_number);
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


typedef void* (__cdecl *library_create_function)(const char*);

library_create_function get_library_create_function(
	const HMODULE library_handle, const char* const library_name, const size_t library_array_size)
{
	const size_t library_create_method_name_length =
		library_array_size + factory_method_name_prefix_length;
	// + 1 for null-terminator
	char* library_create_method_name = (char*)malloc(library_create_method_name_length + 1);

	fill_string(
		library_create_method_name,
		library_create_method_name_length,
		library_name,
		fill_with_library_create_method_name);

	printf("Reading %s function address...\n", library_create_method_name);

	// ReSharper disable once CppLocalVariableMayBeConst
	library_create_function create_function =
		(library_create_function)GetProcAddress(
			library_handle, library_create_method_name);
	free(library_create_method_name);

	if(!create_function)
	{
		exit(CREATE_METHOD_NOT_FOUND);
	}
	
	return create_function;
}



void* create(const char* const library_name, const char* const constructor_argument)
{
	const size_t library_name_array_size = strlen(library_name) + 1;

	const HMODULE library_handle = get_library_handle(library_name, library_name_array_size);
	// ReSharper disable once CppLocalVariableMayBeConst

	library_create_function library_create = get_library_create_function(
		library_handle, library_name, library_name_array_size);

	void* result = library_create(constructor_argument);
	/*while (!FreeLibrary(library_handle))
	{
		printf("Failed to free library %s. Trying again...", library_name);
	}*/
	
	return result;
}
