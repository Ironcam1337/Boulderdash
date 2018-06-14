#include "stdafx.h"
#include "TextureHolder.h"
#include <assert.h>

using namespace sf;
using namespace std;

// Initialise the static reference here - to a null pointer (zero)
TextureHolder* TextureHolder::m_s_Instance = nullptr;

// Implement constructor
TextureHolder::TextureHolder()
{
	// Throw an error and stop execution in debug mode if a copy of the class already exists
	assert(m_s_Instance == nullptr);

	// Assign ourselves to the instance pointer 
	// - this is the new instance of the class which has just been creted.
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
	// Get a reference to m_Textures using m_s_Instance
	auto& m = m_s_Instance->m_Textures;


	// Create an iterator to hold a key value pair (kvp)
	auto keyValuePair = m.find(filename);
	// "auto" in this case is map<string, Texture>::iterator

	if (keyValuePair != m.end())
	{
		// Return the texture that has already been loaded
		return keyValuePair->second;
	}
	else
	{
		// Create a new key value pair using the filename
		// the subscript ([]) operator creates an entry in the map if there is not already one there.
		auto& texture = m[filename];
		// blank texture created, now just load it from file using sfml
		texture.loadFromFile(filename);

		// return the texture to the calling code
		return texture;
	}

}