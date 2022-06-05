#include "lib/TAObjects.h"

#include <iostream>
#include <stdio.h>

using namespace std;

 
int main() {
    // ебать я создал абсрактный хеликоптер

    TAircraft craft(0, 0, 2, 100, 100);

    for (int i = 0; i < 40; i++) {

        craft.calculate();
        int a1 = craft.calculate_a(50, false);
        craft.move(10, a1);
        craft.update_landing(100);

        printf("%i (%f %f) %d \n", a1, craft.x, craft.y, craft.landing);
        
        if (craft.landing) {
            break;
        }
    }

    return 0;
}
