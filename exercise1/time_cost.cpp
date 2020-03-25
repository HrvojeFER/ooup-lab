#include "time_cost.hpp"


/*
 * Answers for task 4:
 *
 * 2.) cool constructor call line calls new and has additional operations for checking allocation success.
 *	   plain_old_class constructor call line just calls its constructor.
 *
 * 3.) call ??plain_old_class@@QAE@XZ
 *
 * 4.) call ??cool_class@@QAE@XZ
 *	   The constructor calls the base constructor and then it sets the vf_table.
 *
 * 5.) plain_old_class::set puts 42 on the stack and calls the function, whereas the base::set had to find
 *	   the pointer to the function before doing what plain_old_class::set had done.
 *
 * 6.) The cool_class vf_table definition has functions get and set. It is initialized at the top of the
 *     assembler file.
 */
void time_cost()
{
    plain_old_class plain_old_class;
    base* cool = new cool_class;
    plain_old_class.set(42);
    cool->set(42);

    delete cool;  // NOLINT(clang-diagnostic-delete-abstract-non-virtual-dtor)
}
