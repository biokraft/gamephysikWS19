#include "MassSpringSystemSimulator.h"

MassSpringSystemSimulator::MassSpringSystemSimulator()
{
	//TODO
}

// Start of UI functions
const char * MassSpringSystemSimulator::getTestCasesStr()
{
	return nullptr;
}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass * DUC)
{
	//TODO
}

void MassSpringSystemSimulator::reset()
{
	//TODO
}

void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext * pd3dImmediateContext)
{
	//TODO
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase)
{
	//TODO
}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed)
{
	//TODO
}

void MassSpringSystemSimulator::simulateTimestep(float timeStep)
{
	//TODO
}

void MassSpringSystemSimulator::onClick(int x, int y)
{
	//TODO
}

void MassSpringSystemSimulator::onMouse(int x, int y)
{
	//TODO
}
// End of UI functions

// Start of specific functions
void MassSpringSystemSimulator::setMass(float mass)
{
	m_fMass = mass;
}

void MassSpringSystemSimulator::setStiffness(float stiffness)
{
	m_fStiffness = stiffness;
}

void MassSpringSystemSimulator::setDampingFactor(float damping)
{
	m_fDamping = damping;
}

int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed)
{
	//TODO
	return 0;
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength)
{
	//TODO
}

int MassSpringSystemSimulator::getNumberOfMassPoints()
{
	//TODO
	return 0;
}

int MassSpringSystemSimulator::getNumberOfSprings()
{
	//TODO
	return 0;
}

Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index)
{
	//TODO
	return Vec3();
}

Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index)
{
	//TODO
	return Vec3();
}

void MassSpringSystemSimulator::applyExternalForce(Vec3 force)
{
	//TODO
}
// End of specific functions
