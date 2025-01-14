#include "GameLayer.h"
#include "CharacterSelectionLayer.h"

#include "Tucan.h"
#include "Capibara.h"
#include "Mono.h"
#include "Gaviota.h"
#include "VineTile.h"
#include "WaterTile.h"
#include "WaterTileFondo.h"
#include "BoxTile.h"
#include "Elefante.h"
#include "Coche.h"
#include "TunnelTile.h"
#include "TeddyTile.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	space = new Space(1);
	firstCharacterIcon = new CharacterIcon("", WIDTH * 0.1, HEIGHT * 0.1, 80, 80, game);
	secondCharacterIcon = new CharacterIcon("", WIDTH * 0.23, HEIGHT * 0.13, 60, 60, game);
	thirdCharacterIcon = new CharacterIcon("", WIDTH * 0.36, HEIGHT * 0.13, 60, 60, game);

	osito1 = new CharacterIcon("", WIDTH * 0.76, HEIGHT * 0.13, 35, 35, game);
	osito2 = new CharacterIcon("", WIDTH * 0.83, HEIGHT * 0.13, 35, 35, game);
	osito3 = new CharacterIcon("", WIDTH * 0.90, HEIGHT * 0.13, 35, 35, game);

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	forbiddenSymbol = new ForbiddenSymbol(WIDTH * 0.9, HEIGHT * 0.9, game);
}

void GameLayer::firstPrepareGameLayer() {
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	getMainCharacterForLevel();
	init();
}


