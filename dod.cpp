#include "dod.h"
#include "var.h" // ��������� ������ ���������� ������
#include <math.h>
using namespace nsVar;
void nsDod::dod() {
	a = 1.0 / (2 * n + 1) / pow(x, (2 * n + 1));
	
}