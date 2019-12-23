#include "DiffusionSimulator.h"
#include "pcgsolver.h"
#include <stdlib.h>
using namespace std;

Grid::Grid() {
}


DiffusionSimulator::DiffusionSimulator()
{
	m_iTestCase = 0;
	m_vfMovableObjectPos = Vec3();
	m_vfMovableObjectFinalPos = Vec3();
	m_vfRotate = Vec3();
	// TODO to be implemented
}

const char * DiffusionSimulator::getTestCasesStr(){
	return "Explicit_solver, Implicit_solver";
}

void DiffusionSimulator::reset(){
		m_mouse.x = m_mouse.y = 0;
		m_trackmouse.x = m_trackmouse.y = 0;
		m_oldtrackmouse.x = m_oldtrackmouse.y = 0;

}

void DiffusionSimulator::initUI(DrawingUtilitiesClass * DUC)
{
	this->DUC = DUC;
	// TODO to be implemented
}

void DiffusionSimulator::notifyCaseChanged(int testCase)
{
	m_iTestCase = testCase;
	m_vfMovableObjectPos = Vec3(0, 0, 0);
	m_vfRotate = Vec3(0, 0, 0);
	//
	// TODO to be implemented
	//
	initField(16, 16);
	cout << T->m << "  " << T->n << "\n";
	switch (m_iTestCase)
	{
	case 0:
		cout << "Explicit solver!\n";
		break;
	case 1:
		cout << "Implicit solver!\n";
		break;
	default:
		cout << "Empty Test!\n";
		break;
	}
}

void DiffusionSimulator::initField(int m, int n)
{
	T = new Grid();
	T->m = m;
	T->n = n;
	vector<Real> srow;
	for (int k = 0; k < n+2; k++) {
		srow.push_back(0);
	}
	T->gridarray.push_back(srow);
	for (int y = 0; y < m; y++) {
		vector<Real> newrow;
		newrow.push_back(0);
		for (int x = 0; x < n; x++) {
			double random_value = ((double)rand() / (RAND_MAX)) * 2;
			newrow.push_back(random_value);
		}
		newrow.push_back(0);
		T->gridarray.push_back(newrow);
	}
	vector<Real> erow;
	for (int k = 0; k < n+2; k++) {
		erow.push_back(0);
	}
	T->gridarray.push_back(erow);
}

Grid* DiffusionSimulator::diffuseTemperatureExplicit(float timeStep) { // TODO add your own parameters

	// TODO to be implemented
	// make sure that the temperature in boundary cells stays zero
	
	// ----
	Grid* newT = new Grid();
	newT->m = T->m;
	newT->n = T->n;
	vector<Real> srow;
	for (int k = 0; k < T->gridarray[0].size(); k++) {
		srow.push_back(0);
	}
	newT->gridarray.push_back(srow);
	for (int py = 1; py < T->gridarray.size() - 1; py++) {
		vector<Real> newrow;
		newrow.push_back(0);
		for (int px = 1; px < T->gridarray[py].size() - 1; px++) {
			double pointVal = T->gridarray[py][px];
			double leftVal = T->gridarray[py][px - 1];
			double rightVal = T->gridarray[py][px + 1];
			double downVal = T->gridarray[py + 1][px];
			double upVal = T->gridarray[py - 1][px];

			double newPointVal = 0 * downVal - pointVal + upVal;
			newPointVal += 0 * leftVal - pointVal + rightVal;
			newPointVal += 0 * upVal - pointVal + downVal;
			newPointVal += 0 * rightVal - pointVal + leftVal;
			newrow.push_back(newPointVal);
		}
		newrow.push_back(0);
		newT->gridarray.push_back(newrow);
	}
	vector<Real> erow;
	for (int k = 0; k < T->gridarray[0].size(); k++) {
		erow.push_back(0);
	}
	newT->gridarray.push_back(erow);
	return newT;
}

void setupB(std::vector<Real>& b, Grid* T) {// TODO add your own parameters
	// TODO to be implemented
	// set vector B[sizeX*sizeY]
	//for (int y = 0; y < T->gridarray.size; y++) {
	//	b.at(y) = 1 - (T->gridarray[y].size - 1);
	//}
	for (int y = 0; y < T->m; y++) {
		for (int x = 0; x < T->n; x++) {
			b.at(y*T->n + x) = -T->gridarray[y][x];
		}
	}
}

