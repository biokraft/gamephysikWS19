#include "MassSpringSystemSimulator.h"

MassSpringSystemSimulator::MassSpringSystemSimulator()
{
	//TODO
	m_iTestCase = 0;
}

// Start of UI functions
const char * MassSpringSystemSimulator::getTestCasesStr()
{
	return "BasicTest,Setup1,Setup2,Setup3"; // names copied from example video
}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass * DUC)
{
	//TODO
}

void MassSpringSystemSimulator::reset()
{
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext * pd3dImmediateContext)
{
	//TODO
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase)
{
	//TODO
	m_iTestCase = testCase;
	switch (m_iTestCase)
	{
	case 0:
		cout << "BasicTest!\n";
		// m_vfMovableObjectPos = Vec3(0, 0, 0);  // template simulator
		// m_vfRotate = Vec3(0, 0, 0);
		break;
	case 1:
		cout << "Setup1!\n";
		// m_iNumSpheres = 100;
		// m_fSphereSize = 0.05f;
		break;
	case 2:
		cout << "Setup2!\n";
		break;
	case 3:
		cout << "Setup3!\n";
		break;
	default:
		cout << "Empty Test!\n";
		break;
	}
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
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

void MassSpringSystemSimulator::onMouse(int x, int y)
{
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;
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
