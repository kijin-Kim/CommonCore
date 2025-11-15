#include "ImageTexture.h"

#include "stb_image/stb_image.h"
#include <glad/glad.h>
#include <iostream>

ImageTexture::ImageTexture(const std::filesystem::path& imagePath)
	: textureID_(0)
	, width_(0)
	, height_(0)
{
	glGenTextures(1, &textureID_);
	glBindTexture(GL_TEXTURE_2D, textureID_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int channels;
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(imagePath.string().c_str(), &width_, &height_, &channels, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "[ImageTexture Error] Failed to load image: " << imagePath << std::endl;
	}
	stbi_image_free(data);
}

ImageTexture::~ImageTexture()
{
	glDeleteTextures(1, &textureID_);
}
void ImageTexture::Resize(int width, int height)
{
	if (width_ == width && height_ == height)
	{
		return;
	}

	width_ = width;
	height_ = height;
	glBindTexture(GL_TEXTURE_2D, textureID_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
}
