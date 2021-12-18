#include "Pacman.h"

Pacman::Pacman(int souls, int direction, Position& pos, int score) {
	this->souls = souls;
	this->score = score;
	this->direction = direction;
	this->pos = pos;
}
int Pacman::get_souls() const {
	return souls;
}
void Pacman::set_souls(int souls) {
	this->souls = souls;
}
void Pacman::decrease_soul() {
	souls--;
}
void Pacman::add_score(int new_val) {
	score=score+new_val;
}
int Pacman::get_score() const {
	return score;
}
bool Pacman::is_invalid_place(const Position& next_pos){
	return (board.get_cell(next_pos) == (unsigned char)Board::WALL);
}