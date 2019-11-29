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
	computeI_0();
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

Mat4 RigidBody::getScaleMatrix() {
	Mat4 mat;
	mat.initScaling(size.x,size.y,size.z);
	return mat;
}

Mat4 RigidBody::getRotationMatrix() {
	return orientation.getRotMat();
}

Mat4 RigidBody::getTranslationMatrix() {
	Mat4 mat;
	mat.initTranslation(position.x,position.y,position.z);
	return mat;
}

Mat4 RigidBody::getCurrentInertia() 
{
	return getRotationMatrix() * inertia_0 * getRotationMatrix().inverse();
}

void RigidBody::computeI_0() {
	Mat4 mat = Mat4();
	//https://en.wikipedia.org/wiki/List_of_moments_of_inertia
	float h = size.y;
	float d = size.z;
	float w = size.x;
	mat.value[0][0] = (1.0 / 12.0)*mass*(h*h + d * d);
	mat.value[1][1] = (1.0 / 12.0)*mass*(w*w + d * d);
	mat.value[2][2] = (1.0 / 12.0)*mass*(w*w + h * h);
	inertia_0 = mat;
}


