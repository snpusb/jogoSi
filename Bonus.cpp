#include "Bonus.h"

Bonus::Bonus(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size) :
	animation(texture, imageCount, switchTime), Entidade(texture, position, size, false)
{
}

Bonus::~Bonus()
{
}

void Bonus::update(float deltaTime)
{
	animation.update(0, deltaTime, true);
	body.setTextureRect(animation.uvRect);
}

