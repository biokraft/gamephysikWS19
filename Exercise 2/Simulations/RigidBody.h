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
	Mat4 getWorldMatrix();
	Mat4 getRotationMatrix();
	Mat4 getScaleMatrix();
	Mat4 getTranslationMatrix();

	Vec3 position;
	Vec3 size;
	Vec3 linearVelocity;
	Vec3 angularVelocity;
	Vec3 force;
	Quat orientation;
	float mass;
};

