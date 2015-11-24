#pragma once
#include "Includes.hpp"

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};

// define the level with an array of tile indices
const int level[] =
{
	0, 29, 29, 29, 29, 29, 29, 29, 29, 0,
};
