#ifndef OOUP_LAB_EXERCISE2_MY_MAX_HPP
#define OOUP_LAB_EXERCISE2_MY_MAX_HPP

// ReSharper disable once CppUnusedIncludeDirective
#include "pch.hpp"


// This approach is very good in terms of respecting SOLID principles, however
// the compiler creates a new function for each combination of types we are using
// (in our case we are using it with six different type combinations and
// that results in the creation of six different functions) of the template function my_max_cpp and
// since we are using iterators and predicates and not straight up pointers,
// we are adding overhead to calls to accessing elements of containers and
// the predicate which results in higher execution times.
// The higher execution time is not noticeable on a small scale, but
// it might be on a large scale where performance is critical.


namespace ooup_lab
{
	namespace exercise2
	{
		template<typename Iterator, typename Predicate>
		Iterator my_max_cpp(Iterator first, Iterator last, const Predicate& gt_predicate);

		void my_max_main_cpp();
	}
}

#endif
