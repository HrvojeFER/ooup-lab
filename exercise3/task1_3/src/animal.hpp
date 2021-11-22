#ifndef OOUP_LAB_EXERCISE_3_TASK_1_3_ANIMAL_HPP
#define OOUP_LAB_EXERCISE_3_TASK_1_3_ANIMAL_HPP


#include "pch.hpp"


namespace oouplab
{
	struct animal
	{
		animal() = default;
		virtual ~animal() = default;

		animal(animal&) = delete;
		animal& operator=(animal&) = delete;
		animal(animal&&) = delete;
		animal& operator=(animal&&) = delete;

		
		virtual std::string name() = 0;
		virtual std::string greet() = 0;
		virtual std::string menu() = 0;
	};
}


#endif
