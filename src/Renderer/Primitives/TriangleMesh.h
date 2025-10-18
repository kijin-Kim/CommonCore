#pragma once
#include "Primitive.h"

class TriangleMesh : public IPrimitive
{
public:
	TriangleMesh() = default;
	virtual ~TriangleMesh();
	virtual void UploadData() override;
	virtual void Bind() const override;
	virtual void Draw() const override;
	virtual void Unbind() const override;
};
