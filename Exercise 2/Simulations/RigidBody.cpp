#include "RigidBody.h"

RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

RigidBody::RigidBody(Vec3 position, Vec3 size, Vec3 linearVelocity, Vec3 angularVelocity, Vec3 force, Quat orientation, float mass)
{
	this->position = position;
	this->size = size;
	this->linearVelocity = linearVelocity;
	this->angularVelocity = angularVelocity;
	this->force = force;
	this->orientation = orientation;
	this->mass = mass;
}

void RigidBody::clearForces()
{
	force = Vec3(0, 0, 0);
}

void RigidBody::addForce(Vec3 additionalForce)
{
	force += additionalForce;
}
