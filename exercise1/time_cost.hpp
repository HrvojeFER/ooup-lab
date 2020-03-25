// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
#ifndef TIME_COST_HPP
#define TIME_COST_HPP


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
void time_cost();


class base
{
public:
    virtual void set(int x) = 0;
    virtual int get() = 0;
};

class cool_class : public base
{
public:
    void set(const int x) override { x_ = x; }
    int get() override { return x_; }

private:
    int x_ = 0;
};

class plain_old_class
{
public:
    void set(const int x) { x_ = x; }
    int get() const { return x_; }

private:
    int x_ = 0;
};


#endif
