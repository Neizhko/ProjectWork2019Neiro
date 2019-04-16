#pragma once
#include <string>

/*It's only a prototype*/

namespace Settings_module
{
	struct Setting
	{
		Setting() = default;
		unsigned long id;
		std::string movement;
		std::string keys;
		double x, y, dx, dy, mouseDelay;
		bool isNULL = false;
	};
}
