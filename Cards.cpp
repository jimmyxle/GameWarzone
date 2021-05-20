#include "Cards.h"

Cards::Cards()
{
	type = CARD_TYPES::UNDEFINED;
	ID = 0;
}

Cards::~Cards()
{

}


Order* Cards::play()
{
	//Order* temp;
	switch (this->getType())
	{
	case CARD_TYPES::BOMB:

		break;
	case CARD_TYPES::REINFORCEMENT:
		
		break;
	case CARD_TYPES::BLOCKADE:

		break;
	case CARD_TYPES::AIRLIFT:

		break;
	case CARD_TYPES::NEGOTIATE:

		break;
	default:
		
		break;
	}
	return new Order();
}


int Cards::print()
{
	switch (type)
	{
	case CARD_TYPES::BOMB:
		printf("Bomb card\n");
		break;
	case CARD_TYPES::REINFORCEMENT:
		printf("Reinforcement card\n");

		break;
	case CARD_TYPES::BLOCKADE:
		printf("Blockade card\n");

		break;
	case CARD_TYPES::AIRLIFT:
		printf("Airlift card\n");

		break;
	case CARD_TYPES::NEGOTIATE:
		printf("Negotiate card\n");

		break;
	default:
		printf("Invalid card\n");

		break;
	}
	return 0;
}




Deck::Deck()
{
	DeckCounter = 0;
	srand((unsigned int)time(NULL));
	cardLibrary.reserve(MAX_DECK_SIZE);
	for (int i = 0; i < MAX_DECK_SIZE; i++)
	{
		cardLibrary.push_back(new Cards());
		cardLibrary.back()->setID(DeckCounter++);
	}

	int counter = 0;
	int i = 0;
	do
	{
		cardLibrary[i++]->setType(CARD_TYPES(counter));
		if (i % 5 == 0)
		{
			counter++;
		}
	} while (i < MAX_DECK_SIZE);
};
Deck::~Deck() 
{
	for (int i = 0; i < cardLibrary.size(); i++)
	{
		delete cardLibrary[i];
	}

	for (int i = 0; i < graveyard.size(); i++)
	{
		delete graveyard[i];
	}

};

Cards* Deck::draw()
{
	Cards* temp = cardLibrary.back();
	cardLibrary.pop_back();

	return temp;
}

int Deck::shuffle()
{
	int firstIndex = 0, secondIndex = 0, numberOfShuffles = 0;

	numberOfShuffles = MAX_NUMBER_OF_SHUFFLES;
	int currentDeckSize = (int)cardLibrary.size();
	for (int j = 0; j < numberOfShuffles; j++)
	{
		firstIndex = rand() % currentDeckSize;
		secondIndex = rand() % currentDeckSize;
		while (secondIndex == firstIndex)
		{
			secondIndex = rand() % currentDeckSize;
		}
		std::swap(cardLibrary[firstIndex], cardLibrary[secondIndex]);
	}


	printf("\n");
	return 0;
}

Cards* Deck::sendToGraveyard(Cards* c)
{
	for (int g = 0; g < graveyard.size(); g++)
	{
		if (graveyard[g]->getID() == c->getID())
			return NULL;
	}
	graveyard.push_back(c);
	return c;
}

Hand::~Hand()
{
	for (int h = 0; h < hand.size(); h++)
	{
		delete hand[h];
	}
}

Cards* Hand::playCard()
{
	int playerChoice = 0;
	bool invalid = false;

	while (!invalid)
	{
		printHand();
		printf("Choose a card. Enter a digit between 0 and %d\n", (int)(hand.size() - 1));
		std::cin >> playerChoice;

		if (playerChoice >= 0 && playerChoice < hand.size())
		{
			invalid = true;
		}
	}

	Cards* temp = hand[playerChoice];
	//temp->play();

	hand.erase(hand.begin() + playerChoice);
	return temp;
}

Cards* Hand::removeCard(Cards* c)
{
	for (int h = 0; h < hand.size(); h++)
	{
		if (hand[h] == c)
		{
			hand.erase(hand.begin() + h);
			return c;
		}
	}
	return nullptr;
}
Cards* Hand::playCard(CARD_TYPES t)
{
	int index = -99;
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i]->getType() == t)
		{
			index = i;
			break;
		}
	}

	Cards* temp = hand[index];
	//temp->play();

	hand.erase(hand.begin() + index);
	return temp;
}

int Hand::printHand()
{
	printf("Cards in hand:\n");
	for (int h = 0; h < hand.size(); h++)
	{
		printf("%d. ", h);
		hand[h]->print();
	}

	return 0;
}

int Hand::placeCardInHand(Cards* c)
{
	hand.push_back(c);
	return 0;
}

Cards* Hand::hasCard(CARD_TYPES c)
{
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i]->getType() == c)
		{
			return hand[i];
		}
	}

	return nullptr;
}