#include "MassSpringSystemSimulator.h"

MassSpringSystemSimulator::MassSpringSystemSimulator()
{
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
	TwType TW_TYPE_TESTCASE_INTEGRATOR = TwDefineEnumFromString("Integrator", "Euler,UNIMPLEMENTED,Midpoint");
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
		TwAddVarRW(DUC->g_pTweakBar, "Integrator", TW_TYPE_TESTCASE_INTEGRATOR, &m_iIntegrator, "");
		TwAddVarRW(DUC->g_pTweakBar, "Mass", TW_TYPE_FLOAT, &m_fMass, "step=0.01 min=0.01");
		TwAddVarRW(DUC->g_pTweakBar, "Stiffness", TW_TYPE_FLOAT, &m_fStiffness, "step=0.1 min=0.1");
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
	for (int i = 0; i < getNumberOfMassPoints(); i++)
	{
		DUC->setUpLighting(Vec3(), 0.4*Vec3(1, 1, 1), 100, Vec3(1, 0, 0));
		DUC->drawSphere(getPositionOfMassPoint(i), Vec3(0.05f, 0.05f, 0.05f));
	}
	for (int i = 0; i < getNumberOfSprings(); i++)
	{
		DUC->beginLine();
		DUC->drawLine(springs.at(i).point1->position, Vec3(0, 1, 0), springs.at(i).point2->position, Vec3(0, 1, 0));
		DUC->endLine();
	}
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase)
{
	m_iTestCase = testCase;
	mpoints.clear();
	springs.clear();
	switch (m_iTestCase)
	{
	case 0:
		cout << "Demo1!\n";
		setupDemo1();
		break;
	case 1:
		cout << "Demo2!\n";
		setupDemo2();
		break;
	case 2:
		cout << "Demo3!\n";
		setupDemo3();
		break;
	case 3:
		cout << "Demo4!\n";
		setupDemo4();
		break;
	default:  // demo 5 optional
		cout << "Empty Test!\n";
		break;
	}
}

void MassSpringSystemSimulator::setupDemo1()
{
	m_iIntegrator = EULER;
	setMass(10);
	setStiffness(40);
	int mp0 = addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
	int mp1 = addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
	addSpring(mp0, mp1, 1);
	simulateTimestep(0.1f);
	cout << "\nEULER\n";
	cout << "\nPoint 1\nPosition: " << getPositionOfMassPoint(mp0) << "\nVelocity: " << getVelocityOfMassPoint(mp0);
	cout << "\n\nPoint 2\nPosition: " << getPositionOfMassPoint(mp1) << "\nVelocity: " << getVelocityOfMassPoint(mp1) << "\n\n";
	mpoints.clear();
	springs.clear();
	m_iIntegrator = MIDPOINT;
	mp0 = addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
	mp1 = addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
	addSpring(mp0, mp1, 1);
	simulateTimestep(0.1f);
	cout << "MIDPOINT\n";
	cout << "\nPoint 1\nPosition: " << getPositionOfMassPoint(mp0) << "\nVelocity: " << getVelocityOfMassPoint(mp0);
	cout << "\n\nPoint 2\nPosition: " << getPositionOfMassPoint(mp1) << "\nVelocity: " << getVelocityOfMassPoint(mp1) << "\n\n";
}

void MassSpringSystemSimulator::setupDemo2()
{
	m_iIntegrator = EULER;
	setMass(10);
	setStiffness(40);
	int mp0 = addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
	int mp1 = addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
	addSpring(mp0, mp1, 1);
}

void MassSpringSystemSimulator::setupDemo3()
{
	m_iIntegrator = MIDPOINT;
	setMass(10);
	setStiffness(40);
	int mp0 = addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
	int mp1 = addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
	addSpring(mp0, mp1, 1);
}

