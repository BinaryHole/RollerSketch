#include "DrawPoint.h"

DrawPoint::DrawPoint() {
	this->x			= 0;
	this->y			= 0;
	this->radius = 0;
}

DrawPoint::DrawPoint(float x, float y, float radius) {
	this->x			= x;
	this->y			= y;
	this->radius	= radius;
}