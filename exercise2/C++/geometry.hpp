#ifndef OOUP_LAB_EXERCISE2_GEOMETRY_HPP
#define OOUP_LAB_EXERCISE2_GEOMETRY_HPP

#include "pch.hpp"

namespace ooup_lab
{
	namespace exercise2
	{
		struct point
		{
			int x{ 0 };
			int y{ 0 };
		};

		struct shape
		{
			enum class e_type { circle, square, rhomb };

			e_type type;
		};

		struct circle
		{
			shape::e_type type{ shape::e_type::circle };
			double radius{ 1.0f };
			point center{};
		};

		struct square
		{
			shape::e_type type{ shape::e_type::square };
			double side{ 1.0f };
			point center{};
		};

		struct rhomb
		{
			shape::e_type type{ shape::e_type::rhomb };
			double a{ 1.0f };
			double b{ 2.0f };
			double angle{ 1.0f }; // in radians close to pi / 3
			point center{};
		};

		inline void draw_square(struct square*)
		{
			std::cerr << "in draw_square" << std::endl;
		}

		inline void draw_circle(struct circle*)
		{
			std::cerr << "in draw_circle" << std::endl;
		}
		inline void draw_rhomb(struct rhomb*)
		{
			std::cerr << "in draw_rhomb" << std::endl;
		}

		inline void draw_shapes(const std::vector<shape*>& shapes)
		{
			for (auto s : shapes)
			{
				switch (s->type)
				{
				case shape::e_type::square:
					draw_square(reinterpret_cast<struct square*>(s));
					break;
				case shape::e_type::circle:
					draw_circle(reinterpret_cast<struct circle*>(s));
					break;
				case shape::e_type::rhomb:
					draw_rhomb(reinterpret_cast<struct rhomb*>(s));
					break;
				default:
					assert(0);
					exit(0);
				}
			}
		}

		inline void move_square(struct square* square, const int dx, const int dy)
		{
			square->center = { square->center.x + dx, square->center.y + dy };
			
			std::cerr << "in draw_square -> x:" << square->center.x << 
				" y: " << square->center.y << std::endl;
		}

		inline void move_circle(struct circle* circle, const int dx, const int dy)
		{
			circle->center = { circle->center.x + dx, circle->center.y + dy };

			std::cerr << "in draw_square -> x:" << circle->center.x << 
				" y: " << circle->center.y << std::endl;
		}
		inline void move_rhomb(struct rhomb* rhomb, const int dx, const int dy)
		{
			rhomb->center = { rhomb->center.x + dx, rhomb->center.y + dy };

			std::cerr << "in draw_square -> x:" << rhomb->center.x << 
				" y: " << rhomb->center.y << std::endl;
		}

		inline void move_shapes(const std::vector<shape*>& shapes, const int dx, const int dy)
		{
			for (auto s : shapes)
			{
				switch (s->type)
				{
				case shape::e_type::square:
					move_square(reinterpret_cast<struct square*>(s), dx, dy);
					break;
				case shape::e_type::circle:
					move_circle(reinterpret_cast<struct circle*>(s), dx, dy);
					break;
				// If we forget to add this case the switch goes to default which
				// breaks the whole program because of the assert(0).
				case shape::e_type::rhomb:
					move_rhomb(reinterpret_cast<struct rhomb*>(s), dx, dy);
					break;
				default:
					assert(0);
					exit(0);
				}
			}
		}

		inline void geo_main()
		{
			std::vector<shape*> shapes;

			// All shapes have a default center position of (0, 0).
			shapes.emplace_back(reinterpret_cast<shape*>(new circle{}));
			shapes.emplace_back(reinterpret_cast<shape*>(new square{}));
			shapes.emplace_back(reinterpret_cast<shape*>(new square{}));
			shapes.emplace_back(reinterpret_cast<shape*>(new circle{}));
			shapes.emplace_back(reinterpret_cast<shape*>(new rhomb{}));

			draw_shapes(shapes);

			// All shapes should have the center position of (dx, dy) if the default constructor is used.
			move_shapes(shapes, 1, 1);

			// Cleanup
			for (auto shape : shapes)
			{
				delete shape;
			}

			shapes.erase(shapes.begin(), shapes.end());
		}
	}
}


#endif
