#include "Primitive.h"

IPrimitive::IPrimitive(const glm::vec4& color, DrawMode drawMode)
	: color_(color)
	, drawMode_(drawMode)
{
}