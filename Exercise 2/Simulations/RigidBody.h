#pragma once
#include "DrawingUtilitiesClass.h"

class RigidBody
{
public:
	RigidBody();
	~RigidBody();
	RigidBody(Vec3 position, Vec3 size, Vec3 linear_velocity, Vec3 angularVelocity, Vec3 force, Quat orientation, float mass);
	void clearForces();
	void addForce(Vec3 force);

	Vec3 position;
	Vec3 size;
	Vec3 linearVelocity;
	Vec3 angularVelocity;
	Vec3 force;
	Quat orientation;
	float mass;
};

