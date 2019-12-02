#include "RigidBodySystemSimulator.h"

RigidBodySystemSimulator::RigidBodySystemSimulator()
{
	m_iTestCase = TESTCASEUSEDTORUNTEST;
	addRigidBody(Vec3(-0.1f, -0.2f, 0.1f), Vec3(0.4f, 0.2f, 0.2f), 100.0f);

	addRigidBody(Vec3(0.0f, 0.2f, 0.0f), Vec3(0.4f, 0.2f, 0.2f), 100.0);
	setOrientationOf(1, Quat(Vec3(0.0f, 0.0f, 1.0f), (float)(M_PI)*0.25f));
	setVelocityOf(1, Vec3(0.0f, -0.1f, 0.05f));
	applyForceOnBody(0, Vec3(0.0, 0.0f, 0.0), Vec3(0, 0, 200));
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
	// applyForceOnBody(0,Vec3(0.3, 0.5, 0.25),Vec3(1, 1, 0));
	for (int i = 0; i < getNumberOfRigidBodies(); i++) {
		// rigidbodies.at(i).addForce(Vec3(0.5f,0.5f,0.2f));
		RigidBody *a = &rigidbodies.at(i);
		a->simulateRotation(timeStep);
		a->simulatePosition(timeStep);
		a->clearForces();
		for (int j = 0; j < getNumberOfRigidBodies(); j++) {
			if (j == i)continue;
			RigidBody *b = &rigidbodies.at(j);
			CollisionInfo info = checkCollisionSAT(a->getWorldMatrix(), b->getWorldMatrix());
			if (info.isValid) {
				//v_i = v_cm + w X x_i
				Vec3 v1 = a->linearVelocity + cross(a->angularVelocity, info.collisionPointWorld);
				Vec3 v2 = b->linearVelocity + cross(b->angularVelocity, info.collisionPointWorld);
				//v_rel = v1-v2
				Vec3 vRel = v1 - v2;

				if (dot(vRel, info.normalWorld) > 0) {
					continue;
				}

				double impulse = calculateImpulse(vRel,info.normalWorld,info.collisionPointWorld,a,b);

				//update velocities
				a->linearVelocity = a->linearVelocity + impulse * info.normalWorld / a->mass;
				b->linearVelocity = b->linearVelocity - impulse * info.normalWorld / b->mass;
			
				a->angularMomentum = a->angularMomentum + cross(a->position,impulse*info.normalWorld);
				b->angularMomentum = b->angularMomentum - cross(b->position, impulse*info.normalWorld);
			}
		}
	}
}

double RigidBodySystemSimulator::calculateImpulse(Vec3 vRel, Vec3 normal,Vec3 point, RigidBody *a, RigidBody *b) {
	float c = a->bounciness * b->bounciness;
	double numerator = -1*(1 + c)*dot(vRel,normal);
	double denominator_1 = 1 / a->mass + 1 / b->mass;
	Vec3 xA = point - a->position;
	Vec3 xB = point - b->position;
	Vec3 denominator_2 = cross(a->inversInertia*cross(xA, normal), a->position) + cross(b->inversInertia*cross(xB, normal), b->position);
	double denominator = denominator_1 + dot(denominator_2, normal);
	return numerator / denominator;
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
	RigidBody::Force adForce;
	adForce.f = force;
	adForce.p = loc;
	body.addForce(adForce);
	body.addAngularForce(cross(loc - body.position, force));
	body.addLinearForce(force);
}

void RigidBodySystemSimulator::addRigidBody(Vec3 position, Vec3 size, int mass)
{
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
