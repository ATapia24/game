#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "misc.h"

struct Texture
{
	sf::Texture texture;
	std::string name;
};

class TextureManager
{
private:
	std::vector <Texture*> textureList;
	std::vector <std::string> subfolders;
	const std::string ROOT_FOLDER = "Assets/";
	bool validFileType(std::string filename);
public:
	TextureManager();
	~TextureManager();
	void loadTextures();
	void addFolder(std::string folder);
	std::vector<Texture*> getTextures();
};

