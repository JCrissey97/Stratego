#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Image.hpp>

class Piece : public sf::Sprite
{
private:

public:
	bool move();
	Piece(sf::Texture &image);
};

Piece::Piece(sf::Texture &image)
{
	this->setTexture(image);
}