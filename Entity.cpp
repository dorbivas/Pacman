#include "Entity.h"

void Entity::print_move(const Position pos, Shape shape, bool color_mode, int score, int souls) const {
	display_score_souls(score, souls, color_mode);
	if (color_mode)
	{
		if (shape == P)
			board.set_color(WHITE);
		else if (shape == T)
			board.set_color(LIGHTBLUE);
		else if (shape == PACMAN)
			board.set_color(YELLOW);
		else // (c == GHOST_ICON)
			board.set_color(RED);
	}
	goto_xy(pos.get_x(), pos.get_y());
	if (shape != 0)
		cout << char(shape);//TIODO MAYBE SET CELL 
}
void Entity::display_score_souls(int score, int souls, bool color_mode) const {
	goto_xy(7, 23);
	if (color_mode)
		board.set_color(LIGHTGREEN);
	cout << score;
	goto_xy(7, 24);
	if (color_mode)
		board.set_color(RED);
	cout << souls;
}
