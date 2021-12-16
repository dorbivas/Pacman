#include "Ghosts.h"
//#include "Game.h" TODO? 
#include <queue>

#include "Game.h"


Position Ghosts::move_ghost(){
	Position new_dir;
	set_direction();

	if (direction == (int)Direction::UP)
	{
		new_dir.set_xy(pos.get_x(), pos.get_y() + 1); 
	}
	else if (direction == (int)Direction::DOWN)
	{
		new_dir.set_xy(pos.get_x(), pos.get_y() - 1);
	}
	else if (direction == (int)Direction::LEFT)
	{
		new_dir.set_xy(pos.get_x()-1, pos.get_y());
	}
	else //RIGHT
	{  
		new_dir.set_xy(pos.get_x()+1, pos.get_y());
	}

	return new_dir;
}


//smart ghost using BFS
//void Ghosts::smart(int grid[][COL], bool vis[][COL], int row, int col)
Entity::Direction Ghosts::smart(unsigned char grid[][25], Position target)
{
    // Direction vectors
    int move_vector_x[] = { -1, 0, 1, 0 };
    int move_vector_y[] = { 0, 1, 0, -1 };
	Entity::Direction next_move;


    int target_x = target.get_x(), target_y = target.get_y();
    std::queue<Position> moving_queue;
    bool is_visted[][25] = { false }; //init all cells as unvisited cells. 
    Position new_pos;

    moving_queue.push(target);
    is_visted[target_x][target_y] = true;

    while (!moving_queue.empty()) {

        Position curr = moving_queue.front();
		moving_queue.pop();

		int curr_x = curr.get_x();
		int curr_y = curr.get_y();
        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {

			if (get_position().get_x() + move_vector_x[i] == curr_x && 
				get_position().get_y() + move_vector_y[i] == curr_y )
			{
				switch (i) {
				case 0:	return Entity::Direction::LEFT;
				case 1: return Entity::Direction::UP;
				case 2:	return Entity::Direction::RIGHT;
				case 3:	return Entity::Direction::DOWN;
				}
			}
            new_pos.set_xy(curr_x + move_vector_x[i], curr_y + move_vector_y[i]);
            if (!is_invalid_place(new_pos) /*&& teleport && visited == false*/)
            {
                moving_queue.push(new_pos);
                is_visted[new_pos.get_x()][new_pos.get_y()] = true;
            }
        }
    }
}

/*
bool Ghosts::Entity::is_collided_ghost(const Position pacman_pos,Ghosts ghosts[],int num_of_ghosts,Pacman pacman) {
	int d1, d2, x_dif, y_dif;
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts[i].get_position() == pacman.get_position())
			return true;

		//edge cases
		d1 = ghosts[i].get_direction();
		d2 = pacman.get_direction();
		x_dif = pacman_pos.get_x() - ghosts[i].get_position().get_x();
		y_dif = pacman_pos.get_y() - ghosts[i].get_position().get_y();
		Position dif(x_dif, y_dif);

		if ((d1 == UP && d2 == DOWN && dif == Position(0, 1) ||
			d1 == DOWN && d2 == UP && dif == Position(0, -1) ||
			d1 == LEFT && d2 == RIGHT && dif == Position(-1, 0) ||
			d1 == RIGHT && d2 == LEFT && dif == Position(1, 0)))
			return true;
	}
	return false;
}*/



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
//}