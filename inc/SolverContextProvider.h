#pragma once

#include "SolverContext.h"

#include <string>
#include <fstream>
#include <memory>

class SolverContextProvider
{
public:
	SolverContextProvider(std::string const& file_name);
	~SolverContextProvider() { _ifs.close(); }

	std::unique_ptr<SolverContext> get_solver_context();
private:
	std::ifstream _ifs;
};
