#pragma once
#include "Primitive.h"


class RectangleMesh : public IPrimitive
{
public:
	explicit RectangleMesh( const glm::vec4& color, DrawMode drawMode);
	virtual ~RectangleMesh();
	virtual void UploadData() override;
	virtual void Bind() const override;
	virtual void Draw() const override;
	virtual void Unbind() const override;
};