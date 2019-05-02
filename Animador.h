#pragma once

#include <SFML\Graphics.hpp>
class Animador
{
private:
	float totalTime;
	float switchTime; 
	sf::Vector2u imageCount;
	sf::Vector2u imageCurrent;


public:
	Animador(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animador();
	sf::IntRect uvRect;
	void update(int row, float deltaTime, bool faceRight);

};

