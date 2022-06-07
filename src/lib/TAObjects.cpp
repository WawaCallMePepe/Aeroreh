#include "TAObjects.h"

using namespace std;

const int n = 8; // aircraft//helicopter
//const int k = 2; // useless now
const float pi = 3.14159265359;
int dt = 1;


/*---------------------------------------CONCTRUCTORS----------------------------------------------*/


TAObject::TAObject() {
	this->f = false;
}


TAirport::TAirport() {}


TAObject::TAObject(float x, float y) {
	this->x = x;
	this->y = y;

	cout << "TAObject generated with: " << this->x << ", " << this->y << endl;
}


TLA::TLA() {}


TLA::TLA(float x, float y, float V, float xc, float yc) : TAObject(x, y) {
	this->V = V;
	this->xc = xc;
	this->yc = yc;

	cout << "TLA generated with: " << x << ", " << y << ", " << V << ", " << xc << ", " << yc << endl;
}


TAirport::TAirport(float x, float y, float l) : TAObject(x, y) {
	this->l = l;
	this->f = false; // svoboda
	cout << "TAirport generated with :" << x << ", " << y << ", " << l << endl;

	for (int i = 0; i < n; i++) {		// n + k; i++)
		//if (i / 2 == 1) {
		//
			//TAircraft* craft = new TAircraft(abs(rand() % 100), abs(rand() % 130), abs(rand() % 300), abs(rand() % 200), abs(rand() % 200));
			//LA.push_back(craft);
		//}
		//else {
		//
		//	THelicopter* craft = new THelicopter(abs(rand() % 100), abs(rand() % 130), abs(rand() % 300), abs(rand() % 200), abs(rand() % 200));
		//	LA.push_back(craft);
		//}
	}
}


TAircraft::TAircraft(float x, float y, float V, float xc, float yc) : TLA(x, y, V, xc, yc) {}


THelicopter::THelicopter(float x, float y, float V, float xc, float yc) : TLA(x, y, V, xc, yc) {}


/*---------------------------------------FUCTIONS----------------------------------------------*/


void TLA::calculate() {
	// (1.1)
    R = sqrt( pow((x - xc), 2) + pow((y - yc), 2) );
    
	// (1.2)
    float b;
	if (x > xc)	{ b = 0; }
	if ((x < xc) && (y < yc)) {	b = -1;	}
	if ((x < xc) && (y > yc)) {	b = 1; }

	fi = b * pi + atan((y - yc) / (x - xc));

	cout << endl << "b = " << b << ", fi1 = " << fi << endl;
}


int TLA::calculate_a(float airp_l, bool airp_f) {
	return 1;
}


int TAircraft::calculate_a(float airp_l, bool airp_f) {
	float X = x + (1.1 * airp_l);

	// (1.6)
	int a = 0;
	if (!(airp_f && !(f)) && (xc < X) && (abs(yc - y) < airp_l / 50)) {
		a = 1;
	}
	else {
		a = 0;
	}
	return a;
}


int THelicopter::calculate_a(float airp_l, bool airp_f) {

	// (1.7)
	int a = 0;
	if (!((airp_f) && !(f))) {
	
		a = 1;
	}
	else {
	
		a = 0;
	}
	return a;
}



void TLA::move(float t, int a) {
	// (1.3)
	if (a == 0) {
		this->f = false;
	}
	if (a == 1) {
		this->f = true;
	}
}


void TAircraft::move(float t, int a) {
	// (1.4)
    float omega = - (V / R);
	
	this->xc = -(xc + R * cos(fi + omega * t)) * (a - 1) + a * (xc + V * dt);
	this->yc = -(yc + R * sin(fi + omega * t)) * (a - 1) + a * yc;
}


void THelicopter::move(float t, int a) {
	// (1.5)
	float dx = - (a * V * cos(fi) * dt);
	float dy = - (a * V * sin(fi) * dt);
	cout << "do perescheta:" << endl << xc << ", " << yc << endl;
	cout << "V = " << V << ", fi = " << fi << ", dx = " << dx << ", dy = " << dy << endl;
	//x = x + dx;
	//y = y + dy;
	xc = xc - dx;
	yc = yc - dy;

	cout << "posle:" << endl << xc << ", " << yc << endl;
}



void TLA::udpate_landing(float airp_l) {
	landing = false;
}

void TAircraft::update_landing(float airp_l) {
	if ((f == true) && (xc > (x + airp_l))) { 
        landing = false; 
    }
	else if (f == true) {
        landing = true;
    }
}


void THelicopter::update_landing(float airp_l) {
	// (1.9)
	if (((pow((xc - x), 2) + pow((yc - y), 2)) < pow((airp_l / 50), 2) && (f == false))) {
		landing = true;
	}
	else {
		landing = false;
	}
}


void TAirport::Do(float t0, float tk) {
	for (int t = t0; t < tk; t += dt) {
		for (int i = 0; i < n; i++) {			// n + k; i++)
			int a = LA[i]->calculate_a(this->l, this->f);
			LA[i]->calculate();
			LA[i]->move(t, a);
			LA[i]->udpate_landing(this->l);

			cout << "(" << i + 1 << ")" << endl << "Do: " << endl << "t = " << t << ", a = " << a << ", landing - " << LA[i]->landing << ", xc = " << LA[i]->xc << ", yc = " << LA[i]->yc << endl;
			cout << endl;
		}
	}
}

/*---------------------------------------DESTRUCTORS----------------------------------------------*/


TAObject::~TAObject() {
	cout << "TAObj died" << endl;
}


TLA::~TLA() {
	cout << "TLA died" << endl;
}


TAirport::~TAirport() {
	for (int i = 0; i < n; i++) {		// n + k; i++) + k; i++) 
		delete LA[i];
	}
	cout << "TAirport died" << endl;
}
