#include "MenuFinalLayer.h"

MenuFinalLayer::MenuFinalLayer(Game* game)
	: Layer(game) {
	init();
}

void MenuFinalLayer::init() {
	// Fondo normal, sin velocidad
	// TODO cambiar fondo
	background = new Background("res/imagen_final_juego.png", WIDTH * 0.5, HEIGHT * 0.5, game);
	button = new Actor("res/Boton_salir.png", WIDTH * 0.5, HEIGHT * 0.33, 232, 72, game);
}

void MenuFinalLayer::draw() {
	background->draw();
	button->draw();

	SDL_RenderPresent(game->renderer); // Renderiza NO PUEDE FALTAR
}

void MenuFinalLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
	}
}

void MenuFinalLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (button->containsPoint(motionX, motionY)) {
			game->loopActive = false;
		}
	}
}