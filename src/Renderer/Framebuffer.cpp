#include "Framebuffer.h"
#include <glad/glad.h>

Framebuffer::Framebuffer(int width, int height)
	: fboId_(0)
	, colorAttachmentId_(0)
	, rboId_(0)
	, width_(width)
	, height_(height)
{
	glGenFramebuffers(1, &fboId_);
	glBindFramebuffer(GL_FRAMEBUFFER, fboId_);

	glGenTextures(1, &colorAttachmentId_);
	glBindTexture(GL_TEXTURE_2D, colorAttachmentId_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachmentId_, 0);

	glGenRenderbuffers(1, &rboId_);
	glBindRenderbuffer(GL_RENDERBUFFER, rboId_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboId_);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &fboId_);
	glDeleteTextures(1, &colorAttachmentId_);
	glDeleteRenderbuffers(1, &rboId_);
}
void Framebuffer::Resize(int width, int height)
{
	if (width_ == width && height_ == height)
	{
		return;
	}

	width_ = width;
	height_ = height;

	glBindTexture(GL_TEXTURE_2D, colorAttachmentId_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	glBindRenderbuffer(GL_RENDERBUFFER, rboId_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width_, height_);
}
