#include "Animador.h"

Animador::Animador(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	imageCurrent.x = 0;
	uvRect.width = (int) (texture->getSize().x / float(imageCount.x));
	uvRect.height = (int) (texture->getSize().y / float(imageCount.y));
}

Animador::~Animador()
{
}

void Animador::update(int row, float deltaTime, bool faceRight)
{
	imageCurrent.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime = 0.0f;
		imageCurrent.x ++;
		if (imageCurrent.x >= imageCount.x)
		{
			imageCurrent.x = 0;
		}
	}
	
	uvRect.top = imageCurrent.y * uvRect.height;

	if (faceRight)
	{
		uvRect.left = imageCurrent.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (imageCurrent.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}

}