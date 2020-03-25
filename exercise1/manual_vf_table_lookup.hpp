// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
#ifndef MANUAL_VF_TABLE_LOOKUP_HPP
#define MANUAL_VF_TABLE_LOOKUP_HPP


class b
{
public:
	virtual int __cdecl first() = 0;
	virtual int __cdecl second(int) = 0;
};

class d : public b
{
public:
	int __cdecl first() override { return 42; }
	int __cdecl second(const int x) override
	{
		return first() + x;
	}
};


void print_manual_vf_table_lookup_result();
void print_manual_vf_table_lookup_result(b*);


#endif // !MANUAL_VF_TABLES_HPP
