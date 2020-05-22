#include "pch.hpp"

#include "factory.hpp"


#include "animal_types.hpp"



int main() // NOLINT(bugprone-exception-escape)
{
	auto& animal_factory{ oouplab::factory<oouplab::animal>::instance() };

	std::unordered_set<std::string> type_names{ animal_factory.get_type_name_count() };
    animal_factory.fill_with_type_names(std::inserter(type_names, type_names.begin()));

	for (const auto& type_name : type_names)
	{
        std::ostringstream output_string_stream{ };

        const auto current_animal = 
			animal_factory.create(type_name, output_string_stream.str());

		output_string_stream << "Pet " << type_name << " ";
		output_string_stream << "says " << current_animal->greet() << " ";
		output_string_stream << "and wants " << current_animal->menu() << ".";

		std::cout << output_string_stream.str() << std::endl;
    }
}
