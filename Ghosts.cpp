#include "Ghosts.h"
using std::queue;

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
	if (steps >= 0 && steps <= 5) {
		novice_lvl_ghost();
		set_mode(Novice);
	}
	else
		smart(target); 
	set_mode(Smart);
}


//smart ghost using BFS
void Ghosts::smart(const Position& target)
{
	// Direction vectors
	int move_vector_x[] = { -1, 0, 1, 0 };
	int move_vector_y[] = { 0, 1, 0, -1 };

	int target_x = target.get_x(), target_y = target.get_y();
	queue<Position> moving_queue;
	bool is_visted[Board::MAX_SIZES::MAX_HEIGHT][Board::MAX_SIZES::MAX_WIDTH] = { { true } }; //init all cells as unvisited cells.
	// TODO: new?
	for (int i = 0; i < board.get_cols(); i++)
		for (int j = 0; j < board.get_rows(); j++)
			is_visted[i][j] = false;

	moving_queue.push(Position(1, 2));
	moving_queue.push(Position(1, 2));
	moving_queue.push(Position(1, 2));
	is_visted[target_y][target_x] = true;
	int max = 1000;

	while (!moving_queue.empty()) {
		if (max-- == 0)
		{
		}
		Position curr = moving_queue.front();
		moving_queue.pop();

		int curr_x = curr.get_x();
		int curr_y = curr.get_y();
		// Go to the adjacent cells
		for (int i = 0; i < 4; i++) {
			Position new_pos;

			new_pos.set_xy(curr_x + move_vector_x[i], curr_y + move_vector_y[i]);
			if (board.is_valid_move(new_pos) && is_visted[new_pos.get_y()][new_pos.get_x()] == false)
			{
				if (curr_x * curr_y < 0)
				{
				}
				moving_queue.push(new_pos);
				is_visted[new_pos.get_y()][new_pos.get_x()] = true;

				if (get_position().get_x() == curr_x + move_vector_x[i] &&
					get_position().get_y() == curr_y + move_vector_y[i])
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

bool Ghosts::is_invalid_place(const Position& next_pos) {
    return ((board.get_cell(next_pos) == (unsigned char)Board::WALL)||(is_my_teleporting(next_pos)));
}
