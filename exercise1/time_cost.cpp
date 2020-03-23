#include "time_cost.hpp"


// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
class base {
public:
	virtual void set(int x) = 0;
    virtual int get() = 0;
};

// ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
class cool_class : public base {
public:
	void set(const int x) override { x_ = x; };
	int get() override { return x_; };
private:
    int x_ = 0;
};

class plain_old_class {
public:
    void set(const int x) { x_ = x; };
    int get() const { return x_; };
private:
    int x_ = 0;
};


void time_cost()
{
    plain_old_class plain_old_class;
    base* cool = new cool_class;
    plain_old_class.set(42);
    cool->set(42);

    delete cool;  // NOLINT(clang-diagnostic-delete-abstract-non-virtual-dtor)
}
