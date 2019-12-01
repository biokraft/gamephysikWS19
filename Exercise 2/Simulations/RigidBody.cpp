#include "RigidBody.h"

RigidBody::RigidBody()
{
}


RigidBody::~RigidBody()
{
}

RigidBody::RigidBody(Vec3 position, Vec3 size, Vec3 linearVelocity, Vec3 angularVelocity, Vec3 force, Quat orientation, float mass)
{
	//Only Boxes -> Center of Mass always (0,0,0)
	this->position = position;
	this->size = size;
	this->linearVelocity = linearVelocity;
	this->angularVelocity = angularVelocity;
	this->force = force;
	if (orientation.w == 0 && orientation.x == 0 && orientation.y == 0 && orientation.z == 0) {
		orientation.w = 1;
	}
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
	mat.value[0][0] = double((1.0 / 12.0)*mass*(h*h + d * d));
	mat.value[1][1] = double((1.0 / 12.0)*mass*(w*w + d * d));
	mat.value[2][2] = double((1.0 / 12.0)*mass*(w*w + h * h));
	mat.value[3][3] = 1;
	inertia_0 = mat;//TODO inverse?
}

void RigidBody::simulatePosition(float timestep) {
	//TODO copy exercise 1 stuff
}

void RigidBody::simulateRotation(float timestep) {

	//1. calculate forces & convert them to torque q
	Vec3 q = Vec3();
	//gp-lecture03-rigid-bodies-2D.pdf page 24
	//TODO foreach point in rigidbody
	// q += point cross force

	//2.  Integrate the orientation r using the angular velocity w
	Quat w = Quat(angularVelocity.x,angularVelocity.y,angularVelocity.z,0);//TODO check 0 position gp-lecture04-orientation.pdf page 25
	Quat test = w.operator*(orientation);
	orientation = orientation + (timestep / 2) * w * orientation;

	//3.  Integrate angular momentum L
	angularMomentum = angularMomentum + timestep * q;

	//4.  Update (inverse) Inertia Tensor I
	//Todo check dimensions of inverse inertia
	Mat4 rot = getRotationMatrix();
	Mat4 rot_t = getRotationMatrix();
	Mat4 inertia_0_inv = inertia_0.inverse();//TODO why NAN?
	rot_t.transpose();

	Mat4 inversInertia = rot * inertia_0_inv * rot_t;

	//5.  Update angular velocity w using I and L
	angularVelocity = inversInertia * angularMomentum;

	//6.  Update the World Space positions of the Points based on the new orientation r
}


