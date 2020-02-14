#pragma once

#include <vector>
#include <set>
#include <unordered_map>

struct Equation
{
	Equation() = default;
	Equation(std::string const& lft, std::string const& rgh)
		: left(lft), right(rgh)
	{}

	std::string left;
	std::string right;
};

struct Storage
{
	std::vector<Equation> equations;
	std::unordered_map<char, int> variables;
	std::set<char> vars_to_find;
};

void print_storage(Storage const& storage);
