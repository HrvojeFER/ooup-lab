#include "my_max_cpp.hpp"

namespace ooup_lab
{
	namespace exercise2
	{
		template<typename Iterator, typename Predicate>
		Iterator my_max_cpp(Iterator first, Iterator last, const Predicate& gt_predicate)
		{
			Iterator max = first;
			
			while(++first != last)
			{
				if (gt_predicate(*first, *max))
				{
					max = first;
				}
			}

			return max;
		}
		
		void my_max_main_cpp()
		{
			int arr_int[] = { 1, 3, 5, 7, 4, 6, 9, 2, 0 };
			// ReSharper disable StringLiteralTypo
			char arr_char[] = "Suncana strana ulice";
			const char* arr_str[] =
			{
			   "gle", "malu", "vocku", "poslije", "kise",
			   "puna", "je", "kapi", "pa", "ih", "njise"
			};
			// ReSharper enable StringLiteralTypo

			std::vector<int> vec_int = { 1, 3, 5, 7, 4, 6, 9, 2, 0 };
			std::set<int> set_int = { vec_int.begin(), vec_int.end() };
			std::vector<std::string> vec_string = 
			{
			   "gle", "malu", "vocku", "poslije", "kise",
			   "puna", "je", "kapi", "pa", "ih", "njise"
			};

			const auto gt_int = [] (const int first, const int second)
			{
				return first > second;
			};
			const auto gt_char = [] (const char first, const char second)
			{
				return first > second;
			};
			const auto gt_str = [](const std::string& first, const std::string& second)
			{
				return strcmp(first.c_str(), second.c_str()) > 0;
			};

			
			std::cout << "C style arrays:" << std::endl;
			
			std::cout << "max int: " << 
				*my_max_cpp(std::begin(arr_int), std::end(arr_int), gt_int) << std::endl;

			std::cout << "max char: " << 
				*my_max_cpp(std::begin(arr_char), std::end(arr_char), gt_char) << std::endl;

			std::cout << "max string: " <<
				*my_max_cpp(std::begin(arr_str), std::end(arr_str), gt_str) << std::endl;

			std::cout <<  std::endl << "C++ STL:" << std::endl;

			std::cout << "max int (vector): " <<
				*my_max_cpp(vec_int.begin(), vec_int.end(), gt_int) << std::endl;

			std::cout << "max int (set): " <<
				*my_max_cpp(set_int.begin(), set_int.end(), gt_int) << std::endl;

			std::cout << "max string (vector): " << 
				*my_max_cpp(vec_string.begin(), vec_string.end(), gt_str) << std::endl;
		}
	}
}
