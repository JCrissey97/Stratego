#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Image.hpp>
#include <string>

using std::string;
using sf::Image;
using sf::Texture;

class Piece : public sf::Sprite
{
private:
	
public:
	Piece(string file_name);
};

Piece::Piece(string file_name)
{
	Image img;
	img.loadFromFile(file_name);
	Texture t;
	t.loadFromImage(img);
	this->setTexture(t);
}