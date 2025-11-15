#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>



template <typename T>
class ResourceManager
{
public:
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	std::shared_ptr<T> Get(const std::string& name)
	{
		auto it = resources_.find(name);
		if (it != resources_.end())
		{
			return it->second;
		}
		return nullptr;
	}

	template <typename... Args>
	std::shared_ptr<T> Create(const std::string& name, Args... args)
	{
		resources_[name] = std::make_shared<T>(std::forward<Args>(args)...);
		return resources_[name];
	}

	template <typename... Args>
	std::shared_ptr<T> GetOrCreate(const std::string& name, Args&&... args)
	{
		std::shared_ptr<T> resource = Get(name);
		if (resource)
		{
			return resource;
		}

		return Create(name, std::forward<Args>(args)...);
	}

private:
	std::unordered_map<std::string, std::shared_ptr<T>> resources_;
};
