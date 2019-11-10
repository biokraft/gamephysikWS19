#include "Point.h"



Point::Point()
{
}


Point::~Point()
{
}

Point::Point(Vec3 position, Vec3 velocity, Vec3 force, float mass, float damping) // evtl mit pointern...
{
	this->position = position;
	this->velocity = velocity;
	this->force = force;
	this->mass = mass;
	this->damping = damping;
}

void Point::calcEulerPos(float timestep)
{
	position = position + velocity * timestep;
	velocity = velocity + getAcceleration() * timestep;
}

void Point::updateMidVals(float timestep)
{
	midPos = position + 0.5f * timestep * velocity;
	midVel = velocity + 0.5f * timestep * getAcceleration();
}

void Point::calcMidpoint(float timestep)
{
	position = position + timestep * midVel;
	velocity = velocity + timestep * getAcceleration();
}

Vec3 Point::getAcceleration() 
{
	return force / mass;
}

void Point::clearForces() 
{
	force = Vec3(0,0,0);
}

void Point::addForce(Vec3 additionalForce) 
{
	force += additionalForce;
}
