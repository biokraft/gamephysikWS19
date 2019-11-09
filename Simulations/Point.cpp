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
	velocity = velocity + getAcceleration() * timestep; // is force acceleration in this case?
	this->clearForces();
}

void Point::calcMidpoint(float timestep)
{
	// TODO implement
	// [Pos of Midstep] = oldPos + ½ × timestep × oldVel
	// [Vel at Midstep] = oldVel  + ½ × timestep × [Acc at oldPos]
	// newPos = oldPos + timestep × [Vel at Midstep]
	// newVel = oldVel  + timestep × [Acc at Midstep]
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
