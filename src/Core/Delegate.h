#pragma once
#include <functional>

template <typename... Args>
class Delegate
{
public:
	using Fn = std::function<void(Args...)>;
	Delegate() = default;
	Delegate(const Delegate&) = delete;
	Delegate& operator=(const Delegate&) = delete;

	void Bind(Fn function) { function_ = function; }

	void Execute(Args... args)
	{
		if (function_)
		{
			function_(args...);
		}
	}

private:
	Fn function_;
};
