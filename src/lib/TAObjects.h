#ifndef TAObjects
#define TAObjects

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <iomanip>

using namespace std;


class TAObject {
public:
	float x;
	float y;
	bool f;

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
	virtual void udpate_landing(float airp_l);
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
	void update_landing(float airp_l);
};


class THelicopter : public TLA {
public:
	THelicopter(float x, float y, float V, float xc, float yc);

	virtual void move(float t, int a);
	int calculate_a(float airp_l, bool airp_f);
	void update_landing(float airp_l);
};


#endif
