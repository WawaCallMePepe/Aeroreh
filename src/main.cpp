#include "lib/TAObjects.h"

#include <iostream>

using namespace std;

 
int main() {
    TAirport airp1(0.0, 0.0, 130.0);
    // TLA* TNP[4];
    // THelicopter Hel1(0.0, 0.0, 10.0, 100.0, 100.0); TNP[0] = &Hel1;
    // THelicopter Hel2(0.0, 0.0, 10.0, 100.0, -100.0); TNP[1] = &Hel2;
    // THelicopter Hel3(0.0, 0.0, 10.0, -100.0, -100.0); TNP[2] = &Hel3;
    // THelicopter Hel4(0.0, 0.0, 10.0, -100.0, 100.0); TNP[3] = &Hel4;
    // for (int i =0; i < 4; i++ ) {
    //     airp1.LA.push_back(TNP[i]);
    //     airp1.LA.push_back(TNP[i]);
    //     airp1.LA.push_back(TNP[i]);
    //     airp1.LA.push_back(TNP[i]);
    // }
    
    THelicopter* Hel1 = new THelicopter(0.0, 0.0, 10.0, 100.0, 100.0); 
    THelicopter* Hel2 = new THelicopter(0.0, 0.0, 10.0, 100.0, -100.0); 
    THelicopter* Hel3 = new THelicopter(0.0, 0.0, 10.0, -100.0, -100.0);     
    THelicopter* Hel4 = new THelicopter(0.0, 0.0, 10.0, -100.0, 100.0); 
    TAircraft* Air1 = new TAircraft(0.0, 0.0, 15.0, 150.0, 150.0);
    TAircraft* Air2 = new TAircraft(0.0, 0.0, 15.0, 150.0, -150.0);
    TAircraft* Air3 = new TAircraft(0.0, 0.0, 15.0, -150.0, -150.0);
    TAircraft* Air4 = new TAircraft(0.0, 0.0, 15.0, -150.0, 150.0);
	
    airp1.LA.push_back(Hel1);
    airp1.LA.push_back(Hel2);
    airp1.LA.push_back(Hel3);
    airp1.LA.push_back(Hel4);
    airp1.LA.push_back(Air1);
    airp1.LA.push_back(Air2);
    airp1.LA.push_back(Air3);
    airp1.LA.push_back(Air4);

    airp1.Do(0.0, 18.0);

    return 0;
}
