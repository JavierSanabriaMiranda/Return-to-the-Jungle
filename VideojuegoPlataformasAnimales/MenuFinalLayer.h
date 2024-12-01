#pragma once
#include "Layer.h"
#include "Actor.h"
#include "Background.h"

class MenuFinalLayer : public Layer
{
public:
	MenuFinalLayer(Game* game);
	void init() override;
	void draw() override;
	void processControls() override;
	void mouseToControls(SDL_Event event);
	Background* background;
	Actor* button;
};

