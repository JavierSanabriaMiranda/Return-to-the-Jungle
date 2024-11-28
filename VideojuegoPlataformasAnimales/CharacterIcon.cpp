#include "CharacterIcon.h"

CharacterIcon::CharacterIcon(string img, float x, float y, int width, int height, Game* game)
	: Actor(img, x, y, width, height, game) {
}

void CharacterIcon::setIcon(string img) {
	texture = game->getTexture(img);
}