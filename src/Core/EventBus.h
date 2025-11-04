#pragma once
#include <functional>

struct IEvent
{
	virtual ~IEvent() = default;
};

class EventBus
{
public:
	class EventHandle
	{
	public:
		template <typename T> void CreateNewHandle()
		{
			static size_t nextValue = 0;
			id_ = nextValue++;
			typeidHashCode_ = typeid(T).hash_code();
		}

		bool operator==(const EventHandle& other) const
		{
			return id_ == other.id_ && typeidHashCode_ == other.typeidHashCode_;
		}

		size_t GetTypeHashCode() const { return typeidHashCode_; }

	private:
		size_t id_;
		size_t typeidHashCode_;
	};

	template <typename T> using Fn = std::function<void(const T&)>;

	static EventBus& GetInstance()
	{
		static EventBus instance;
		return instance;
	}

	template <typename T> EventHandle Subscribe(Fn<T> eventFn)
	{
		EventHandle handle;
		handle.CreateNewHandle<T>();
		auto function = [eventFn](const IEvent& e) { eventFn(static_cast<const T&>(e)); };
		eventFunctions_[typeid(T).hash_code()].emplace_back(handle, function);
		return handle;
	}

	void Unsubscribe(EventHandle handle)
	{
		auto it = eventFunctions_.find(handle.GetTypeHashCode());
		if (it != eventFunctions_.end())
		{
			std::vector<EventFunction>& handlers = it->second;
			handlers.erase(std::remove_if(handlers.begin(), handlers.end(),
										  [handle](const EventFunction& handler) { return handler.Handle == handle; }),
						   handlers.end());
		}
	}

	void Publish(const IEvent& e)
	{
		auto it = eventFunctions_.find(typeid(e).hash_code());
		if (it != eventFunctions_.end())
		{
			for (EventFunction& eventHandler : it->second)
			{
				eventHandler.Functions(e);
			}
		}
	}

private:
	struct EventFunction
	{
		EventHandle Handle;
		std::function<void(const IEvent&)> Functions;
	};

	EventBus() = default;

private:
	std::unordered_map<size_t, std::vector<EventFunction>> eventFunctions_;
};