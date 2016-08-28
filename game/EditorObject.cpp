#include "stdafx.h"
#include "EditorObject.h"


EditorObject::EditorObject()
{
}


EditorObject::~EditorObject()
{
}

//MOVE UP
void EditorObject::moveUp(float speed)
{
	speed *= -1;
	
	switch (type)
	{
	case ObjType::RECTANGLE:
		rectangle.move(sf::Vector2f(0, speed));
		break;

	case ObjType::CIRCLE:
		circle.move(sf::Vector2f(0, speed));
		break;

	case ObjType::STATIC_OBJ:
		rectangle.move(sf::Vector2f(0, speed));
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}

//MOVE DOWN
void EditorObject::moveDown(float speed)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		rectangle.move(sf::Vector2f(0, speed));
		break;

	case ObjType::CIRCLE:
		circle.move(sf::Vector2f(0, speed));
		break;

	case ObjType::STATIC_OBJ:
		rectangle.move(sf::Vector2f(0, speed));
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}

//MOVE LEFT
void EditorObject::moveLeft(float speed)
{
	speed *= -1;

	switch (type)
	{
	case ObjType::RECTANGLE:
		rectangle.move(sf::Vector2f(speed, 0));
		break;

	case ObjType::CIRCLE:
		circle.move(sf::Vector2f(speed, 0));
		break;

	case ObjType::STATIC_OBJ:
		rectangle.move(sf::Vector2f(speed, 0));
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}

//MOVE RIGHT
void EditorObject::moveRight(float speed)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		rectangle.move(sf::Vector2f(speed, 0));
		break;

	case ObjType::CIRCLE:
		circle.move(sf::Vector2f(speed, 0));
		break;

	case ObjType::STATIC_OBJ:
		rectangle.move(sf::Vector2f(speed, 0));
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}

//TODO: ROTATE ON CENTER POINT
//ROTATE LEFT
void EditorObject::rotateLeft(float speed)
{
	speed *= -1;
	switch (type)
	{
	case ObjType::RECTANGLE:
		rectangle.rotate(speed);
		break;

	case ObjType::CIRCLE:
		circle.rotate(speed);
		break;

	case ObjType::STATIC_OBJ:
		rectangle.rotate(speed);
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}

//ROTATE RIGHT
void EditorObject::rotateRight(float speed)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		rectangle.rotate(speed);
		break;

	case ObjType::CIRCLE:
		rectangle.rotate(speed);
		break;

	case ObjType::STATIC_OBJ:
		rectangle.rotate(speed);
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}

//GROW TOP
void EditorObject::growTop(float size)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
	{
		rectangle.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y + size));
		rectangle.setOrigin(sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
		rectangle.setPosition(misc::pointLocation(rectangle.getPosition(), -rectangle.getRotation() * DEG2RAD + PIh, size / 2));
		break;
	}
	case ObjType::CIRCLE:
		break;

	case ObjType::STATIC_OBJ:
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}

}

//GROW BOTTOM
void EditorObject::growBottom(float size)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
	{
		rectangle.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y + size));
		rectangle.setOrigin(sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
		rectangle.setPosition(misc::pointLocation(rectangle.getPosition(), -rectangle.getRotation() * DEG2RAD - PIh, size / 2));
		break;
	}
	case ObjType::CIRCLE:
		break;

	case ObjType::STATIC_OBJ:
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}

}

//GROW LEFT
void EditorObject::growLeft(float size)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		rectangle.setSize(sf::Vector2f(rectangle.getSize().x + size, rectangle.getSize().y));
		rectangle.setOrigin(sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
		rectangle.setPosition(misc::pointLocation(rectangle.getPosition(), -rectangle.getRotation() * DEG2RAD + PI, size / 2));
		break;

	case ObjType::CIRCLE:
		break;

	case ObjType::STATIC_OBJ:
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}

//GROW RIGHT
void EditorObject::growRight(float size)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		rectangle.setSize(sf::Vector2f(rectangle.getSize().x + size, rectangle.getSize().y));
		rectangle.setOrigin(sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
		rectangle.setPosition(misc::pointLocation(rectangle.getPosition(), -rectangle.getRotation() * DEG2RAD, size / 2));
		break;

	case ObjType::CIRCLE:
		break;

	case ObjType::STATIC_OBJ:
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}

}

//SHRINK LEFT
void EditorObject::shrinkLeft(float size)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		if (rectangle.getSize().x > 0)
		{
			rectangle.setSize(sf::Vector2f(rectangle.getSize().x - size, rectangle.getSize().y));
			rectangle.setOrigin(sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
			rectangle.setPosition(misc::pointLocation(rectangle.getPosition(), -rectangle.getRotation() * DEG2RAD, size / 2));
		}
		break;

	case ObjType::CIRCLE:
		break;

	case ObjType::STATIC_OBJ:

		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}

}

//SHRINK RIGHT
void EditorObject::shrinkRight(float size)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		if (rectangle.getSize().x > 0)
		{
			rectangle.setSize(sf::Vector2f(rectangle.getSize().x - size, rectangle.getSize().y));
			rectangle.setOrigin(sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
			rectangle.setPosition(misc::pointLocation(rectangle.getPosition(), -rectangle.getRotation() * DEG2RAD - PI, size / 2));
		}
		break;

	case ObjType::CIRCLE:
		break;

	case ObjType::STATIC_OBJ:

		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}

}

//SHRINK TOP
void EditorObject::shrinkTop(float size)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		if (rectangle.getSize().y > 0)
		{
			rectangle.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y - size));
			rectangle.setOrigin(sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
			rectangle.setPosition(misc::pointLocation(rectangle.getPosition(), -rectangle.getRotation() * DEG2RAD - PIh, size / 2));
		}
		break;

	case ObjType::CIRCLE:
		break;

	case ObjType::STATIC_OBJ:

		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}

//SHRINK BOTTOM
void EditorObject::shrinkBottom(float size)
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		if (rectangle.getSize().y > 0)
		{
			rectangle.setSize(sf::Vector2f(rectangle.getSize().x, rectangle.getSize().y - size));
			rectangle.setOrigin(sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
			rectangle.setPosition(misc::pointLocation(rectangle.getPosition(), -rectangle.getRotation() * DEG2RAD + PIh, size / 2));
		}
		break;

	case ObjType::CIRCLE:
		break;

	case ObjType::STATIC_OBJ:
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}

//ORIGIN UPDATE
void EditorObject::originUpdate()
{
	switch (type)
	{
	case ObjType::RECTANGLE:
		rectangle.setOrigin(sf::Vector2f(rectangle.getSize().x / 2, rectangle.getSize().y / 2));
		rectangle.setPosition(sf::Vector2f((rectangle.getSize().x / 2) + rectangle.getPosition().x, (rectangle.getSize().y / 2) + rectangle.getPosition().y));
		break;

	case ObjType::CIRCLE:
		break;

	case ObjType::STATIC_OBJ:
		break;

	case ObjType::DYNAMIC_OBJ:
		break;
	}
}