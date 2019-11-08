#include "Spring.h"



Spring::Spring()
{
}


Spring::~Spring()
{
}

Spring::Spring(int point1, int point2, float stiffness, float initialLength)
{
	this->point1 = point1;
	this->point2 = point2;
	this->stiffness = stiffness;
	this->initialLength = initialLength;
}