void MassSpringSystemSimulator::setupDemo4()
{
	m_iIntegrator = EULER;
	setMass(10);
	setStiffness(100);
	std::mt19937 eng;
	std::uniform_real_distribution<float> randPos(-0.5f, 0.5f);
	for (int i = 0; i < 10; i++)
	{
		addMassPoint(Vec3(randPos(eng), randPos(eng), randPos(eng)), Vec3(0,0,0), false);
	}
	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			Vec3 diff = getPositionOfMassPoint(i) - getPositionOfMassPoint(j);
			addSpring(i, j, sqrtf(dot(diff, diff)));
		}
	}
}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed)
{
	if (m_iTestCase != 3)
	{
		return;
	}
	Point2D mouseDiff;
	mouseDiff.x = m_trackmouse.x - m_oldtrackmouse.x;
	mouseDiff.y = m_trackmouse.y - m_oldtrackmouse.y;
	if (mouseDiff.x != 0 || mouseDiff.y != 0)
	{
		Mat4 worldViewInv = Mat4(DUC->g_camera.GetWorldMatrix() * DUC->g_camera.GetViewMatrix());
		worldViewInv = worldViewInv.inverse();
		Vec3 inputView = Vec3((float)mouseDiff.x, (float)-mouseDiff.y, 0);
		Vec3 inputWorld = worldViewInv.transformVectorNormal(inputView);
		float inputScale = 0.000025f;
		inputWorld = inputWorld * inputScale;
		for (std::vector<Point>::size_type i = 0; i != mpoints.size(); i++) {
			mpoints[i].position += inputWorld;
			mpoints[i].velocity.y = 0;
		}
	}
}

void MassSpringSystemSimulator::simulateTimestep(float timeStep)
{
	Vec3 gravity = Vec3(0, -10, 0);
	switch (m_iIntegrator)
	{
	case EULER:
		for (std::vector<Spring>::size_type i = 0; i != springs.size(); i++) {
			springs[i].computeElasticForces();
			springs[i].addForcesToEndpoints();
		}
		for (std::vector<Point>::size_type i = 0; i != mpoints.size(); i++) {
			if (m_iTestCase == 3)
			{
				mpoints[i].addForce(gravity);
			}
			mpoints[i].calcEulerPos(timeStep, m_iTestCase == 3);
			mpoints[i].clearForces();
		}
		break;
	case LEAPFROG:  // optional
		break;
	case MIDPOINT:
		for (std::vector<Spring>::size_type i = 0; i != springs.size(); i++) {
			springs[i].computeElasticForces();
			springs[i].addForcesToEndpoints();
		}
		for (std::vector<Point>::size_type i = 0; i != mpoints.size(); i++) {
			if (m_iTestCase == 3)
			{
				mpoints[i].addForce(gravity);
			}
			mpoints[i].updateMidVals(timeStep);
			mpoints[i].clearForces();
		}
		for (std::vector<Spring>::size_type i = 0; i != springs.size(); i++) {
			springs[i].computeElasticMidpointForces();
			springs[i].addForcesToEndpoints();
		}
		for (std::vector<Point>::size_type i = 0; i != mpoints.size(); i++) {
			if (m_iTestCase == 3)
			{
				mpoints[i].addForce(gravity);
			}
			mpoints[i].calcMidpoint(timeStep, m_iTestCase == 3);
			mpoints[i].clearForces();
		}
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

int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 velocity, bool isFixed)  // currently isFixed has no effect
{
	mpoints.push_back(Point(position, velocity, Vec3(0, 0, 0), &m_fMass, &m_fDamping, isFixed));
	return getNumberOfMassPoints() - 1;
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength)
{
	Spring spring = Spring(&mpoints[masspoint1], &mpoints[masspoint2], &m_fStiffness, initialLength);
	springs.push_back(spring);
}

int MassSpringSystemSimulator::getNumberOfMassPoints()
{
	return mpoints.size();
}

int MassSpringSystemSimulator::getNumberOfSprings()
{
	return springs.size();
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
	for (std::vector<Point>::size_type i = 0; i != mpoints.size(); i++) {
		mpoints[i].addForce(force);
	}
}
// End of specific functions
