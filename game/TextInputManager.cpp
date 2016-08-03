#include "stdafx.h"
#include "TextInputManager.h"

//CONSTRUCTOR
TextInputManager::TextInputManager()
{
	done = 0;
	cursor = 0;
	spaceKey = 32;
	enterKey = 13;
	backspaceKey = 127;
	capslockKey = 0x14;
	nullKey = 0;
	capsOffset = 32;
	keySetup();
	mode = TextInputMode::ALL;
}

//UPDATE
void TextInputManager::update()
{
	char key = determineKeypress();

	if (key != nullKey)
	{
		if (key == backspaceKey)
			eraseCharacter();
		else if (key == enterKey)
			done = 1;
		else
			newCharacter(key);
	}
}

//NEW CHARACTER
void TextInputManager::newCharacter(char key)
{
	text.resize(text.size() + 1);
	text[cursor] = key;
	cursor++;
}

//ERASE CHARACTER
void TextInputManager::eraseCharacter()
{
	if (text.size() > 0)
	{
		text.erase(text.begin() + cursor - 1);
		cursor--;
	}
}

//DETERMINE KEYPRESS
char TextInputManager::determineKeypress()
{
	char key = nullKey;

	//misc
	if (enter.getValue())
		return enterKey;
	else if (backspace.getValue())
		return backspaceKey;

	//letters
	if (mode == TextInputMode::ALL || mode == TextInputMode::LETTERS)
	{
		if (space.getValue())
			key = ' ';
		else if (a.getValue())
			key = 'a';
		else if (b.getValue())
			key = 'b';
		else if (c.getValue())
			key = 'c';
		else if (d.getValue())
			key = 'd';
		else if (e.getValue())
			key = 'e';
		else if (f.getValue())
			key = 'f';
		else if (g.getValue())
			key = 'g';
		else if (h.getValue())
			key = 'h';
		else if (i.getValue())
			key = 'i';
		else if (j.getValue())
			key = 'j';
		else if (k.getValue())
			key = 'k';
		else if (l.getValue())
			key = 'l';
		else if (m.getValue())
			key = 'm';
		else if (n.getValue())
			key = 'n';
		else if (o.getValue())
			key = 'o';
		else if (p.getValue())
			key = 'p';
		else if (q.getValue())
			key = 'q';
		else if (r.getValue())
			key = 'r';
		else if (s.getValue())
			key = 's';
		else if (t.getValue())
			key = 't';
		else if (u.getValue())
			key = 'u';
		else if (v.getValue())
			key = 'v';
		else if (w.getValue())
			key = 'w';
		else if (x.getValue())
			key = 'x';
		else if (y.getValue())
			key = 'y';
		else if (z.getValue())
			key = 'z';

		//caps offset
		if (GetKeyState(capslockKey) && misc::isLetter(key))
			key -= capsOffset;
	}
	
	//numbers
	if (mode == TextInputMode::ALL || mode == TextInputMode::NUMBERS)
	{
		if (n0.getValue())
			key = '0';
		else if (n1.getValue())
			key = '1';
		else if (n2.getValue())
			key = '2';
		else if (n3.getValue())
			key = '3';
		else if (n4.getValue())
			key = '4';
		else if (n5.getValue())
			key = '5';
		else if (n6.getValue())
			key = '6';
		else if (n7.getValue())
			key = '7';
		else if (n8.getValue())
			key = '8';
		else if (n9.getValue())
			key = '9';
	}

	return key;
}

