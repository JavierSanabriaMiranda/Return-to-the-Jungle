#include "Enemy.h"

Enemy::Enemy(string img, float x, float y, int width, int height, Game* game)
	: Actor(img, x, y, width, height, game) {

	vx = 1;
	vy = 3;

	orientation = game->orientationRight;
	state = game->stateMoving;

	state = game->stateMoving;
}

void Enemy::update() {
	// Do nothing
}

void Enemy::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}
