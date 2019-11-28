#include "RigidBodySystemSimulator.h"

RigidBodySystemSimulator::RigidBodySystemSimulator()
{
}

const char * RigidBodySystemSimulator::getTestCasesStr()
{
	return "Demo1,Demo2,Demo3,Demo4";
}

void RigidBodySystemSimulator::initUI(DrawingUtilitiesClass * DUC)
{
	// TODO implement
}

void RigidBodySystemSimulator::reset()
{
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void RigidBodySystemSimulator::drawFrame(ID3D11DeviceContext * pd3dImmediateContext)
{
	// TODO implement
}

void RigidBodySystemSimulator::notifyCaseChanged(int testCase)
{
	// TODO implement
}

void RigidBodySystemSimulator::externalForcesCalculations(float timeElapsed)
{
	// TODO implement
}

void RigidBodySystemSimulator::simulateTimestep(float timeStep)
{
	// TODO implement
}

void RigidBodySystemSimulator::onClick(int x, int y)
{
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

void RigidBodySystemSimulator::onMouse(int x, int y)
{
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

int RigidBodySystemSimulator::getNumberOfRigidBodies()
{
	return rigidbodies.size();
}

Vec3 RigidBodySystemSimulator::getPositionOfRigidBody(int i)
{
	return rigidbodies.at(i).position;
}

Vec3 RigidBodySystemSimulator::getLinearVelocityOfRigidBody(int i)
{
	return rigidbodies.at(i).linearVelocity;
}

Vec3 RigidBodySystemSimulator::getAngularVelocityOfRigidBody(int i)
{
	return rigidbodies.at(i).angularVelocity;
}

void RigidBodySystemSimulator::applyForceOnBody(int i, Vec3 loc, Vec3 force)
{
	RigidBody& body = rigidbodies.at(i);
	body.addForce(force + cross(force, loc - body.position));
}

void RigidBodySystemSimulator::addRigidBody(Vec3 position, Vec3 size, int mass)
{
	rigidbodies.push_back(RigidBody(position, size, Vec3(), Vec3(), Vec3(), Quat(), mass));
}

void RigidBodySystemSimulator::setOrientationOf(int i, Quat orientation)
{
	rigidbodies.at(i).orientation = orientation;
}

void RigidBodySystemSimulator::setVelocityOf(int i, Vec3 velocity)
{
	rigidbodies.at(i).linearVelocity = velocity;
}
