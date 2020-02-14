#pragma once

#include "Storage.hpp"
#include "InputProvider.hpp"

#include <string>
#include <vector>

class Parser {
	bool _need_log;

	bool _rules{false};
	bool _end_of_rules{false};
	bool _facts{false};

	int  reverse_polish_entry(std::string const& str, std::vector<char>& out);
	void parser(std::string const& rule);
	void lexer(std::string const& rule);
	void check_right(std::string const& str);
	void check_left(std::string const& str);

	std::unique_ptr<InputProvider> _input_provider;
	std::unique_ptr<Storage> _storage;
public:
	Parser() = default;
	Parser(std::unique_ptr<InputProvider> input_provider)
		: _input_provider(std::move(input_provider))
	{
		_need_log = _input_provider->get_creation_context()->is_flag_exists("-v");
	}

	void process();

	inline void turn_on_log() noexcept { _need_log = true; }
	inline void turn_off_log() noexcept { _need_log = false; }

	inline std::unique_ptr<Storage> get_storage() { return std::move(_storage); }
};
