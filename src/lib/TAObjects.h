#ifndef TAObjects
#define TAObjects

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <iomanip>

using namespace std;


enum typeTLA {Aircraft, Helicopter};

// struct coords {
// 	float x, y;
// };

class TAObject {
public:
	float x;
	float y;
	// coords place;
	bool f;
	typeTLA spec;

	TAObject();
	TAObject(float x, float y);
	~TAObject();
};


class TLA : public TAObject {
public:
	float xc;
	float yc;
	float R;
	float fi;
	float V;
	bool landing;

	TLA();
	TLA(float x, float y, float V, float xc, float yc);
	~TLA();

	virtual void calculate();
	virtual void move(float t, int a);
	virtual int calculate_a(float airp_l, bool airp_f);
};


class TAirport : public TAObject {
public:
	float l;
	vector<TLA*> LA;
	
	TAirport();
	TAirport(float x, float y, float l);
	~TAirport();

	void Do(float t0, float tk);
};


class TAircraft : public TLA {
public:
	TAircraft(float x, float y, float V, float xc, float yc);

	virtual void move(float t, int a);
	int calculate_a(float airp_l, bool airp_f);
};


class THelicopter : public TLA {
public:
	THelicopter(float x, float y, float V, float xc, float yc);

	virtual void move(float t, int a);
	int calculate_a(float airp_l, bool airp_f);
};


#endif
