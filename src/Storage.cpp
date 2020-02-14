#include "Storage.hpp"

#include <iostream>

void print_storage(Storage const& storage)
{
	std::cout << std::endl << "Storage:" << std::endl;
	std::cout << "\tEquations:" << std::endl;
	for (auto const& equation : storage.equations)
	{
		std::cout << "\t\tleft: " << equation.left << " right: " << equation.right << std::endl;
	}
	std::cout << "\tVariables:" << std::endl;
	for (auto const& variable : storage.variables)
	{
		std::cout << "\t\tvar: " << variable.first << " state: " << variable.second << std::endl;
	}
	std::cout << "\tVariable to find:" << std::endl;
	for (auto variable : storage.vars_to_find)
	{
		std::cout << "\t\tvar: " << variable << std::endl;
	}
	std::cout << std::endl;
}
