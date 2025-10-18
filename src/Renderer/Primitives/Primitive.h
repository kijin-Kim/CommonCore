#pragma once


class IPrimitive
{
public:
	virtual ~IPrimitive() = default;
	virtual void UploadData() = 0;
	virtual void Bind() const = 0;
	virtual void Draw() const = 0;
	virtual void Unbind() const = 0;

protected:
	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;
};