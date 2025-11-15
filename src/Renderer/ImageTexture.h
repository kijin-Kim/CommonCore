#pragma once
#include <filesystem>

class ImageTexture
{
public:
	ImageTexture(const std::filesystem::path& imagePath);
	ImageTexture& operator=(const ImageTexture&) = delete;
	ImageTexture(const ImageTexture&) = delete;
	~ImageTexture();
	void Resize(int width, int height);

	unsigned int GetID() const { return textureID_; }
	int GetWidth() const { return width_; }
	int GetHeight() const { return height_; }

protected:
	unsigned int textureID_;
	int width_;
	int height_;
};
