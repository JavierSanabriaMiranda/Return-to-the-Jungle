#include "Enemy.h"

Enemy::Enemy(string img, float x, float y, int width, int height, Game* game)
	: Actor(img, x, y, 40, 25, game) {

	vx = 1;
	vy = 3;

	/*vxIntelligence = -1;*/
	/*vx = vxIntelligence;*/
	orientation = game->orientationRight;
	state = game->stateMoving;

	state = game->stateMoving;

	/*aMovingRight = new Animation("res/Gaviota_volando_derecha.png", width, height,
		350, 35, 6, 6, true, game);

	aMovingLeft = new Animation("res/Gaviota_volando_izquierda.png", width, height,
		350, 35, 6, 6, true, game);

	animation = aMovingRight;*/
}

void Enemy::update() {
	// Do nothing
}

void Enemy::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}

//void Enemy::impacted() {
//	if (state != game->stateDying) {
//		state = game->stateDying;
//	}
//}
