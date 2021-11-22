#ifndef OOUP_LAB_EXERCISE_3_TASK_1_3_TIGER_HPP
#define OOUP_LAB_EXERCISE_3_TASK_1_3_TIGER_HPP


#include "pch.hpp"

#include "factory.hpp"


#include "animal.hpp"



namespace oouplab
{
	struct tiger final : animal
	{
	private:
		std::string name_;

	public:
		explicit tiger(std::string name) :
			animal{ },
			name_{ std::move(name) } { }


	private:
		static std::shared_ptr<animal> create(const std::string& name)
		{
			return std::reinterpret_pointer_cast<animal>(std::make_shared<tiger>(name));
		}

		static inline const factory<animal>::creator_register factory_register
		{
			factory<animal>::instance().register_creator("tiger", create)
		};

		
	public:
		std::string name() override
		{
			return name_;
		}

		std::string greet() override
		{
			return std::string{ "meow" };
		}

		std::string menu() override
		{
			return std::string{ "MEAT" };
		}
	};
}


#endif
