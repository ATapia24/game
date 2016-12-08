#ifndef EDITOR_OBJECT_H
#define EDITOR_OBJECT_H

#include <SFML/Graphics.hpp>
#include "misc.h"
#include <iostream>
#include <cmath>
#include <string>

enum ObjType
{
	RECTANGLE,
	CIRCLE,
	STATIC_OBJ,
	DYNAMIC_OBJ,
	N_TYPES,
	DELETED
};

class EditorObject
{
private:
	
public:
	ObjType type;
	sf::Sprite sprite;
	sf::RectangleShape rectangle;
	sf::CircleShape circle;
	std::string textureName;
	
	//transform object
	void moveUp(float speed);
	void moveDown(float speed);
	void moveLeft(float speed);
	void moveRight(float speed);
	void rotateLeft(float speed);
	void rotateRight(float speed);
	void growTop(float size);
	void growBottom(float size);
	void growLeft(float size);
	void growRight(float size);
	void shrinkLeft(float size);
	void shrinkRight(float size);
	void shrinkTop(float size);
	void shrinkBottom(float size);
	void originUpdate();

	EditorObject();
	~EditorObject();
};

#endif