#include "Exceptions.h"

void Exceptions::print_exceptions() const
{
	system("cls");
	cout << "For " << screen << " file, there are " << msg.size() << " Errors :" << endl;

	for (size_t i = 0; i < msg.size(); i++)
		cout << i + 1 << ". " << msg[i] << endl;
}
