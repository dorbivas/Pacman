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
void Pacman::set_score(int score) {
	this->score = score;
}
void Pacman::add_score() {
	score++;
}
int Pacman::get_score() const {
	return score;
}