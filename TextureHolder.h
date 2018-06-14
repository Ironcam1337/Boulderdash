#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
private:
	
	std::map<std::string, sf::Texture> m_Textures;
	static TextureHolder* m_s_Instance;

public:

	// Constructor
	TextureHolder();

	// Getter for texture by name
	static sf::Texture& GetTexture(std::string const& filename);
};