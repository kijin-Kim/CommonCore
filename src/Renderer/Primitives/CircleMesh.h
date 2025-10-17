#pragma once
#include "Primitive.h"

class CircleMesh : public IPrimitive
{
public:
	CircleMesh(int segments = 36);
	virtual ~CircleMesh();
	virtual void Bind() const override;
	virtual void Draw() const override;
	virtual void Unbind() const override;

private:
	int segmentCount_;
};
