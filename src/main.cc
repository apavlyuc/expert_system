#include "Solver.h"
#include "SolverContextProvider.h"

#include <iostream>

namespace {
	void print_usage()
	{

	}
}//namespace

int main(int ac, char **av)
{
	if (ac != 2)
	{
		print_usage();
		return 0;
	}

	std::unique_ptr<SolverContext> solver_context = SolverContextProvider(av[1]).get_solver_context();
	Solver solver{std::move(solver_context)};

	solver.solve();
	solver.print_answer();

	return 0;
}
