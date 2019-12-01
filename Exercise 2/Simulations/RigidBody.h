#pragma once
#include "DrawingUtilitiesClass.h"
using namespace std;

class RigidBody
{
public:
	RigidBody();
	~RigidBody();
	RigidBody(Vec3 position, Vec3 size, Vec3 linear_velocity, Vec3 angularVelocity, Vec3 force, Quat orientation, float mass);
	void clearForces();
	void addForce(Vec3 force);
	void simulateRotation(float timestep);
	void simulatePosition(float timestep);
	Mat4 getWorldMatrix();
	Mat4 getRotationMatrix();
	Mat4 getScaleMatrix();
	Mat4 getTranslationMatrix();
	Mat4 getCurrentInertia();

	Vec3 position;
	vector<Vec3> initPoints;
	vector<Vec3> points;
	Vec3 size;
	Vec3 linearVelocity;
	Vec3 angularVelocity;
	Vec3 force;
	Quat orientation;
	float mass;
private:
	Vec3 angularMomentum;
	Mat4 inertia_0;
	//Mat4 inversInertia;
	void computeI_0();
	void updatePoints();
};

