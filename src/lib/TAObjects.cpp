#include "TAObjects.h"

using namespace std;

const int n = 1; 
const float pi = 3.14159265359;
int dt = 1;


TAObject::TAObject(float x, float y) {
    this->x = x;
    this->y = y;
}

TLA::TLA(float x, float y, float V, float xc, float yc) : TAObject(x, y) {
    this->V = V;
	this->xc = xc;
	this->yc = yc;
}

TAirport::TAirport(float x, float y, float l) : TAObject(x, y)
{
	this->l = l;
	this->f = false; // svoboda

	for (int i = 0; i < n; i++)
	{
		TAircraft* craft = new TAircraft(abs(rand() % 100), abs(rand() % 130), abs(rand() % 300), abs(rand() % 200), abs(rand() % 200));
		LA.push_back(craft);
	}
}

TAircraft::TAircraft(float x, float y, float V, float xc, float yc) : TLA(x, y, V, xc, yc) {}

// THelicopter::THelicopter(float x, float y, float V, float xc, float yc) : TLA(x, y, V, xc, yc) {}



void TLA::calculate() {
    R = sqrt( pow((x - xc), 2) + pow((y - yc), 2) );
    
    float b;

	if (x > xc)	{ b = 0; }
	if ((x < xc) && (y < yc)) {	b = -1;	}
	if ((x < xc) && (y > yc)) {	b = 1;	}

	fi = b * pi + atan((y - yc) / (x - xc));
}


int TLA::calculate_a(float airp_l, bool airp_f) { return 1; }

int TAircraft::calculate_a(float airp_l, bool airp_f) {
	int a;
    float X = x + (1.1 * airp_l);

	if (!(airp_f && !(f)) && (xc < X) && (abs(yc - y) < airp_l / 50)) { 
        a = 1; 
    }
	else { 
        a = 0;
    }

	return a;
}

// int THelicopter::calculate_a(float airp_x, float airp_y, float airp_l, bool airp_f) {
// 	int a;

// 	if (!((airp_f) && !(f))) {
//         a = 1;
//     }
// 	else {
//         a = 0;
//     }

// 	return a;
// }




void TLA::move(float t, int a) {
	if (a == 0) { this->f = false; }
	if (a == 1)	{ this->f = true;  }
}

void TAircraft::move(float t, int a) {
    float omega = -(V / R);
	
	x = -(xc + R * cos(fi + omega * t)) * (a - 1) + a * (x + V * dt);
	y = -(yc + R * sin(fi + omega * t)) * (a - 1) + a *  y;
}

// void THelicopter::move(float t, int a) {
// 	x = x - a * V * cos(fi) * dt;
// 	y = y - a * V * sin(fi) * dt;
// }


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


// void THelicopter::update_landing(float airp_x, float airp_y, float airp_l) {
// 	if (((pow((x - airp_x), 2) + pow((y - airp_y), 2)) < pow((airp_l / 50), 2) && (f == false))) {
// 		landing = true;
// 	}
// 	else {
// 		landing = false;
// 	}
// }




TAObject::~TAObject() { }
TLA::~TLA() { }