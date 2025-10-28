#pragma once
#include <functional>

struct IEvent
{
	virtual ~IEvent() = default;
};

class EventBus
{
public:
	template <typename T>
	using EventFn = std::function<void(const T&)>;

	template <typename T>
	void Subscribe(EventFn<T> eventFn)
	{
		eventFunctions_[typeid(T).hash_code()].push_back([eventFn](const IEvent& e)
		{
			eventFn(static_cast<const T&>(e));
		});
	}

	void Publish(const IEvent& e)
	{
		auto it = eventFunctions_.find(typeid(e).hash_code());
		if (it != eventFunctions_.end())
		{
			for (std::function<void(const IEvent&)>& eventFn : it->second)
			{
				eventFn(e);
			}
		}
	}

private:
	std::unordered_map<size_t, std::vector<std::function<void(const IEvent&)> > > eventFunctions_;
};