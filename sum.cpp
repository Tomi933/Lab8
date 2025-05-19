#include <math.h>
#include "dod.h"
#include "sum.h"
#include "var.h" // підключили зовнішні оголошення змінних

using namespace nsDod;
using namespace nsVar;
void nsSum::sum() {
    n = 0;
    dod(); // обчислення першого доданка
    s = a;
    while (fabs(a) > e) {
        n++;
        dod();
        s += a;
    }
}