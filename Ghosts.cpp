#include "Ghosts.h"
using std::queue;
using std::list;

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
		good_f_status = true;
	}
	else
	{
		smart(target);
		good_f_status = false;
	}
		


}


void Ghosts::smart(const Position& target)
{
	// Direction vectors
	int move_vector_x[] = { -1, 0, 1, 0 };
	int move_vector_y[] = { 0, 1, 0, -1 };

	int target_x = target.get_x(), target_y = target.get_y();
	queue<Position> moving_queue;

	vector<vector<bool>> is_visted(board.get_rows(), vector<bool>(board.get_cols(), false));
	is_visted[target_y][target_x] = true;

	moving_queue.push(target);

	while (!moving_queue.empty()) {
		Position curr = moving_queue.front();
		moving_queue.pop();

		int curr_x = curr.get_x();
		int curr_y = curr.get_y();

		// Go to the adjacent cells
		for (int i = 0; i < 4; i++) {
			Position new_pos(curr_x + move_vector_x[i], curr_y + move_vector_y[i]);
			if (board.is_valid_move(new_pos) && is_visted[new_pos.get_y()][new_pos.get_x()] == false)
			{
				is_visted[new_pos.get_y()][new_pos.get_x()] = true;

				if (get_position().get_x() == curr_x + move_vector_x[i] &&
					get_position().get_y() == curr_y + move_vector_y[i])
				{
					switch (i) { // OPOSITE TODO FUNC OUT
					case 0:
						set_direction(Entity::Direction::RIGHT);
						return;
					case 1:
						set_direction(Entity::Direction::UP);
						return;
					case 2:
						set_direction(Entity::Direction::LEFT);
						return;
					case 3:
						set_direction(Entity::Direction::DOWN);
						return;
					}
				}
				moving_queue.push(new_pos);
			}
		}
	}
}
bool Ghosts::is_invalid_place(const Position& next_pos) {
    return ((board.get_cell(next_pos) == (unsigned char)Board::WALL)||(is_my_teleporting(next_pos)));
}
