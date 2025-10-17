#pragma once
#include "Primitive.h"

class TriangleMesh : public IPrimitive
{
public:
	TriangleMesh();
	virtual ~TriangleMesh();
	virtual void Bind() const override;
	virtual void Draw() const override;
	virtual void Unbind() const override;
};
