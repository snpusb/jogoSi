#include "Bonus.h"

class Vida :
	public Bonus
{
public:
	Vida(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, sf::Vector2f size, int qtd);
	~Vida();
	int getQtdVida();
private:
	int qtdVidas;
};
