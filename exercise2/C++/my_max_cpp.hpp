#ifndef OOUP_LAB_EXERCISE2_MY_MAX_HPP
#define OOUP_LAB_EXERCISE2_MY_MAX_HPP

// ReSharper disable once CppUnusedIncludeDirective
#include "pch.hpp"

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
