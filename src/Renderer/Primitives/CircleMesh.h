#pragma once
#include "Primitive.h"

class CircleMesh : public IPrimitive
{
public:
	explicit CircleMesh(const glm::vec4& color);
	virtual ~CircleMesh();
	virtual void UploadData() override;
	virtual void Bind() const override;
	virtual void Draw() const override;
	virtual void Unbind() const override;

};