//KEY SETUP
void TextInputManager::keySetup()
{
	using namespace sf;

	//misc
	space.set(Keyboard::Space, KeyType::SINGLE);
	enter.set(Keyboard::Return, KeyType::SINGLE);
	backspace.set(Keyboard::BackSpace, KeyType::SINGLE_COOLDOWN);

	//letter
	a.set(Keyboard::A, KeyType::SINGLE_COOLDOWN);
	b.set(Keyboard::B, KeyType::SINGLE_COOLDOWN);
	c.set(Keyboard::C, KeyType::SINGLE_COOLDOWN);
	d.set(Keyboard::D, KeyType::SINGLE_COOLDOWN);
	e.set(Keyboard::E, KeyType::SINGLE_COOLDOWN);
	f.set(Keyboard::F, KeyType::SINGLE_COOLDOWN);
	g.set(Keyboard::G, KeyType::SINGLE_COOLDOWN);
	h.set(Keyboard::H, KeyType::SINGLE_COOLDOWN);
	i.set(Keyboard::I, KeyType::SINGLE_COOLDOWN);
	j.set(Keyboard::J, KeyType::SINGLE_COOLDOWN);
	k.set(Keyboard::K, KeyType::SINGLE_COOLDOWN);
	l.set(Keyboard::L, KeyType::SINGLE_COOLDOWN);
	m.set(Keyboard::M, KeyType::SINGLE_COOLDOWN);
	n.set(Keyboard::N, KeyType::SINGLE_COOLDOWN);
	o.set(Keyboard::O, KeyType::SINGLE_COOLDOWN);
	p.set(Keyboard::P, KeyType::SINGLE_COOLDOWN);
	q.set(Keyboard::Q, KeyType::SINGLE_COOLDOWN);
	r.set(Keyboard::R, KeyType::SINGLE_COOLDOWN);
	s.set(Keyboard::S, KeyType::SINGLE_COOLDOWN);
	t.set(Keyboard::T, KeyType::SINGLE_COOLDOWN);
	u.set(Keyboard::U, KeyType::SINGLE_COOLDOWN);
	v.set(Keyboard::V, KeyType::SINGLE_COOLDOWN);
	w.set(Keyboard::W, KeyType::SINGLE_COOLDOWN);
	x.set(Keyboard::X, KeyType::SINGLE_COOLDOWN);
	y.set(Keyboard::Y, KeyType::SINGLE_COOLDOWN);
	z.set(Keyboard::Z, KeyType::SINGLE_COOLDOWN);

	//num
	n0.set(Keyboard::Num0, KeyType::SINGLE_COOLDOWN);
	n1.set(Keyboard::Num1, KeyType::SINGLE_COOLDOWN);
	n2.set(Keyboard::Num2, KeyType::SINGLE_COOLDOWN);
	n3.set(Keyboard::Num3, KeyType::SINGLE_COOLDOWN);
	n4.set(Keyboard::Num4, KeyType::SINGLE_COOLDOWN);
	n5.set(Keyboard::Num5, KeyType::SINGLE_COOLDOWN);
	n6.set(Keyboard::Num6, KeyType::SINGLE_COOLDOWN);
	n7.set(Keyboard::Num7, KeyType::SINGLE_COOLDOWN);
	n8.set(Keyboard::Num8, KeyType::SINGLE_COOLDOWN);
	n9.set(Keyboard::Num9, KeyType::SINGLE_COOLDOWN);
}

//RESET
void TextInputManager::reset()
{
	text.clear();
	done = 0;
}

//CLEAR
void TextInputManager::clear()
{
	text.clear();
}

//SET MODE
void TextInputManager::setMode(TextInputMode _mode)
{
	mode = _mode;
}

//SET STRING
void TextInputManager::setString(const std::string string)
{
	text = string;
	cursor = (short)text.size();
}

//SET STRING NUMERIC
void TextInputManager::setString(const double value)
{
	text = misc::doubleToString(value);
	cursor = (short)text.size();
}

//IS DONE
const bool TextInputManager::isDone()
{
	return done;
}

//FORCE DONE
void TextInputManager::forceDone()
{
	done = 1;
}

//GET STRING
const std::string TextInputManager::getString()
{
	return text;
}

//GET INTEGER VALUE
const int TextInputManager::getIntegerValue()
{
	if (mode == TextInputMode::NUMBERS && text.size() > 0 && text.size() < 10)
		return std::stoi(text);

	return 0;
}

//GET CURSOR
const short TextInputManager::getCursor()
{
	return cursor;
}