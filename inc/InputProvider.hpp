#pragma once

#include "CreationContext.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

class InputProvider
{
public:
	virtual bool read_next_input(std::string& dst, char delimeter = '\n') const = 0;

	virtual std::shared_ptr<CreationContext> const& get_creation_context() const = 0;
};

class ConsoleInputProvider : public InputProvider
{
public:
	friend std::unique_ptr<InputProvider> create_InputProvider(std::shared_ptr<CreationContext> context);

	virtual bool read_next_input(std::string& dst, char delimeter) const override;
	
	virtual inline std::shared_ptr<CreationContext> const& get_creation_context() const override { return _context; }
private:
	ConsoleInputProvider(std::shared_ptr<CreationContext> context, std::string const& end_indicator = "end")
		: _context(context), _end_indicator(end_indicator)
	{
		std::cout << "For end of input and start processing print: [" << end_indicator << ']' << std::endl;
	}
	
	std::shared_ptr<CreationContext> _context;
	const std::string _end_indicator;
};

class FileInputProvider : public InputProvider
{
public:
	friend std::unique_ptr<InputProvider> create_InputProvider(std::shared_ptr<CreationContext> context);

	virtual bool read_next_input(std::string& dst, char delimeter) const override;

	virtual inline std::shared_ptr<CreationContext> const& get_creation_context() const override { return _context; }
private:
	FileInputProvider(std::shared_ptr<CreationContext> context, std::string const& file_name)
		: _context(context), ifs(file_name)
	{}

	std::shared_ptr<CreationContext> _context;
	mutable std::ifstream ifs;
};

std::unique_ptr<InputProvider> create_InputProvider(std::shared_ptr<CreationContext> context);
