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
	velocity = velocity + force * timestep; // is force acceleration in this case?
}

void Point::calcMidpoint(float timestep)
{
	// TODO implement
	// [Pos of Midstep] = oldPos + ½ × timestep × oldVel
	// [Vel at Midstep] = oldVel  + ½ × timestep × [Acc at oldPos]
	// newPos = oldPos + timestep × [Vel at Midstep]
	// newVel = oldVel  + timestep × [Acc at Midstep]
}
