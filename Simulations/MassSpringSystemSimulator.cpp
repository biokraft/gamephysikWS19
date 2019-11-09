#include "MassSpringSystemSimulator.h"

MassSpringSystemSimulator::MassSpringSystemSimulator()
{
	// TODO initialize necessary variables
	m_iTestCase = 0;
}

// Start of UI functions
const char * MassSpringSystemSimulator::getTestCasesStr()
{
	return "Demo1,Demo2,Demo3,Demo4";  // demo 5 optional
}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass * DUC)
{
	this->DUC = DUC;
	switch (m_iTestCase)
	{
	case 0:
		TwRemoveVar(DUC->g_pTweakBar, "Timestep");  // time step in demo is constant
		break;
	case 1:
		TwRemoveVar(DUC->g_pTweakBar, "Timestep");  // time step in demo is constant
		break;
	case 2:
		TwRemoveVar(DUC->g_pTweakBar, "Timestep");  // time step in demo is constant
		break;
	case 3:
		TwAddVarRW(DUC->g_pTweakBar, "Integrator", TW_TYPE_INT32, &m_iIntegrator, "min=0 max=2 step=2"); // TODO display names instead
		// TODO add more TwAddVarRW() (see page 3 point 4 in task description)
		break;
	default:break;
	}
}

void MassSpringSystemSimulator::reset()
{
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext * pd3dImmediateContext)
{
	// TODO (tips on last exercise page)
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase)
{
	// TODO set initial variables in demos where necessary (possibly spawn mass points and strings here)
	m_iTestCase = testCase;
	switch (m_iTestCase)
	{
	case 0:
		cout << "Demo1!\n";
		// TODO set time step to 0.1
		break;
	case 1:
		cout << "Demo2!\n";
		// TODO set time step to 0.005
		break;
	case 2:
		cout << "Demo3!\n";
		// TODO set time step to 0.005
		break;
	case 3:
		cout << "Demo4!\n";
		break;
	default:  // demo 5 optional
		cout << "Empty Test!\n";
		break;
	}
}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed)
{
	// TODO
}

void MassSpringSystemSimulator::simulateTimestep(float timeStep)
{
	// TODO
	switch (m_iTestCase)
	{
	case 0:
		
		break;
	case 2: // euler
		for (std::vector<int>::size_type i = 0; i != springs.size(); i++) {
			springs[i].computeElasticForces();
			springs[i].addForcesToEndpoints();
		}
		for (std::vector<int>::size_type i = 0; i != mpoints.size(); i++) {
			//mpoints[i].calcEulerPos(timeStep);
			//mpoints[i].clearForces();
			mpoints[i].addForce(Vec3(0,0,-10));//add gravity TODO is -z gravity ??
			mpoints[i].calcEulerPos(timeStep);
		}
		break;
	case 3: // midpoint
		break;
	default:
		break;
	}
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

int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 velocity, bool isFixed)
{
	mpoints.push_back(Point(position, velocity, Vec3(0, 0, 0), m_fMass, m_fDamping));
	// TODO isFixed -> new vector for saving if mass point is fixed?
	return getNumberOfMassPoints() - 1;  // TODO return index of mass point?
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength)
{
	// TODO springs.push_back();  // How are the springs even saved? Is the springs vector even necessary? TODO: Update header file
								  // this method doesn't return anything unlike addMassPoint()

	Spring spring = Spring(&mpoints[masspoint1], &mpoints[masspoint2], m_fStiffness, initialLength);
	springs.push_back(spring);
}

int MassSpringSystemSimulator::getNumberOfMassPoints()
{
	return mpoints.size();
}

int MassSpringSystemSimulator::getNumberOfSprings()
{
	return springs.size();  // TODO if springs aren't saved in array (see addSpring() comments), maybe change to counter variable (int)
}

Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index)
{
	return mpoints.at(index).position;
}

Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index)
{
	return mpoints.at(index).velocity;
}

void MassSpringSystemSimulator::applyExternalForce(Vec3 force)
{
	// TODO, test class only calls this once with (0,0,0) so low priority if needed
}
// End of specific functions