void GameLayer::init() {
	space = new Space(1);

	addCharactersToSpace();

	scrollX = 0;
	tiles.clear();
	waterTiles.clear();
	vineTiles.clear();
	boxTiles.clear();
	collectables.clear();
	enemies.clear();

	background = new Background("res/fondo_0.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	if (!takenCheckpoint) {
		numCollectables = 0;
		numeroOsosCargados = 0;
		dibujarOsitos(numCollectables);
	}
	else {
		for (int i = 0; i < 3; i++) {
			collectablesTaken[i] = collectableTakenAtCheckpoint[i];
		}
		numeroOsosCargados = 0;
		numCollectables = numCollectablesAtCheckpoint;
		dibujarOsitos(numCollectablesAtCheckpoint);
	}

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
		player->y = checkpoint->y - player->height/2;
	}
	for (Player* character : characters) {
		if (character == nullptr) {
			game->layer = game->characterSelectionLayer;
			break;
		}
	}
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case '1': {
		if (player == nullptr)
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
	case 'A': {
		Tile* tile = new Tile("res/andamio.png", x, y, game);
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
		checkpoint = new Tile("res/checkpoint.png", x, y,29, 70, game);
		// modificación para empezar a contar desde el suelo.
		checkpoint->y = checkpoint->y - checkpoint->height / 2;
		space->addDynamicActor(checkpoint);
		break;
	}
	case 'L': {
		VineTile* tile = new VineTile("derecha", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		vineTiles.push_back(tile);
		space->addDynamicActor(tile);
		break;
	}
	case 'V': {
		VineTile* tile = new VineTile("izquierda", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		vineTiles.push_back(tile);
		space->addDynamicActor(tile);
		break;
	}
	case 'W': {
		Tile* tile = new WaterTile(x, y, game);
		Tile* fondoTile = new WaterTileFondo(x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		fondoTile->y = fondoTile->y - fondoTile->height / 2;
		tiles.push_back(fondoTile);
		waterTiles.push_back(tile);
		space->addDynamicActor(tile);
		space->addDynamicActor(fondoTile);
		break;
	}
	case 'B': {
		BoxTile* tile = new BoxTile(x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		boxTiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '@': {
		Tile* tile = new Tile("res/grass.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '8': {
		Tile* tile = new Tile("res/dirt.png", x, y, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'T': {
		Tile* tile = new Tile("res/tree.png", x, y, 105, 182, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addDynamicActor(tile);
		break;
	}
	case 'K': {
		Tile* tile = new Tile("res/banco.png", x, y, 89, 55, game);
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addDynamicActor(tile);
		break;
	}
	case 'G': {
		Enemy* enemy = new Gaviota(x, y, game);
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'R': {
		Enemy* enemy = new Coche(x, y, game);
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'U': {
		TunnelTile* tile = new TunnelTile("izquierda", x, y, game, this);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		tunnelTilesL.push_back(tile);
		space->addDynamicActor(tile);
		break;
	}
	case 'D': {
		TunnelTile* tile = new TunnelTile("derecha", x, y, game, this);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		tunnelTilesD.push_back(tile);
		space->addDynamicActor(tile);
		break;
	}
	case 'C': {
		numeroOsosCargados++;
		if (collectablesTaken[numeroOsosCargados-1] && takenCheckpoint)
			break;
		Tile* tile = new TeddyTile(x, y, game, numeroOsosCargados);
		tile->y = tile->y - tile->height / 2;
		collectables.push_back(tile);
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
		player->moveDown();
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
		// Vaciamos la lista de personajes
		for (int i = 0; i < 3; i++) {
			characters[i] = nullptr;
		}
		nextCharacter = 1;
		getMainCharacterForLevel();
		// Abrimos la pantalla de selección de personajes
		game->characterSelectionLayer->init();
		game->layer = game->characterSelectionLayer;
		if (game->currentLevel > game->finalLevel) {
			game->layer = game->menuFinalLayer;
			return;
		}
		
		pause = true;
		takenCheckpoint = false;
		// vaciamos los personajes
		for (int i = 0; i < 3; i++) {
			characters[i] = nullptr;
		}

		// Se deselecciona el personaje
		player = nullptr;

		// Seleccionamos al personaje "protagonista" del nivel
		getMainCharacterForLevel();
		
		init();
	}

	// Obtenido el checkpoint
	if (checkpoint->isOverlap(player) && takenCheckpoint == false) {
		takenCheckpoint = true;
		// Cuando se coge el checkpoint se guarda el estado de los collecionables en ese momento
		for (int i = 0; i < 3; i++) {
			collectableTakenAtCheckpoint[i] = collectablesTaken[i];
		}
		numeroOsosCargadosAtCheckpoint = numeroOsosCargados;
		numCollectablesAtCheckpoint = numCollectables;
	}

	//Colisiones con el agua
	for (auto const& water : waterTiles) {
		if (player->getType()=="Capibara") {
			Capibara* capi = (Capibara*)player;
			if (water->isOverlap(player)) {
				capi->canSwim = true;
				break;
			}
			else {
				capi->canSwim = false;
			}
		}
		else {
			if (water->isOverlap(player)) {
				init(); //Si no es una capibara, no puede nadar y muere
				break;
			}
		}
	}

	//Colisiones con las cajas
	list<BoxTile*> deleteCajas;
	for (auto const& caja : boxTiles) {
		if (caja->isOverlap(player)) {
			Elefante* elefante = (Elefante*)player;
			if (player->getType() == "Elefante" && elefante->breaking) {
				caja->state = caja->stateBreaking; // 1 = stateBreaking
			}
		}
	}

	for (auto const& caja : boxTiles) {
		if (caja->state == caja->stateBroken) {
			deleteCajas.push_back(caja); 
		}
	}
	// Eliminar las cajas que los elefantes rompen
	for (auto const& caja : deleteCajas) {
		boxTiles.remove(caja);
		space->removeStaticActor(caja);
	}
	deleteCajas.clear();

	for (auto const& caja : deleteCajas) {
			boxTiles.remove(caja);
	}
	deleteCajas.clear();

	// Jugador se cae
	if (player->y > HEIGHT + 80) {
		init();
	}

	player->update();
	space->update();
	background->update();

	
	
	// Colisión con lianas
	for (auto const& vineTile : vineTiles) {
		if (player->getType() == "Mono") {
			Mono* mono = (Mono*)player;
			if (player->isOverlap(vineTile)) {
				mono->canClimb = true;
				break;
			}
			else {
				mono->canClimb = false;
			}

		}
	}

	for (auto const& enemy : enemies) {
		enemy->update();
	}

	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			init();
			return;
		}
	}

	for (auto const& tunnel : tunnelTilesD) {
		tunnel->update();
	}

	for (auto const& box : boxTiles) {
		box->update();
	}

	//// Colisiones , Player - Collectable
	list<Tile*> deleteCollectables;
	for (auto const& collectable : collectables) {
		if (collectable->isOverlap(player)) {
			deleteCollectables.push_back(collectable);
			collectablesTaken[((TeddyTile*)collectable)->getNumeroOso() - 1] = true;
			numCollectables++;
			dibujarOsitos(numCollectables);
		}
	}

	for (auto const& collectable : deleteCollectables) {
		collectables.remove(collectable);
	}
	
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

	citySign->draw(scrollX);
	checkpoint->draw(scrollX);
	player->draw(scrollX);
	for (auto const& tile : waterTiles) {
		tile->draw(scrollX);
	}
	for (auto const& tile : boxTiles) {
		tile->draw(scrollX);
	}
	for (auto const& tile : tunnelTilesD) {
		tile->draw(scrollX);
	}
	for (auto const& tile : tunnelTilesL) {
		tile->draw(scrollX);
	}
	for (auto const& tile : collectables) {
		tile->draw(scrollX);
	}

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX);
	}

	firstCharacterIcon->draw();
	secondCharacterIcon->draw();
	thirdCharacterIcon->draw();
	forbiddenSymbol->draw();

	osito1->draw();
	osito2->draw();
	osito3->draw();

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
		case SDLK_SPACE: // romper caja
			player->breakBox();
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

			switch (i) {
			case 0:
				firstCharacterIcon->setIcon(character->getBigIcon());
				break;
			case 1:
				secondCharacterIcon->setIcon(character->getSmallIcon());
				break;
			case 2:
				thirdCharacterIcon->setIcon(character->getSmallIcon());
				break;
			}

			break;
		}
	}
}

void GameLayer::changeCharacter() {
	int nextPlayerHeight = characters[nextCharacter]->height;

	int x = player->x;
	int y = player->y - nextPlayerHeight/2;
	characters[nextCharacter]->setLocation(x, y);
	if (space->canTransformInto(characters[nextCharacter], x, y)) {
		

		firstCharacterIcon->setIcon(characters[nextCharacter]->getBigIcon());
		thirdCharacterIcon->setIcon(player->getSmallIcon());

		player = characters[nextCharacter];
		player->setLocation(x, y);
		player->setVY(0);
		nextCharacter++;
		if (nextCharacter > 2) {
			nextCharacter = 0;
		}

		secondCharacterIcon->setIcon(characters[nextCharacter]->getSmallIcon());
	}
	else {
		forbiddenSymbol->show();
	}
}

void GameLayer::getMainCharacterForLevel() {
	switch (game->currentLevel) {
	case 0:
		((CharacterSelectionLayer*)(game->characterSelectionLayer))->selectMono();
		break;
	case 1:
		((CharacterSelectionLayer*)(game->characterSelectionLayer))->selectCapibara();
		break;
	case 2:
		((CharacterSelectionLayer*)(game->characterSelectionLayer))->selectTucan();
		break;
	}
}

void GameLayer::addCharactersToSpace() {
	for (int i = 0; i < 3; i++) {
		if (characters[i] != nullptr) {
			space->addDynamicActor(characters[i]);
		}
	}
}

void GameLayer::dibujarOsitos(int numCollectables) {
	switch (numCollectables) {
	case 0:
		osito1->setIcon("res/Tile_teddy_transparente.png");
		osito2->setIcon("res/Tile_teddy_transparente.png");
		osito3->setIcon("res/Tile_teddy_transparente.png");
		break;
	case 1:
		osito1->setIcon("res/Tile_teddy.png");
		osito2->setIcon("res/Tile_teddy_transparente.png");
		osito3->setIcon("res/Tile_teddy_transparente.png");
		break;
	case 2:
		osito1->setIcon("res/Tile_teddy.png");
		osito2->setIcon("res/Tile_teddy.png");
		osito3->setIcon("res/Tile_teddy_transparente.png");
		break;
	case 3:
		osito1->setIcon("res/Tile_teddy.png");
		osito2->setIcon("res/Tile_teddy.png");
		osito3->setIcon("res/Tile_teddy.png");
		break;
	}
}