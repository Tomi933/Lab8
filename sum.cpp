#include <math.h>
#include "dod.h"
#include "sum.h"
#include "var.h" // ��������� ������ ���������� ������

using namespace nsDod;
using namespace nsVar;
void nsSum::sum() {
    n = 0;
    dod(); // ���������� ������� �������
    s = a;
    while (fabs(a) > e) {
        n++;
        dod();
        s += a;
    }
}