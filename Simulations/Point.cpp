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

void Point::updateTempPos(float timestep)
{
	tempPos = position + (timestep / 2) * velocity;
}

void Point::calcMidpoint(float timestep)
{
	// TODO implement
	// [Pos of Midstep] = oldPos + ½ × timestep × oldVel
	// [Vel at Midstep] = oldVel  + ½ × timestep × [Acc at oldPos]
	// newPos = oldPos + timestep × [Vel at Midstep]
	// newVel = oldVel  + timestep × [Acc at Midstep]
	//Vec3 midPos = position + 0.5f * timestep * velocity;
	//Vec3 midVel = velocity + 0.5f * timestep * getAcceleration();
	//position = position + timestep * midVel;
	//velocity = velocity + timestep

	//–We have v(t), x(t)
	//–Compute xtmp at t + h / 2 based on v(t)
	//–Compute a(t) (i.e., evaluate elastic forces)
	//–Compute vtmp at t + h / 2 based on a(t)
	//–Compute x at t + h
	//–Compute a at t + h / 2 based on xtmp and vtmp(elastic forces again!)
	//–Compute v at t + h
	Vec3 tempVel = velocity + (timestep / 2) * getAcceleration();
	position = position + timestep * tempVel;
	// TODO compute a at t + h / 2 based on xtmp and vtmp(elastic forces again!)
	// maybe compute a(t) (3rd comment line) in updateTempPos() as well to differentiate from Euler
	velocity = velocity + timestep;
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
