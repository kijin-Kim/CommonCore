#pragma once
#include <filesystem>
#include <string>
#include <unordered_map>

class Texture
{
public:
	Texture(const std::string& name, unsigned int textureID)
		: name_(name)
		, textureID_(textureID)

	{
	}
	virtual ~Texture();
	void Resize(int width, int height);
	unsigned int GetID() const { return textureID_; }
	const std::string& GetName() const { return name_; }


	int GetWidth() const { return width_; }
	int GetHeight() const { return height_; }


protected:
	unsigned int textureID_;
	std::string name_;
	int width_;
	int height_;
};

class ImageTexture : public Texture
{
public:
	ImageTexture(const std::filesystem::path& path);
};

class RenderTexture : public Texture
{
public:
	RenderTexture(const std::string& name, int width, int height);
};

class TextureManager
{
public:
	static TextureManager& GetInstance()
	{
		static TextureManager instance;
		return instance;
	}

	template <typename T> std::shared_ptr<T> Get(const std::string& name)
	{
		auto it = textures_.find(name);
		if (it != textures_.end())
		{
			return static_pointer_cast<T>(it->second);
		}
		return nullptr;
	}

	std::shared_ptr<ImageTexture> LoadTextureFromFile(const std::filesystem::path& path)
	{
		std::shared_ptr<ImageTexture> texture = TextureManager::GetInstance().Get<ImageTexture>(path.string());
		if (texture)
		{
			return texture;
		}

		texture = std::make_shared<ImageTexture>(path);
		textures_[path.string()] = texture;
		return texture;
	}

	std::shared_ptr<RenderTexture> CreateRenderTexture(const std::string& name, int width, int height)
	{
		std::shared_ptr<RenderTexture> texture = TextureManager::GetInstance().Get<RenderTexture>(name);
		if (texture)
		{
			return texture;
		}

		texture = std::make_shared<RenderTexture>(name, width, height);
		textures_[name] = texture;
		return std::static_pointer_cast<RenderTexture>(texture);
	}

private:
	std::unordered_map<std::string, std::shared_ptr<Texture>> textures_;
};
