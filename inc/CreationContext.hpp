#pragma once

#include <unordered_map>
#include <string>

struct CreationContext
{
	friend class FlagsHandler;

	bool is_flag_exists(std::string const& flag) const noexcept;

	std::string get_flag_value(std::string const& flag) const noexcept;
private:
	std::unordered_map<std::string, std::string> _flag_value;
};
