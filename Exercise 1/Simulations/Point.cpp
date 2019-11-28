#include "Point.h"



Point::Point()
{
}


Point::~Point()
{
}

Point::Point(Vec3 position, Vec3 velocity, Vec3 force, float* mass, float* damping, bool isFixed) // evtl mit pointern...
{
	this->position = position;
	this->velocity = velocity;
	this->force = force;
	this->mass = mass;
	this->damping = damping;
	this->isFixed = isFixed;
}

void Point::calcEulerPos(float timestep, bool collisionDetection)
{
	if (isFixed)
	{
		return;
	}
	position = position + velocity * timestep;
	if (collisionDetection && position.y < -0.95f)  // collision detection
	{
		position.y = -0.95f;
		velocity /= 1.01f;
		velocity.y = 0;
	}
	velocity = velocity + getAcceleration() * timestep;
}

void Point::updateMidVals(float timestep)
{
	midPos = position + 0.5f * timestep * velocity;
	midVel = velocity + 0.5f * timestep * getAcceleration();
}

void Point::calcMidpoint(float timestep, bool collisionDetection)
{
	if (isFixed)
	{
		return;
	}
	position = position + timestep * midVel;
	if (collisionDetection && position.y < -0.95f)  // collision detection
	{
		position.y = -0.95f;
		velocity /= 1.01f;
		velocity.y = 0;
	}
	velocity = velocity + timestep * getAcceleration();
}

Vec3 Point::getAcceleration() 
{
	return force / (*mass);
}

void Point::clearForces() 
{
	force = Vec3(0,0,0);
}

void Point::addForce(Vec3 additionalForce) 
{
	force += additionalForce;
}
