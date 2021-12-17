#include "Entity.h"

void Entity::print_move(const Position pos, Shape shape, bool color_mode, int score, int souls) const {
	//display_score_souls(score, souls, color_mode);
	if (color_mode)
	{
		if (shape == P)
			board.set_color((int)Board::Color::WHITE);
		else if (shape == T)
			board.set_color((int)Board::Color::LIGHTBLUE);
		else if (shape == PACMAN)
			board.set_color((int)Board::Color::YELLOW);
		else // (c == GHOST_ICON)
			board.set_color((int)Board::Color::RED);
	}
	goto_xy(pos.get_x(), pos.get_y());
	if (shape != 0)
		cout << char(shape);//TIODO MAYBE SET CELL 
}

bool Entity::is_invalid_place(const Position& next_pos) {
	return (board.get_cell(next_pos) == (unsigned char)Board::WALL);
}
