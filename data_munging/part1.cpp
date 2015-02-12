#include "part1.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <datafile>\n";
		return 1;
	}

	std::ifstream ifs {argv[1]};
	if (!ifs.good())
	{
		std::cerr << "Error opening the file '" << argv[1] << "'.\n";
		return 1;
	}

	auto data = read_weather_data(ifs);
	ifs.close();

	auto it = find_max_spread_element(data.begin(), data.end());
	if (it != data.end())
	{
		std::cout << "Day with maximum temperature spread: "
		          << std::get<0>(*it)
		          << "\n";
	}
	else
	{
		std::cerr << "Error: No data found.\n";
		return 1;
	}
}
