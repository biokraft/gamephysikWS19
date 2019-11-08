#pragma once
#include "Simulator.h"
class Point
{
public:
	Point();
	~Point();
	Point(Vec3 position, Vec3 velocity, Vec3 force, float mass, float damping);

	void calcEulerPos(float timestep);
	void calcMidpoint(float timestep);

	Vec3 position;
	Vec3 velocity;
	Vec3 force;
	float mass;
	float damping;
};

