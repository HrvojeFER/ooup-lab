#ifndef OOUP_LAB_EXERCISE_3_TASK_1_3_PARROT_HPP
#define OOUP_LAB_EXERCISE_3_TASK_1_3_PARROT_HPP


#include "pch.hpp"

#include "factory.hpp"

#include "animal.hpp"


namespace oouplab
{
	struct parrot final : animal
	{
	private:
		std::string name_;

	public:
		explicit parrot(std::string name) :
			animal{ },
			name_{ std::move(name) } { }

		
	private:
		static std::shared_ptr<animal> create(const std::string& name)
		{
			return std::reinterpret_pointer_cast<animal>(std::make_shared<parrot>(name));
		}

		static inline const factory<animal>::creator_register factory_register
		{
			factory<animal>::instance().register_creator("parrot", create)
		};


	public:
		std::string name() override
		{
			return name_;
		}

		std::string greet() override
		{
			return std::string{ "KA KAAAA" };
		}

		std::string menu() override
		{
			return std::string{ "Greens" };
		}
	};
}


#endif
