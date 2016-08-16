#include "stdafx.h"
#include "TextureManager.h"

//CONSTRUCTOR
TextureManager::TextureManager()
{
}

//DECONSTRUCTOR
TextureManager::~TextureManager()
{
}

//LOAD
void TextureManager::loadTextures()
{
	//every sub folder
	for (unsigned int i = 0; i < subfolders.size(); i++)
	{
		std::vector<std::string> files = misc::getFileNames(ROOT_FOLDER + subfolders[i]);
		
		//every file within folder
		for (unsigned int j = 0; j < files.size(); j++)
		{
			//create texture object
			if (validFileType(files[j]))
			{
				Texture* texture = new Texture;
				sf::Texture raw_texture;

				//load and set name
				raw_texture.loadFromFile(ROOT_FOLDER + subfolders[i] + '/' + files[j]);
				texture->texture = raw_texture;
				texture->name = files[j];

				textureList.push_back(texture);
			}
		}
	}
}

//ADD FOLDER
void TextureManager::addFolder(std::string folder)
{
	subfolders.push_back(folder);
}

//VALID FILE TYPE
bool TextureManager::validFileType(std::string filename)
{
	if (misc::getFileType(filename) == "png")
		return 1;
	
	return 0;
}

//GET TEXTURES
std::vector<Texture*> TextureManager::getTextures()
{
	return textureList;
}