#ifndef OOUP_LAB_EXERCISE_3_TASK_1_3_FACTORY_HPP
#define OOUP_LAB_EXERCISE_3_TASK_1_3_FACTORY_HPP


#include "pch.hpp"


namespace oouplab
{
    // factory.hpp
    template<typename BaseType>
    struct factory
	{
        using base_type = BaseType;
        using creator_function = std::function<std::shared_ptr<BaseType>(const std::string&)>;

    private:
        using creator_map = std::unordered_map<std::string, creator_function>;
        creator_map creators_;

    	
    public:
    	factory(factory&) = delete;
    	factory& operator=(factory&) = delete;
        factory(factory&&) = delete;
        factory& operator=(factory&&) = delete;

    private:
        factory() = default;
        ~factory() = default;
    	
    public:
        [[nodiscard]] static factory& instance()
    	{
            static factory singleton{ };
            return singleton;
        }


        using creator_register = typename creator_map::iterator;
    	
    	creator_register register_creator(
            const std::string& type_name, creator_function create)
        {
            return creators_.emplace(type_name, std::move(create)).first;
        }

        [[nodiscard]] std::shared_ptr<BaseType> create(
            const std::string& type_name, const std::string& argument)
        {
            const auto iterator = creators_.find(type_name);
        	if (iterator == creators_.end())
        	{
                throw std::runtime_error{ "Type name key not found." };
        	}
        	
            return iterator->second(argument);
        }

    	
    	[[nodiscard]] size_t get_type_name_count() const
        {
            return creators_.size();
        }

    	// Forward iterator tag does not inherit from output iterator tag from which all other
    	// qualified iterator tags inherit.
    	template<typename Iterator, std::enable_if_t<
    		std::is_convertible_v<typename std::iterator_traits<Iterator>::iterator_category,
    			std::output_iterator_tag> ||
			std::is_convertible_v<typename std::iterator_traits<Iterator>::iterator_category,
				std::forward_iterator_tag>,
    	int> = 0>
        void fill_with_type_names(const Iterator& begin)
    	{
            std::transform(creators_.begin(), creators_.end(), begin, 
                [](const typename creator_map::value_type& creator_pair) -> std::string
	            {
                    return creator_pair.first;
	            });
    	}
    };
}


#endif
