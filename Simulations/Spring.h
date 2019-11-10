#pragma once
#include "Point.h"
//#include "MassSpringSystemSimulator.h"

class MassSpringSystemSimulator;
class Spring
{
public:
	Spring();
	~Spring();
	Spring(Point *point1, Point *point2, float* stiffness, float initialLength);

	void computeElasticForces();
	void computeElasticMidpointForces();
	void addForcesToEndpoints();

	Point *point1;
	Point *point2;
	Vec3 p1Force;
	Vec3 p2Force;
	float* stiffness;
	float initialLength;

	// float currentLength;
};

