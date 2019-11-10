#pragma once
#include "Simulator.h"
class Point
{
public:
	Point();
	~Point();
	Point(Vec3 position, Vec3 velocity, Vec3 force, float* mass, float* damping, bool isFixed);

	void clearForces();
	void addForce(Vec3 force);
	void calcEulerPos(float timestep, bool collisionDetection);
	void updateMidVals(float timestep);
	void calcMidpoint(float timestep, bool collisionDetection);
	Vec3 getAcceleration();

	Vec3 position;
	Vec3 midPos;
	Vec3 velocity;
	Vec3 midVel;
	Vec3 force;
	float* mass;
	float* damping;
	bool isFixed;
};

