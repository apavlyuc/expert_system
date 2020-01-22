#include "SolverContextProvider.h"

SolverContextProvider::SolverContextProvider(std::string const& file_name)
{
	_ifs = std::ifstream(file_name, std::ifstream::in);
}

std::unique_ptr<SolverContext> SolverContextProvider::get_solver_context()
{
	return std::make_unique<SolverContext>();
}
