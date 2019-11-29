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

Mat4 RigidBody::getWorldMatrix()
{
	Mat4 worldMatrix = getScaleMatrix() * getRotationMatrix() * getTranslationMatrix();
	return worldMatrix;
}

Mat4  RigidBody::getScaleMatrix() {
	Mat4 mat;
	mat.initScaling(size.x,size.y,size.z);
	return mat;
}

Mat4  RigidBody::getRotationMatrix() {
	return orientation.getRotMat();
}

Mat4  RigidBody::getTranslationMatrix() {
	Mat4 mat;
	mat.initTranslation(position.x,position.y,position.z);
	return mat;
}
