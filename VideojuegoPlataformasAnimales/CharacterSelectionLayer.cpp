#include "CharacterSelectionLayer.h"
#include "Tucan.h"
#include "Mono.h"
#include "Capibara.h"
#include "Serpiente.h"


CharacterSelectionLayer::CharacterSelectionLayer(Game* game, GameLayer* gameLayer)
	: Layer(game) {
	init();
	gamePad = SDL_GameControllerOpen(0);
	currentGameLayer = gameLayer;
}

void CharacterSelectionLayer::init() {
	// Fondo normal, sin velocidad
	// TODO cambiar fondo
	setFondo("res/Fondo_seleccion_personaje.jpg");
	buttonTucan = new Actor("res/seleccion_tucan.png", WIDTH * 0.2, HEIGHT * 0.4, 100, 100, game);
	buttonElefante = new Actor("res/seleccion_tucan.png", WIDTH * 0.5, HEIGHT * 0.4, 100, 100, game);
	buttonSerpiente = new Actor("res/Serpiente.png", WIDTH * 0.8, HEIGHT * 0.4, 82, 25, game);
	buttonCapibara = new Actor("res/seleccion_capibara.png", WIDTH * 0.35, HEIGHT * 0.75, 100, 100, game);
	buttonMono = new Actor("res/seleccion_mono.png", WIDTH * 0.65, HEIGHT * 0.75, 100, 100, game);

	selectedCapibara = false;
	selectedElefante = false;
	selectedMono = false;
	selectedSerpiente = false;
	selectedTucan = false;
}

void CharacterSelectionLayer::setFondo(string fileName) {
	background = new Background(fileName, WIDTH * 0.5, HEIGHT * 0.5, game);
}

void CharacterSelectionLayer::draw() {
	background->draw();
	buttonTucan->draw();
	buttonElefante->draw();
	buttonSerpiente->draw();
	buttonCapibara->draw();
	buttonMono->draw();

	SDL_RenderPresent(game->renderer); // Renderiza NO PUEDE FALTAR
}

void CharacterSelectionLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}
		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
	}

	//procesar controles, solo tiene uno
	if (controlContinue) {
		// Cambia la capa
		game->layer = game->gameLayer;
		controlContinue = false;
	}
}

void CharacterSelectionLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE: // derecha
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		}
	}
}

void CharacterSelectionLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;

	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (buttonTucan->containsPoint(motionX, motionY)) {
			selectTucan();
		}
		if (buttonCapibara->containsPoint(motionX, motionY)) {
			selectCapibara();
		}
		if (buttonElefante->containsPoint(motionX, motionY)) {
			selectElefante();
		}
		if (buttonSerpiente->containsPoint(motionX, motionY)) {
			selectSerpiente();
		}
		if (buttonMono->containsPoint(motionX, motionY)) {
			selectMono();
		}
	}
}

void CharacterSelectionLayer::gamePadToControls(SDL_Event event) {
	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);

	if (buttonA) {
		controlContinue = true;
	}
}

void CharacterSelectionLayer::selectTucan() {
	if (selectedTucan == false) {
		currentGameLayer->addCharacter(new Tucan(0, 0, game));
		charactersSelected++;
		selectedTucan = true;
		buttonTucan = new Actor("res/tucan_escogido.png", WIDTH * 0.2, HEIGHT * 0.4, 100, 100, game);
		if (charactersSelected == 3) {
			controlContinue = true;
			charactersSelected = 1;
		}
	}
}

void CharacterSelectionLayer::selectElefante() {
	if (selectedElefante == false) {
		//currentGameLayer->addCharacter(new Tucan(0, 0, game));
		charactersSelected++;
		selectedElefante = true;
		if (charactersSelected == 3) {
			controlContinue = true;
			charactersSelected = 1;
		}
	}
}

void CharacterSelectionLayer::selectSerpiente() {
	if (selectedSerpiente == false) {
		currentGameLayer->addCharacter(new Serpiente(0, 0, game));
		charactersSelected++;
		selectedSerpiente = true;
		if (charactersSelected == 3) {
			controlContinue = true;
			charactersSelected = 1;
		}
	}
}

void CharacterSelectionLayer::selectCapibara() {
	if (selectedCapibara == false) {
		currentGameLayer->addCharacter(new Capibara(0, 0, game));
		charactersSelected++;
		selectedCapibara = true;
		if (charactersSelected == 3) {
			controlContinue = true;
			charactersSelected = 1;
		}
	}
}

void CharacterSelectionLayer::selectMono() {
	if (selectedMono == false) {
		currentGameLayer->addCharacter(new Mono(0, 0, game));
		charactersSelected++;
		selectedMono = true;
		if (charactersSelected == 3) {
			controlContinue = true;
			charactersSelected = 1;
		}
	}
}