#include "FlagsHandler.hpp"
#include "InputProvider.hpp"
#include "Parser.hpp"
#include "Storage.hpp"
#include "Solver.hpp"

#include <iostream>
#include <algorithm>

void print_result(Solver const& solver)
{
	std::cout << std::endl << "Result:" << std::endl;

	auto const& result = solver.get_result();
	for (auto const& var_val : result)
	{
		std::cout << var_val.first << " = ";
		std::cout << (var_val.second == 1 ? "true" : "false");
		std::cout << std::endl;		
	}
}

int main(int ac, char **av)
{
	FlagsHandler handler;
	std::shared_ptr<CreationContext> context = handler.create_CreationContext(ac, av);

	try {
		Parser parser{create_InputProvider(context)};

		parser.process();

		std::unique_ptr<Storage> data = parser.get_storage();

		if (context->is_flag_exists("-v"))
		{
			print_storage(*data);
		}

		Solver solver{context->is_flag_exists("-vv")};

		solver.solve_unknown_variables(*data);

		print_result(solver);
	} catch (std::exception const& e)
	{
		std::cout << "\033[1;31mException: " << e.what() << "\033[0m" << std::endl;
	}
	return 0;
}