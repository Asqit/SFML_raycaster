#include "preCompiled.hpp"


namespace Andy_T {
	float distance_int_2D(float x1,float y1,float x2,float y2)
	{
		float xDis = x1 - x2;
		float yDis = y1 - y2;
		return std::sqrt(std::pow(xDis, 2) + std::pow(yDis, 2));
	}
}