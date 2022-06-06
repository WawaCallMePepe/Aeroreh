#include "lib/TAObjects.h"

#include <iostream>

using namespace std;

 
int main() {
    TAirport airp1(0.0, 0.0, 10.0);
    TLA* TNP[4];
    // целых 4 абстрактынх хеликоптера
    THelicopter Hel1(0.0, 0.0, 10.0, 100.0, 100.0); TNP[0] = &Hel1;
    THelicopter Hel2(0.0, 0.0, 10.0, 100.0, -100.0); TNP[1] = &Hel2;
    THelicopter Hel3(0.0, 0.0, 10.0, -100.0, -100.0); TNP[2] = &Hel3;
    THelicopter Hel4(0.0, 0.0, 10.0, -100.0, 100.0); TNP[3] = &Hel4;
    for (int i =0; i < 4; i++ ) {
        airp1.LA.push_back(TNP[i]);
        airp1.LA.push_back(TNP[i]);
        airp1.LA.push_back(TNP[i]);
        airp1.LA.push_back(TNP[i]);
    }
    airp1.Do(0.0, 15.0);
    // int a1 = 0; // craft.calculate_a(100, false);

    // airp1.Do(0, 10);
    //craft.update_landing(100);

    //cout << a1 << ", " << Hel1.xc << ", " << Hel1.yc << endl; //", " << craft.landing << ", " << craft.R << endl;

    return 0;
}