void DiffusionSimulator::fillT(std::vector<Real>& x) {// TODO add your own parameters
	// TODO to be implemented
	//fill T with solved vector x
	//make sure that the temperature in boundary cells stays zero (done)
	T->gridarray.clear();
	vector<Real> srow;
	for (int k = 0; k < T->gridarray[0].size(); k++) {
		srow.push_back(0);
	}
	T->gridarray.push_back(srow);
	for (int py = 1; py < T->gridarray.size() - 1; py++) {
		vector<Real> newrow;
		newrow.push_back(0);
		for (int px = 1; px < T->gridarray[py].size() - 1; px++) {
			newrow.push_back(x.at(py*(T->n + 2) + px));
		}
		newrow.push_back(0);
		T->gridarray.push_back(newrow);
	}
	vector<Real> erow;
	for (int k = 0; k < T->gridarray[0].size(); k++) {
		erow.push_back(0);
	}
	T->gridarray.push_back(erow);
}

void setupA(SparseMatrix<Real>& A, double factor, float timeStep) {//TODO add your own parameters
	// TODO to be implemented
	//setup Matrix A[sizeX*sizeY*sizeZ, sizeX*sizeY*sizeZ]
	// set with:  A.set_element( index1, index2 , value );
	// if needed, read with: A(index1, index2);
	// avoid zero rows in A -> set the diagonal value for boundary cells to 1.0

	//for (int i = 0; i < 25; i++) {
	//		A.set_element(i, i, 1); // set diagonal
	//}
	// ----

	double dx = 1; // delta x; TODO Richtige Werte (Konstante) setzen
	double dt = timeStep; // delta time
	double alpha = 0.1; // TODO alpha = factor?

	double r = alpha * dt / dx * dx;

	for (int y = 0; y < A.index.size(); y++) {
		for (int x = 0; x < A.index[y].size(); y++) {
			A.set_element(y, x, 0);
			if (y == x)
				A.set_element(y, x, (1 - 2 * r));
			if ((x == y - 1 || x == y + 1) && y > 0 && y < (A.index.size() - 1)) {
				A.set_element(y, x, r);
			}
		}
	}
	A.set_element(0, 0, 1);
	A.set_element(A.index.size()-1, A.index[A.index.size()-1].size()-1, 1);
}


void DiffusionSimulator::diffuseTemperatureImplicit(float timeStep) { // TODO add your own parameters
	// solve A T = b
	// to be implemented
	const int N = T->m*T->n;//N = sizeX*sizeY*sizeZ
	SparseMatrix<Real> *A = new SparseMatrix<Real> (N);
	std::vector<Real> *b = new std::vector<Real>(N);

	setupA(*A, 0.1, timeStep);
	setupB(*b, T);

	// perform solve
	Real pcg_target_residual = 1e-05;
	Real pcg_max_iterations = 1000;
	Real ret_pcg_residual = 1e10;
	int  ret_pcg_iterations = -1;

	SparsePCGSolver<Real> solver;
	solver.set_solver_parameters(pcg_target_residual, pcg_max_iterations, 0.97, 0.25);

	std::vector<Real> x(N);
	for (int j = 0; j < N; ++j) { x[j] = 0.; }

	// preconditioners: 0 off, 1 diagonal, 2 incomplete cholesky
	solver.solve(*A, *b, x, ret_pcg_residual, ret_pcg_iterations, 0);
	// x contains the new temperature values
	fillT(x);//copy x to T
}



void DiffusionSimulator::simulateTimestep(float timeStep)
{
	// TODO to be implemented
	// update current setup for each frame
	switch (m_iTestCase)
	{
	case 0:
		T = diffuseTemperatureExplicit(timeStep);
		break;
	case 1:
		diffuseTemperatureImplicit(timeStep);
		break;
	}
}

void DiffusionSimulator::drawObjects()
{
	// TODO to be implemented
	//visualization
	for (int y = 0; y < T->m+2; y++) {
		for (int x = 0; x < T->n+2; x++) {
			cout << T->gridarray[y][x] << "\n";
			DUC->setUpLighting(Vec3(), 0.4*Vec3(1, 1, 1), 100, Vec3(1, T->gridarray[y][x], T->gridarray[y][x]));
			DUC->drawSphere(Vec3(x, y, 1), Vec3(1, 1, 1));
		}
	}
}


void DiffusionSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext)
{
	drawObjects();
}

void DiffusionSimulator::onClick(int x, int y)
{
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

void DiffusionSimulator::onMouse(int x, int y)
{
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}
