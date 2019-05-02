#include "AreaDeColisao.h"

AreaDeColisao::AreaDeColisao(sf::RectangleShape& body, bool principalE): body(body)
{
	principal = principalE;
	
	sizeHalf.x = -1;
	sizeHalf.y = -1;
}

AreaDeColisao::~AreaDeColisao()
{
}

void AreaDeColisao::move(float dx, float dy)
{
	body.move(dx, dy);
}

bool AreaDeColisao::getPrincipal()
{
	return principal;
}

bool AreaDeColisao::checkColisao(AreaDeColisao& objeto,sf::Vector2f& dire�ao, float empurra)
{
	sf::Vector2f objetoPos = objeto.getPosition();
	sf::Vector2f objetoHalfSize = objeto.getHalfSize();
	sf::Vector2f essePos = getPosition();
	sf::Vector2f esseHalfSize = getHalfSize();

	float deltax = objetoPos.x - essePos.x;
	float deltay = objetoPos.y - essePos.y;

	float itersec�aox = abs(deltax) - (objetoHalfSize.x + esseHalfSize.x);
	float itersec�aoy = abs(deltay) - (objetoHalfSize.y + esseHalfSize.y);

	if (itersec�aoy < 0.00000f && itersec�aox < 0.00000000f)
	{
		empurra = std::min(std::max(empurra, 0.0f), 1.0f);

		if (itersec�aox > itersec�aoy)
		{
			if (deltax > 0.000000f)
			{
				move(itersec�aox*(1.0f - empurra), 0.0f);
				objeto.move(-itersec�aox * empurra, 0.0f);
				dire�ao.x = 1.0f;
				dire�ao.y = 0.0f;
			}
			else
			{
				move(-itersec�aox*(1.0f - empurra), 0.0f);
				objeto.move(itersec�aox * empurra, 0.0f);
				dire�ao.x = -1.0f;
				dire�ao.y = 0.0f;
			}
		}
		else
		{
			if (deltay > 0.00000f)
			{
				move(0.0f,itersec�aoy*(1.0f - empurra));
				objeto.move(0.0f,-itersec�aoy * empurra);
				dire�ao.x = 0.0f;
				dire�ao.y = 1.0f;
			}
			else
			{
				move(0.0f,-itersec�aoy * (1.0f - empurra));
				objeto.move(0.0f,itersec�aoy * empurra);
				dire�ao.x = 0.0f;
				dire�ao.y = -1.0f;
			}
		}
		
		return true;
	}
	return false;
}

sf::Vector2f AreaDeColisao::getPosition() const
{
	return body.getPosition();
}

void AreaDeColisao::setHalfSize(sf::Vector2f half)
{
	sizeHalf = half;
}

sf::RectangleShape AreaDeColisao::getBody()
{
	return body;
}

sf::Vector2f AreaDeColisao::getHalfSize()
{
	if (-1 == sizeHalf.x)
	{
		sizeHalf = calcHalfSize();
	}
	return sizeHalf;
}

sf::Vector2f AreaDeColisao::calcHalfSize()
{
	if (principal)
	{
		sizeHalf.x = body.getSize().x / 6.0f;
		sizeHalf.y = body.getSize().y / 2.0f;
	}
	else
	{
		sizeHalf = body.getSize() / 2.0f;
	}
	return sizeHalf;
}

