#include "Solver.hpp"

#include <utility>
#include <iostream>
#include <algorithm>

namespace {
	bool is_operation(char c)
	{
		return (c == '|' || c == '^' || c == '+' || c == '!');
	}

	int performe_operation(int a, int b, char operation)
	{
		switch (operation)
		{
			case '+':
			{
				if (a == -1 || b == -1)
				{
					return -1;
				}
				if (a == 0 || b == 0)
				{
					return 0;
				}
				return 1;
			}
			case '|':
			{
				if (a == 1 || b == 1)
				{
					return 1;
				}
				if (a == 0 || b == 0)
				{
					return 0;
				}
				return -1;
			}
			case '^':
			{
				if (a == 0 || b == 0)
				{
					return 0;
				}
				return (a == b ? -1 : 1);
			}
		}
		std::cout << "i don't know this operation type" << std::endl;
		exit(3);
	}

	int performe_operation(int a, char operation)
	{
		switch (operation)
		{
			case '!':
			{
				if (a == 1) return -1;
				if (a == -1) return 1;
				return a;
			}
		}
		std::cout << "i don't know this operation type" << std::endl;
		exit(4);
	}

	bool solve_equation_part(std::string part, std::unordered_map<char, int> const& variables, bool is_recalculation, bool need_log)
	{
		if (need_log)
		{
			std::cout << "part [" << part << "]" << std::endl;
		}

		std::string data;
		{
			for (char c : part)
			{
				if (is_operation(c))
				{
					data.push_back(c);
				}
				else
				{
					int val = variables.at(c);
					if (is_recalculation && val == 0)
					{
						val = -1;
					}
					data.push_back((char)val);
				}
			}
		}

		for (int i = 0; i < (int)data.size(); ++i)
		{
			if (is_operation(data[i]))
			{
				if (data[i] == '!')
				{
					int val = performe_operation(data[i - 1], '!');
					data[i] = val;
					data.erase(i - 1, 1);
					i = -1;
				}
				else
				{
					int val = performe_operation(data[i - 2], data[i - 1], data[i]);
					data[i] = val;
					data.erase(i - 2, 2);
					i = -1;
				}
			}
		}

		return (data[0] == 1);
	}

}// namespace

void Solver::solve_unknown_variables(Storage storage)
{
	bool is_recalculate = false;

	auto start_equation_processing = [this, &storage](bool recalculation) {
		int size = storage.equations.size();
		for (int i = 0; i < size; ++i)
		{
			bool is_smg_changed = _process_equation(storage, storage.equations[i], recalculation);
			if (is_smg_changed)
			{
				i = -1;
			}
		}
	};

	auto store_solved_vars = [this, &storage](bool& is_recalculate)
	{
		for (char c : storage.vars_to_find)
		{
			_solved_var[c] = storage.variables[c];
			if (_solved_var[c] == 0)
			{
				is_recalculate = true;
			}
		}
	};

	start_equation_processing(is_recalculate);
	store_solved_vars(is_recalculate);

	if (!is_recalculate)
	{
		return;
	}

	if (_need_log)
	{
		std::cout << "Recalculation." << std::endl;
	}

	start_equation_processing(is_recalculate);
	store_solved_vars(is_recalculate);
}

/*
**	return true, if some variables has been changed
*/
bool	Solver::_process_equation(Storage& storage, Equation& equation, bool recalculation)
{
	bool left_result = solve_equation_part(equation.left, storage.variables, recalculation, _need_log);
	if (_need_log)
	{
		std::cout << "left_result: " << left_result << std::endl;
	}
	if (left_result == false)
	{
		return false;
	}

	bool right_result = solve_equation_part(equation.right, storage.variables, recalculation, _need_log);
	if (_need_log)
	{
		std::cout << "right_result: " << right_result << std::endl;
	}
	if (right_result == false)
	{
		bool is_vars_changed_normaly = _change_variables(storage, equation.right);
		if (is_vars_changed_normaly == false)
		{
			std::cout << "some shit is happened. _change_variables return false" << std::endl;
			exit(5);
		}
		return true;
	}
	return false;
}

bool	Solver::_change_variables(Storage& storage, std::string const& right_part)
{
	if (right_part.size() <= 2)
	{
		char var = right_part[0];
		if (storage.variables[var] != 0)
		{
			return false;
		}

		if (right_part[1] == '!')
		{
			if (_need_log)
			{
				std::cout << "Var [" << var << "] set to false" << std::endl;
			}
			storage.variables[var] = -1;
		}
		else
		{
			if (_need_log)
			{
				std::cout << "Var [" << var << "] set to true" << std::endl;
			}
			storage.variables[var] = 1;
		}
		return true;
	}
	else if (right_part.size() == 3)
	{
		if (right_part[2] != '+')
		{
			std::cout << "unexpected operation in right part [" << right_part[2] << ']' << std::endl;
			exit(7);
		}
		char var_a = right_part[0];
		char var_b = right_part[1];

		if (storage.variables[var_a] != 0 || storage.variables[var_b] != 0)
		{
			return false;
		}
		if (_need_log)
		{
			std::cout << "Var [" << var_a << "] set to true" << std::endl;
			std::cout << "Var [" << var_b << "] set to true" << std::endl;
		}
		storage.variables[var_a] = 1;
		storage.variables[var_b] = 1;
		return true;
	}
	else
	{
		std::cout << "unexpected shit" << std::endl;
		exit(6);
	}

	return false;
}