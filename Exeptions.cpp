#include "Exceptions.h"

void Exceptions::print_exceptions() const
{
	system("cls");
	cout << "For " << screen << " file, there are " << error_msgs.size() << " Errors :" << endl;

	for (size_t i = 0; i < error_msgs.size(); i++)
		cout << i + 1 << ". " << error_msgs[i] << endl;
}
