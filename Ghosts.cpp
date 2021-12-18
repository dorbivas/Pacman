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


//smart ghost using BFS
void Ghosts::smart(Position target)
{
	// Direction vectors
	int move_vector_x[] = { -1, 0, 1, 0 };
	int move_vector_y[] = { 0, 1, 0, -1 };

	int target_x = target.get_x(), target_y = target.get_y();
	std::queue<Position> moving_queue;
	bool is_visted[Board::board_size::HEIGHT][Board::board_size::WIDTH] = { { false } }; //init all cells as unvisited cells. 
	/*for (int i = 0; i < Board::board_size::HEIGHT; i++)
		for (int j = 0; j < Board::board_size::WIDTH; j++)
			is_visted[i][j] = false;*/

	moving_queue.push(target);
	is_visted[target_y][target_x] = true;

	while (!moving_queue.empty()) {

		Position curr = moving_queue.front();
		moving_queue.pop();

		int curr_x = curr.get_x();
		int curr_y = curr.get_y();
		// Go to the adjacent cells
		for (int i = 0; i < 4; i++) {
			Position new_pos;

			new_pos.set_xy(curr_x + move_vector_x[i], curr_y + move_vector_y[i]);
			/*   if (new_pos.get_x() == 38 && new_pos.get_y() == 12)
				   cout << 'u';*/
			if (is_valid_bfs(new_pos) && is_visted[new_pos.get_y()][new_pos.get_x()] == false)
			{
				moving_queue.push(new_pos);
				is_visted[new_pos.get_y()][new_pos.get_x()] = true;

				if (get_position().get_x() + move_vector_x[i] == curr_x &&
					get_position().get_y() + move_vector_y[i] == curr_y)
				{
					switch (i) { // OPOSITE TODO FUNC OUT
					case 0:    set_direction(Entity::Direction::RIGHT);
						return;
					case 1:    set_direction(Entity::Direction::DOWN);
						return;
					case 2:    set_direction(Entity::Direction::LEFT);
						return;
					case 3:    set_direction(Entity::Direction::UP);
						return;
					}
				}
			}

		}/*
		 for (int i = 0; i < Board::board_size::HEIGHT; i++) {
			 for (int j = 0; j < Board::board_size::WIDTH; j++) {
				 cout << is_visted[i][j];
			 }

			 cout << endl;*/
	}
}


bool Ghosts::is_valid_bfs(Position new_pos)
{
	if (new_pos.get_x() >= Board::board_size::WIDTH || new_pos.get_y() >= Board::board_size::HEIGHT)
		return false;
	if (is_invalid_place(new_pos))
		return false;
	return true;

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