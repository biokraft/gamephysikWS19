#include "RigidBodySystemSimulator.h"

RigidBodySystemSimulator::RigidBodySystemSimulator()
{
	//Test
	addRigidBody(Vec3(0,0,0),Vec3(1,1,1),1);
}

const char * RigidBodySystemSimulator::getTestCasesStr()
{
	return "Demo1,Demo2,Demo3,Demo4";
}

void RigidBodySystemSimulator::initUI(DrawingUtilitiesClass * DUC)
{
	this->DUC = DUC;
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
	for (int i = 0; i < getNumberOfRigidBodies(); i++)
	{
		DUC->setUpLighting(Vec3(), 0.4*Vec3(1, 1, 1), 100, Vec3(0.5, 0.5, 0.5));
		DUC->drawRigidBody(rigidbodies.at(i).getWorldMatrix());
		//DUC->drawSphere(getPositionOfMassPoint(i), Vec3(0.05f, 0.05f, 0.05f));
	}
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
	applyForceOnBody(0,Vec3(0.3, 0.5, 0.25),Vec3(1, 1, 0));
	for (int i = 0; i < getNumberOfRigidBodies(); i++) {
		//rigidbodies.at(i).addForce(Vec3(0.5f,0.5f,0.2f));
		rigidbodies.at(i).simulateRotation(timeStep);
		rigidbodies.at(i).simulatePosition(timeStep);
		rigidbodies.at(i).clearForces();
	}
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
	//body.addForce(force + cross(force, loc - body.position));
	body.addAngularForce(cross(force, loc - body.position));
	body.addLinearForce(force);
}

void RigidBodySystemSimulator::addRigidBody(Vec3 position, Vec3 size, int mass)
{
	//Vec3 eulerTest = Vec3(0.15,0.15,0);
	rigidbodies.push_back(RigidBody(position, size, Quat(), mass));
}

void RigidBodySystemSimulator::setOrientationOf(int i, Quat orientation)
{
	rigidbodies.at(i).orientation = orientation;
}

void RigidBodySystemSimulator::setVelocityOf(int i, Vec3 velocity)
{
	rigidbodies.at(i).linearVelocity = velocity;
}
