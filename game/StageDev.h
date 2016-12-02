#include "Stage.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <SFML\Graphics.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <stdio.h>
#include <time.h>
#include <typeinfo>

#include "StageManager.h"
#include "WindowMgr.h"
#include "misc.h"
#include "Player.h"
#include "NativePosition.h"
#include "Entity.h"
#include "TextureManager.h"
#include "Box2D\Box2D.h"
#include "KeyManager.h"
#include "Map.h"
#include "EditorObject.h"
#include "Solid.h"
#include "ViewBlocker.h"
#include "Actor.h"
#include "PathFinder.h"

class StageDev : public Stage, public b2ContactListener
{
private:
	sf::Texture bgText;
	sf::RectangleShape bg;
	TextureManager textures;
	std::vector<Entity*> objects;
	Player player;
	
	ViewBlocker* vb;
	Solid* walls;
	int n_walls;

	b2World* world;
	Map map;

	PathFinder pathf;
	std::vector<sf::RectangleShape> grid;
	sf::VertexArray* va;
	Timer t1, t2;
	Actor bot;
	Key waypoint;

	sf::Texture lightTexture;
	sf::Sprite lightSprite, l2;
	sf::RenderTexture lightmapTexture;
	sf::Sprite lightmap;

public:
	StageDev();
	~StageDev();
	StageDev(StageManager* stageManager, WindowMgr* _window);
	void load();
	void unload();
	void update();
	void draw();
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};
