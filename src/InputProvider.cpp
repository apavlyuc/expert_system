#include "InputProvider.hpp"

#include <iostream>

std::unique_ptr<InputProvider> create_InputProvider(std::shared_ptr<CreationContext> context)
{
	static const std::string file_flag{"-f"};

	if (context->is_flag_exists(file_flag))
	{
		return std::unique_ptr<FileInputProvider>(new FileInputProvider(context, context->get_flag_value(file_flag)));
	}
	else
	{
		return std::unique_ptr<ConsoleInputProvider>(new ConsoleInputProvider(context));
	}
}

bool ConsoleInputProvider::read_next_input(std::string& dst, char delimeter = '\n') const
{
	if (std::getline(std::cin, dst, delimeter))
	{
		return (dst != _end_indicator);
	}
	return false;
}

bool FileInputProvider::read_next_input(std::string& dst, char delimeter = '\n') const
{
	if (std::getline(ifs, dst, delimeter))
	{
		return true;
	}
	return false;
}

