#include "Packman.h"

void Packman::gotoxy(int y, int x) {
	cout << "\x1b[%d;%df" << x + 1 << y + 1;
}

