#include "lib/TAObjects.h"

#include <iostream>

using namespace std;

 
int main() {
    TAirport airp1(0.0, 0.0, 10.0);
	
    // целых 4 абстрактынх хеликоптера
    THelicopter* Hel1 = new THelicopter(0.0, 0.0, 10.0, 100.0, 100.0); 
    THelicopter* Hel2 = new THelicopter(0.0, 0.0, 10.0, 100.0, -100.0); 
    THelicopter* Hel3 = new THelicopter(0.0, 0.0, 10.0, -100.0, -100.0);     
    THelicopter* Hel4 = new THelicopter(0.0, 0.0, 10.0, -100.0, 100.0); 
	
    
    airp1.LA.push_back(hel1);
	airp1.LA.push_back(hel2);
	airp1.LA.push_back(hel3);
	airp1.LA.push_back(hel4);
    
	
    airp1.Do(0.0, 15.0);

    return 0;
}
