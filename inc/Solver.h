#pragma once

#include "SolverContext.h"

#include <memory>

class Solver
{
public:
	Solver(std::unique_ptr<SolverContext> context) { _context = std::move(context); }

	void solve();
	void get_meaning_for(char fact);

	void print_answer();
private:
	std::unique_ptr<SolverContext> _context;
};
