#include "Parser.hpp"

#include <iostream>
#include <regex>
#include <algorithm>

namespace {
	const std::map<char, int> priority = {
		{'|', 0}, {'+', 1}, {'^', 2}, {'!', 3}, {'(', 4}, {')', 5}
	};

	void delete_spaces_and_comments(std::string& str)
	{
		std::size_t comment_start_idx = str.rfind('#');
		if (comment_start_idx != std::string::npos)
		{
			str.erase(comment_start_idx);
		}
		str.erase(std::remove_if(str.begin(), str.end(), [](char c){
			return isspace(c);
		}), str.end());
	}

	bool is_operation(char c)
	{
		return ((c == '+' || c == '|' || c == '!' || c == '^'));
	}
}// namespace

int	Parser::reverse_polish_entry(std::string const& str, std::vector<char>& out)
{
	std::vector<char> buffer;
	int i = 0;
	for (auto c : str)
	{
		if (priority.find(c) == priority.end())
			out[i++] = c;
		else
		{
			if (c == '(')
				buffer.push_back(c);
			else if (c == ')')
			{
				char tmp = buffer.back();
				buffer.pop_back();
				while (tmp != '(')
				{
					out[i++] = tmp;
					tmp = buffer.back();
					buffer.pop_back();
				}
			}
			else
			{
				if (buffer.empty())
					buffer.push_back(c);
				else if (priority.find(c)->second <= priority.find(buffer.back())->second and buffer.back() != '(')
				{
					out[i++] = buffer.back();
					buffer.pop_back();
					buffer.push_back(c);
				}
				else
					buffer.push_back(c);
			}
		}
	}
	while (!buffer.empty())
	{
		out[i++] = buffer.back();
		buffer.pop_back();
	}
	return (i);
}

void	Parser::parser(std::string const& rule)
{
	std::size_t found = rule.find("=>");
	std::string left_part = rule.substr(0, found);
	std::string right_part = rule.substr(found + 2);
	std::vector<char> vec_left(left_part.length());
	std::vector<char> vec_right(right_part.length());
	int len_l = reverse_polish_entry(left_part, vec_left);
	int len_r = reverse_polish_entry(right_part, vec_right);

	std::string left = std::string(vec_left.data(), len_l);
	std::string right = std::string(vec_right.data(), len_r);

	if (rule[0] == '=')
	{
		std::size_t size = rule.size();
		for (std::size_t i = 1; i < size; ++i)
		{
			_storage->variables[rule[i]] = 1;
		}
	}
	else if (rule[0] == '?')
	{
		std::size_t size = rule.size();
		for (std::size_t i = 1; i < size; ++i)
		{
			_storage->vars_to_find.insert(rule[i]);
		}
	}
	else
	{
		Equation equ{left, right};

		if (_need_log)
		{
			std::cout << "left: [" << equ.left << "] right: [" << equ.right << "]" << std::endl;
		}

		_storage->equations.push_back(equ);
		
		for (char c : equ.left)
		{
			if (is_operation(c))
			{
				continue;
			}

			_storage->variables[c] = (_storage->variables[c] == 1 ? 1 : 0);
		}

		for (char c : equ.right)
		{
			if (is_operation(c))
			{
				continue;
			}

			_storage->variables[c] = (_storage->variables[c] == 1 ? 1 : 0);
		}
	}
}

void	Parser::check_left(std::string const& str)
{
	char prev = '\0';
	int n_bracket = 0;
	for (auto symb : str)
	{
		if ((symb >= 'A' and symb <= 'Z') or symb == '(')
		{
			if (prev == '\0' or prev == '(' or prev == '!' or prev == '+' or prev == '|' or prev == '^')
				prev = symb;
			else
				throw std::runtime_error(std::string("Before \"") + symb + "\" can`t be \"" + prev + "\".");
			if (symb == '(')
				n_bracket++;
		}
		else if (symb == ')' or symb == '+' or symb == '|' or symb == '^')
		{
			if ((prev >= 'A' && prev <= 'Z') or prev == ')')
				prev = symb;
			else
				throw std::runtime_error(std::string("Before \"") + symb + "\" can`t be \"" + prev + "\".");
			if (symb == ')' and n_bracket > 0)
				n_bracket--;
			else if (symb == ')' and n_bracket == 0)
				throw std::runtime_error("Extra close bracket in left part of rule.");
		}
		else if (symb == '!')
		{
			if (prev == '\0' or prev == '(' or prev == '+' or prev == '|' or prev == '^')
				prev = symb;
			else
				throw std::runtime_error(std::string("Before \"") + symb + "\" can`t be \"" + prev + "\".");
		}
		else
			throw std::runtime_error(std::string("Unknown symbol \"") + symb + "\" in left part of rule.");
	}
	if (n_bracket != 0)
		throw std::runtime_error("There are unclosed opening brackets in the left part of rule.");
	if (prev == '\0' or prev == '(' or prev == '!' or prev == '+' or prev == '|' or prev == '^')
		throw std::runtime_error(std::string("Left part of rule can`t end with \"") + prev + "\" symbol.");
}

