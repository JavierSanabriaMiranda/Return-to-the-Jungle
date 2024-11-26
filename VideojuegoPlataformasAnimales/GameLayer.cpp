#include "GameLayer.h"
#include "Tucan.h"
#include "VineTile.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;

	space = new Space(1);
	getMainCharacterForLevel();
	init();
}


void GameLayer::init() {

	scrollX = 0;
	tiles.clear();

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	background = new Background("res/fondo_0.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);



	loadMap(to_string(game->currentLevel));
}

void GameLayer::loadMap(string name) {

	string mapName = "res/" + name + ".txt";
	string backgroundName = "res/fondo_" + name + ".jpg";

	char character;
	string line;
	ifstream streamFile(mapName.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
	// Cargar fondo
	background = new Background(backgroundName, WIDTH * 0.5, HEIGHT * 0.5, -1, game);

	if (takenCheckpoint) {
		player->x = checkpoint->x;
		player->y = checkpoint->y;
	}
	// TODO cambiar de sitio
	game->layer = game->characterSelectionLayer;
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case '1': {
		player = characters[0];
		player->setLocation(x, y);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/Suelo_ciudad.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'S': {
		citySign = new Actor("res/Cartel.png", x, y, 45, 53, game);
		// modificación para empezar a contar desde el suelo.
		citySign->y = citySign->y - citySign->height / 2;
		space->addDynamicActor(citySign); // Realmente no hace falta
		break;
	}
	case '0': {
		checkpoint = new Tile("res/checkpoint.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		checkpoint->y = checkpoint->y - checkpoint->height / 2;
		space->addDynamicActor(checkpoint);
		break;
	}
	case 'L': {
		Tile* tile = new VineTile( x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addDynamicActor(tile);
		break;
	}

	}
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		// Cambio automático de input

		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
	}
	//procesar controles
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {

	}
	else if (controlMoveY < 0) {
		player->jump();
	}
	else {

	}



}

void GameLayer::update() {
	if (pause) {
		return;
	}

	// Nivel superado
	if (citySign->isOverlap(player)) {
		game->currentLevel++;
		game->layer = game->characterSelectionLayer;
		if (game->currentLevel > game->finalLevel) {
			game->currentLevel = 0;
			message = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
				WIDTH, HEIGHT, game);
		}
		
		pause = true;
		takenCheckpoint = false;
		// vaciamos los personajes
		for (int i = 0; i < 3; i++) {
			characters[i] = nullptr;
		}
		// Seleccionamos al personaje "protagonista" del nivel
		getMainCharacterForLevel();
		
		init();
	}

	// Obtenido el checkpoint
	if (checkpoint->isOverlap(player)) {
		takenCheckpoint = true;
	}


	// Jugador se cae
	if (player->y > HEIGHT + 80) {
		init();
	}

	space->update();
	background->update();
	player->update();

	//for (auto const& collectable : collectables) {
	//	collectable->update();
	//}

	//for (auto const& enemy : enemies) {
	//	enemy->update();
	//}

	//// Colisiones
	//for (auto const& enemy : enemies) {
	//	if (player->isOverlap(enemy)) {
	//		player->loseLife();
	//		if (player->lifes <= 0) {
	//			init();
	//			return;
	//		}
	//	}
	//}

	//// Colisiones , Player - Collectable
	//list<Collectable*> deleteCollectables;
	//for (auto const& collectable : collectables) {
	//	if (collectable->isOverlap(player)) {
	//		bool cInList = std::find(deleteCollectables.begin(),
	//			deleteCollectables.end(),
	//			collectable) != deleteCollectables.end();

	//		if (!cInList) {
	//			deleteCollectables.push_back(collectable);
	//		}
	//		numCollectables++;
	//		textCollectables->content = to_string(numCollectables);
	//	}
	//}

	//for (auto const& collectable : deleteCollectables) {
	//	collectables.remove(collectable);
	//}
	//deleteCollectables.clear();

	
}

void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}

	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}
}


void GameLayer::draw() {
	calculateScroll();

	background->draw();
	for (auto const& tile : tiles) {
		tile->draw(scrollX);
	}

	//for (auto const& collectable : collectables) {
	//	collectable->draw(scrollX);
	//}

	citySign->draw(scrollX);
	checkpoint->draw(scrollX);
	player->draw(scrollX);
	//for (auto const& enemy : enemies) {
	//	enemy->draw(scrollX);
	//}

	//backgroundPoints->draw();
	//textPoints->draw();

	//backgroundCollectables->draw();
	//textCollectables->draw();



	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_c: // cambiar personaje
			changeCharacter();
			break;
		}


	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		}

	}

}
void GameLayer::mouseToControls(SDL_Event event) {
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
	}
}

void GameLayer::addCharacter(Player* character) {
	for (int i = 0; i < 3; i++) {
		if (characters[i] == nullptr) {
			characters[i] = character;
			space->addDynamicActor(character);
			break;
		}
	}
}

void GameLayer::changeCharacter() {
	int x = player->x;
	int y = player->y;

	player = characters[nextCharacter];
	player->setLocation(x, y);
	nextCharacter++;
	if (nextCharacter > 2) {
		nextCharacter = 0;
	}
}

void GameLayer::getMainCharacterForLevel() {
	switch (game->currentLevel) {
	case 0:
		addCharacter(new Tucan(0, 0, game));
		break;
	case 1:
		addCharacter(new Tucan(0, 0, game));
		break;
	case 2:
		addCharacter(new Tucan(0, 0, game));
		break;
	}
}

