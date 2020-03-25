// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
#ifndef CONSTRUCTOR_POLYMORPHISM_BEHAVIOUR_HPP
#define CONSTRUCTOR_POLYMORPHISM_BEHAVIOUR_HPP


#include <cstdio>


class base
{
public:
    base()
	{
        method();
    }

    virtual void virtual_method()
	{
        printf("base\n");
    }

    void method()
	{
        printf("method: ");
        virtual_method();
    }
};

class derived : public base
{
public:
    derived() : base()
	{
        method();
    }

    void virtual_method() override
    {
        printf("derived\n");
    }
};


void test_constructor_polymorphism_behaviour();


#endif // !CONSTRUCTOR_POLYMORPHISM_BEHAVIOUR_HPP
