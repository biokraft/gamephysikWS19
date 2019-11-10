#include "Spring.h"


Spring::Spring()
{
}


Spring::~Spring()
{
}

Spring::Spring(Point *point1, Point *point2, float* stiffness, float initialLength)
{
	this->point1 = point1;
	this->point2 = point2;
	this->stiffness = stiffness;
	this->initialLength = initialLength;
}

void Spring::computeElasticForces() {
	//Get PointPositions from MassSpringSystem
	Vec3 p1 = point1->position;
	Vec3 p2 = point2->position;

	//Calculate distance
	Vec3 diff = p1 - p2;
	float distance = sqrtf(dot(diff, diff));
	Vec3 normalizedDirection = diff / distance;


	//Calculate Force (Hooks Law) 
	//F = -stiffness × (||P1 - P2|| - rest_length)
	float f = (-(*stiffness) * (distance - initialLength));
	p1Force = f * normalizedDirection;
	p2Force = f * (-normalizedDirection);
}

void Spring::computeElasticMidpointForces() {
	//Get PointPositions from MassSpringSystem
	Vec3 p1 = point1->midPos;
	Vec3 p2 = point2->midPos;

	//Calculate distance
	Vec3 diff = p1 - p2;
	float distance = sqrtf(dot(diff, diff));
	Vec3 normalizedDirection = diff / distance;


	//Calculate Force (Hooks Law) 
	//F = -stiffness × (||P1 - P2|| - rest_length)
	float f = (-(*stiffness) * (distance - initialLength));
	p1Force = f * normalizedDirection;
	p2Force = f * (-normalizedDirection);
}

void Spring::addForcesToEndpoints() 
{
	point1->addForce(p1Force);
	point2->addForce(p2Force);
}

