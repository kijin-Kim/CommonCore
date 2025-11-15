#pragma once

class Framebuffer
{
public:
	Framebuffer(int width, int height);
	~Framebuffer();
	Framebuffer(const Framebuffer&) = delete;
	Framebuffer& operator=(const Framebuffer&) = delete;
	void Resize(int width, int height);

	unsigned int GetFboId() const { return fboId_; }
	unsigned int GetColorAttachmentId() const { return colorAttachmentId_; }
	int GetWidth() const { return width_; }
	int GetHeight() const { return height_; }

private:
	unsigned int fboId_;
	unsigned int colorAttachmentId_;
	unsigned int rboId_;

	int width_;
	int height_;
};