void	Parser::check_right(std::string const& str)
{
	char prev = '\0';
	int n_bracket = 0;
	for (auto symb : str)
	{
		if ((symb >= 'A' and symb <= 'Z') or symb == '(')
		{
			if (prev == '\0' or prev == '(' or prev == '!' or prev == '+')
				prev = symb;
			else
				throw std::runtime_error(std::string("Before \"") + symb + "\" can`t be \"" + prev + "\" in right part of rule.");
			if (symb == '(')
				n_bracket++;
		}
		else if (symb == ')' or symb == '+')
		{
			if ((prev >= 'A' && prev <= 'Z') or prev == ')')
				prev = symb;
			else
				throw std::runtime_error(std::string("Before \"") + symb + "\" can`t be \"" + prev + "\" in right part of rule.");
			if (symb == ')' and n_bracket > 0)
				n_bracket--;
			else if (symb == ')' and n_bracket == 0)
				throw std::runtime_error("Extra close bracket in right part of rule.");
		}
		else if (symb == '!')
		{
			if (prev == '\0' or prev == '(' or prev == '+')
				prev = symb;
			else
				throw std::runtime_error(std::string("Before \"") + symb + "\" can`t be \"" + prev + "\" in right part of rule.");
		}
		else
			throw std::runtime_error(std::string("Unknown symbol \"") + symb + "\" in right part of rule.");
	}
	if (n_bracket != 0)
		throw std::runtime_error("There are unclosed opening brackets in the right part of rule.");
	if (prev == '\0' or prev == '(' or prev == '!' or prev == '+' or prev == '|' or prev == '^')
		throw std::runtime_error(std::string("Right part of rule can`t end with \"") + prev + "\" symbol.");
}

void	Parser::lexer(std::string const& rule)
{
	if (rule[0] != '=' && rule[0] != '?')
	{
		std::string left_part;
		std::string right_part;
		std::size_t found = rule.find("=>");
		if (found != std::string::npos)
		{
			left_part = rule.substr(0, found);
			right_part = rule.substr(found + 2);
			check_left(left_part);
			check_right(right_part);
		}
		else
		{
			throw std::runtime_error("Rule don't have implies symbol \"=>\".");
		}
		if (_end_of_rules == true)
		{
			throw std::runtime_error("You can`t write rules after facts.");
		}
	}
	else
	{
		std::regex r_fact("=[A-Z]*(#.*)?");
		std::regex r_quer("\\?[A-Z]+(#.*)?");
		if (std::regex_match(rule, r_fact))
		{
			if (_facts == true)
			{
				throw std::runtime_error("After fact must be written a query.");
			}
			_facts = true;
			_end_of_rules = true;
		}
		else if (std::regex_match(rule, r_quer))
		{
			if (_facts == false)
			{
				throw std::runtime_error("Before query must be written a fact.");
			}
			_facts = false;
		}
		else
		{
			throw std::runtime_error("Unknown instruction.");
		}
	}
}

void	Parser::process()
{
	_storage = std::make_unique<Storage>();

	std::string token;
	while (_input_provider->read_next_input(token))
	{
		try {
			if (_need_log)
			{
				std::cout << token << std::endl;
			}
			delete_spaces_and_comments(token);
			if (token.empty())
			{
				continue;
			}

			lexer(token);
			parser(token);
		} catch (std::exception const& e)
		{
			std::cout << "\033[1;31mException: " << e.what() << "\033[0m\n";
		}
	}
}
