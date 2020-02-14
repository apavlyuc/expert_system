#include "CreationContext.hpp"

bool CreationContext::is_flag_exists(std::string const& flag) const noexcept
{
	return (_flag_value.count(flag) != 0);
}

std::string CreationContext::get_flag_value(std::string const& flag) const noexcept
{
	if (is_flag_exists(flag))
	{
		return _flag_value.at(flag);
	}
	return "";
}
