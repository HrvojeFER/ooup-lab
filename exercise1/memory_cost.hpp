#ifndef MEMORY_COST_HPP
#define MEMORY_COST_HPP


/*
 * CoolClass contains a virtual table pointer,
 * so in a 32-bit environment it is 4 bytes larger than the PlainOldClass.
 * In a 64-bit environment it is 12 bytes larger which could be because the virtual table pointer is 8 bytes long
 * and one of the classes is not properly aligned, so the compiler leaves out 4 bytes of extra space.
 * Compiler used: MSVC v142
 */
void print_virtual_tables_memory_cost();


#endif
