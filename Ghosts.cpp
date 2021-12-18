#include "Ghosts.h"

void Ghosts::novice_lvl_ghost(){
	if (steps == MAX_STEPS) {
		steps = 0;
		direction = generate_random_dir();
	}
	else
		steps++;
}

void Ghosts::good_lvl_ghost(Position target)
{
	if (steps >= 0 && steps <= 5)
		novice_lvl_ghost();
	else
		novice_lvl_ghost();
		//smart(target); TODO
}



bool Ghosts::is_invalid_place(const Position& next_pos) {
    return ((board.get_cell(next_pos) == (unsigned char)Board::WALL)||(is_my_teleporting(next_pos)));
}
//
//void Ex01Logic::getInputFromUserForArr(int& sumInput)
//{
//	string inputForArr;
//	int numberInArr = 0;
//	int sizeOfArr = 0;
//	string token;
//
//	cout << "Please enter in the first row the size of an array." << endl <<
//		"In the second row the members of the array." << endl << "In the third row a searched sum of two numbers : " << endl;
//	getline(cin, inputForArr);
//	sizeOfArr = stoi(inputForArr);
//	getline(cin, inputForArr);
//	istringstream iss(inputForArr);
//	getline(cin, inputForArr);
//	sumInput = stoi(inputForArr);
//
//	if (cin.eof() || (!iss.eof())) {
//		while (getline(iss, token, '\n'))
//		{
//			num_of_lines++;
//			numberInArr = stoi(token);
//			if (numberInArr < 0)
//			{
//				arr.clear();
//				throw "The arr can contain only natural numbers!";
//			}
//			else
//			{
//				arr.push_back(numberInArr);
//			}
//			sizeOfArr--;
//		}
//	}
//	if (sizeOfArr > 0 || sizeOfArr < 0)
//	{
//		arr.clear();
//		throw "The number of members that entered the array does not match its size";
//	}
//
//	if (arr.size() == 0)
//	{
//		throw "The array is empty!";
//	}
//
//}*/