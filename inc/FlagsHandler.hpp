#pragma once

#include "CreationContext.hpp"

#include <memory>

class FlagsHandler
{
public:
	inline void turn_on_log() noexcept { _need_log = true; }
	inline void turn_off_log() noexcept { _need_log = false; }

	std::shared_ptr<CreationContext> create_CreationContext(int ac, char **av) const noexcept;
private:
	bool _need_log{false};
};
