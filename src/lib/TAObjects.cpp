#include "TAObjects.h"

using namespace std;

int n = 8; // aircraft//helicopter
//const int k = 2; // useless now
const float pi = 3.14159265359;
float dt = 0.01;


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


TLA::TLA() {
	this->f = true;
}


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

	// for (int i = 0; i < n; i++) {		// n + k; i++)
	// 	if (i / 2 == 1) {
	// 		TAircraft* craft = new TAircraft(abs(rand() % 100), abs(rand() % 130), abs(rand() % 300), abs(rand() % 200), abs(rand() % 200));
	// 		LA.push_back(craft);
	// 	}
	// 	else {
	// 		THelicopter* craft = new THelicopter(abs(rand() % 100), abs(rand() % 130), abs(rand() % 300), abs(rand() % 200), abs(rand() % 200));
	// 		LA.push_back(craft);
	// 	}
	// }
}


TAircraft::TAircraft(float x, float y, float V, float xc, float yc) : TLA(x, y, V, xc, yc) {
	this->spec = Aircraft;
}


THelicopter::THelicopter(float x, float y, float V, float xc, float yc) : TLA(x, y, V, xc, yc) {
	this->spec = Helicopter;
}


/*---------------------------------------FUCTIONS----------------------------------------------*/


void TLA::calculate() {
	// (1.1)
    R = sqrt( pow((x - xc), 2) + pow((y - yc), 2) );
    
	// (1.2)
    float b;
	if (x > xc)	{ b = 0; }
	if ((x < xc) && (y < yc)) {	b = -1;	}
	if ((x < xc) && (y > yc)) {	b =  1; }

	fi = b * pi + atan((y - yc) / (x - xc));

	//cout << endl << "b = " << b << ", fi1 = " << fi << ", R = " << R << endl;
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
	
	xc = -(x + R * cos(fi + omega * t)) * (a - 1) + a * (xc - V * dt);
	yc = -(y + R * sin(fi + omega * t)) * (a - 1) + a * yc;

	// (1.3)
	if (a == 0) {
		this->f = false;
	}
	if (a == 1) {
		this->f = true;
	}

	//cout << "x, y = " << x << ", " << y << " xc, yc = " << xc << ", " << yc << endl;
}


void THelicopter::move(float t, int a) {
	// (1.5)
	float dx = (a * V * cos(fi) * dt);
	float dy = (a * V * sin(fi) * dt);
	//cout << "do perescheta:" << endl << xc << ", " << yc << endl;
	//cout << "V = " << V << ", fi = " << fi << ", dx = " << dx << ", dy = " << dy << endl;
	//x = x + dx;
	//y = y + dy;
	xc = xc + (a * V * cos(fi) * dt); // xc - dx
	yc = yc + (a * V * sin(fi) * dt); // yc - dy

	// (1.3)
	if (a == 0) {
		this->f = false;
	}
	if (a == 1) {
		this->f = true;
	}

	//cout << "posle: " << " x, y = " << x << y << endl << "xc, yc = " << xc << ", " << yc << ", f = " << this->f << endl;
}



void TAirport::Do(float t0, float tk) {
	const string path = "log.txt";
	ofstream out(path);
	if (out.is_open()) {
		for (float t = t0; t < tk; t += dt) {
			for (int i = 0; i < n; i++) {
				int a = LA[i]->calculate_a(this->l, this->f);
				LA[i]->calculate();
				LA[i]->move(t, a);

				if (LA[i]->spec == Helicopter) {
					if (((pow((LA[i]->xc - x), 2) + pow((LA[i]->yc - y), 2)) < pow((l / 50), 2) && (this->f == false))) {
						this->f = true;
        				LA[i]->landing = 1;
						LA[i]->f = false;
						this->f = false;

						cout << "Heli #" << i + 1 << " landed" << endl;
						out << "Heli #" << i + 1 << " landed" << endl;
						delete LA[i + 1];
						n--;
						cout << "n = " << n << endl;
					}
					else {
						LA[i]->landing = 0;
						cout << "Heli #" << i + 1 << " not landed yet" << endl;
					}
					// cout << "LA.f = " << LA[i]->f << endl;
					// cout << "Do: " << "(" << i + 1 << ") " << "x, y = " << LA[i]->x << ", " << LA[i]->y << endl;
					// cout << endl << "t = " << t << ", a = " << a << ", landing - " << LA[i]->landing << ", xc = " << LA[i]->xc << ", yc = " << LA[i]->yc << endl;
					// cout << endl;
					// out << "LA.f = " << LA[i]->f << endl;
					// out << "Do: " << "(" << i + 1 << ") " << "x, y = " << LA[i]->x << ", " << LA[i]->y << endl;
					// out << endl << "t = " << t << ", a = " << a << ", landing - " << LA[i]->landing << ", xc = " << LA[i]->xc << ", yc = " << LA[i]->yc << endl;
					// out << endl;
				}
				else {
					if ((LA[i]->f == true) && (abs(LA[i]->xc) < (x + l))) {
						this->f = true;
        				LA[i]->landing = 1;
						LA[i]->f = false;
						this->f = false;

						cout << "Air #" << i + 1 << " landed" << endl;
						out << "Air #" << i + 1 << " landed" << endl;
						delete LA[i + 1];
						n--;
						cout << "n = " << n << endl;
    				}
					else if (LA[i]->f == true) {
        				LA[i]->landing = 0;
						cout << "LA #" << i + 1 << " not landed yet" << endl;
    				}
					// 	// cout << "LA.f = " << LA[i]->f << endl;
					// 	// cout << "Do: " << "(" << i + 1 << ") " << "x, y = " << LA[i]->x << ", " << LA[i]->y << endl;
					// 	// cout << endl << "t = " << t << ", a = " << a << ", landing - " << LA[i]->landing << ", xc = " << LA[i]->xc << ", yc = " << LA[i]->yc << endl;
					// 	// cout << endl;
					// 	// out << "LA.f = " << LA[i]->f << endl;
					// 	// out << "Do: " << "(" << i + 1 << ") " << "x, y = " << LA[i]->x << ", " << LA[i]->y << endl;
					// 	// out << endl << "t = " << t << ", a = " << a << ", landing - " << LA[i]->landing << ", xc = " << LA[i]->xc << ", yc = " << LA[i]->yc << endl;
					// 	// out << endl;
					// }

					// if (LA[i]->landing) {
					
				}
				
			}
		}

		out.close();
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
	// for (int i = 0; i < n; i++) {		// n + k; i++) + k; i++) 
	// 	delete LA[i];
	// }
	cout << "TAirport died" << endl;
}