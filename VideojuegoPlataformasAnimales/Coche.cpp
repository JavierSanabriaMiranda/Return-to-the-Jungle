#include "Coche.h"

Coche::Coche(float x, float y, Game* game)
	:Enemy("res/Coche.png", x, y, 100, 54, game) {

	vx = -1;

	// generamos numero aleatorio
	std::srand(std::time(0));

	// Generar número aleatorio entre 1 y 3
	int numero_aleatorio = (std::rand() % 3) + 1;
	std::string numero_str = std::to_string(numero_aleatorio); // Convertir int a string

	string name = "res/Coche" + numero_str + "_movimiento.png";

	aMovingLeft = new Animation(name, width, height,
		500, 67, 6, 4, true, game);

	animation = aMovingLeft;
}


void Coche::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();
	x = x + vx;
}
