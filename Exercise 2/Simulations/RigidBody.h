#pragma once
#include "DrawingUtilitiesClass.h"

using namespace std;

class RigidBody
{
public:
	RigidBody();
	~RigidBody();
	RigidBody(Vec3 position, Vec3 size, Quat orientation, float mass);
	struct Force{
		Vec3 f;
		Vec3 p;
	};
	void clearForces();
	void addLinearForce(Vec3 force);
	void addAngularForce(Vec3 force);
	void addForce(RigidBody::Force force);
	void simulateRotation(float timestep);
	void simulatePosition(float timestep);
	Mat4 getWorldMatrix();
	Mat4 getRotationMatrix();
	Mat4 getScaleMatrix();
	Mat4 getTranslationMatrix();
	Mat4 getCurrentInertia();

	Vec3 position;
	vector<Force> forces;
	Vec3 size;
	Vec3 linearVelocity;
	Vec3 angularVelocity;
	Vec3 linearForce;
	Vec3 angularForce;
	Vec3 angularMomentum;
	Quat orientation;
	Mat4 inversInertia;
	float mass;
	float bounciness;
private:
	Mat4 inertia_0;
	//Mat4 inversInertia;
	void computeI_0();
	Vec3 getAcceleration();
};

