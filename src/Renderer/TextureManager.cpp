#include "TextureManager.h"

#include <glad/glad.h>
#include <iostream>
#include <stb_image/stb_image.h>

Texture::~Texture()
{
	glDeleteTextures(1, &textureID_);
}
void Texture::Resize(int width, int height)
{
	width_ = width;
	height_ = height;
	glBindTexture(GL_TEXTURE_2D, textureID_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

}

ImageTexture::ImageTexture(const std::filesystem::path& path)
	: Texture(path.string(), 0)
{
	int channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.string().c_str(), &width_, &height_, &channels, 0);
	if (!data)
	{
		std::cerr << "Failed to load texture: " << path.string() << std::endl;
		return;
	}
	glGenTextures(1, &textureID_);
	glBindTexture(GL_TEXTURE_2D, textureID_);

	GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, width_, height_, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);
}

RenderTexture::RenderTexture(const std::string& name, int width, int height)
	: Texture(name, 0)

{
	width_ = width;
	height_ = height;
	glGenTextures(1, &textureID_);
	glBindTexture(GL_TEXTURE_2D, textureID_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
