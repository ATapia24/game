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
#include "MenuList.h"
#include "MenuSelect.h"
#include "misc.h"
#include "Player.h"
#include "NativePosition.h"
#include "Entity.h"
#include "Floor.h"
#include "Box2D\Box2D.h"

class StageDev : public Stage, public b2ContactListener
{
private:
	sf::Texture bgText;
	sf::Sprite bg;

	Player player;
	Entity* bots;
	int n_bots;
	Floor floor, bottom, stop, bullet;
	Floor *box;
	//Entity bullet;

	//tmp
	bool q_rel, a_rel, d_rel, b_c, q_rel2, a_rel2, d_rel2, b_c2;

	b2World* world;
	const float SCALE = 100;
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
