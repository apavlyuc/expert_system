#pragma once

#include "Storage.hpp"

#include <map>
#include <set>

class Solver
{
public:
	Solver(bool need_log = false)
		: _need_log(need_log)
	{}

	void	solve_unknown_variables(Storage storage);

	inline void turn_on_log() noexcept { _need_log = true; }
	inline void turn_off_log() noexcept { _need_log = false; }

	inline std::map<char, int> const& get_result() const { return _solved_var; };
private:
	bool	_process_equation(Storage& storage, Equation& equation, bool recalculation = false);
	bool	_change_variables(Storage& storage, std::string const& right_part);

	std::map<char, int> _solved_var;

	bool _need_log;
};
