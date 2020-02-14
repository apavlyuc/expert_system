#include "FlagsHandler.hpp"

#include <iostream>
#include <set>

namespace {
	// std::string	-> flag name
	// bool			-> has value or not
	const std::unordered_map<std::string, bool> flags{
		{ "-f", true },
		{ "-v", false },
		{ "-vv", false }
	};

	const std::set<std::string> required_flags{

	};

	void print_usage(std::string const& exec_name)
	{
		std::cout << "NAME" << std::endl;
		std::cout << "\t" << exec_name << " - expert system executable" << std::endl << std::endl;

		std::cout << "SYNOPSIS" << std::endl;
		std::cout << "\t" << exec_name << " [OPTION]..." << std::endl << std::endl;

		std::cout << "REQUIRED_FLAGS" << std::endl;
		std::cout << "\t";
		for (auto const& flag : required_flags)
		{
			std::cout << flag << ' ';
		}
		std::cout << std::endl;

		std::cout << "DESCRIPTION" << std::endl;
		{
			std::cout << "\t-f file," << std::endl;
			std::cout << "\t\t File to be processed. Contains facts, rules, goals." << std::endl;

			std::cout << "\t-v," << std::endl;
			std::cout << "\t\t Turn on verbouse mode. More logs are shown." << std::endl;

			std::cout << "\t-vv," << std::endl;
			std::cout << "\t\t Turn on verbouse mode. All log messages are shown." << std::endl;

			std::cout << "\t-h," << std::endl;
			std::cout << "\t\t Display this message and exit." << std::endl;
		}
	}
}// namespace

std::shared_ptr<CreationContext> FlagsHandler::create_CreationContext(int ac, char **av) const noexcept
{
	std::shared_ptr<CreationContext> ret = std::make_shared<CreationContext>();

	try {
		for (int i = 1; i < ac; ++i)
		{
			bool has_value = flags.at(av[i]);
			if (has_value)
			{
				ret->_flag_value[av[i]] = av[i + 1];
				++i;
			}
			else
			{
				ret->_flag_value[av[i]];
			}
		}

		for (auto const& flag : required_flags)
		{
			ret->_flag_value.at(flag);
		}
	} catch (...)
	{
		print_usage(av[0]);
		exit(1);
	}

	if (ret->is_flag_exists("-h"))
	{
		print_usage(av[0]);
		exit(2);
	}

	return ret;
}