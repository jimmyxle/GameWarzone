#pragma once
#include "Essentials.h"

#define MAX_DECK_SIZE 25
#define MAX_TYPE_SIZE 5
#define MAX_NUMBER_OF_SHUFFLES 75


class Order;

enum class CARD_TYPES {
	BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, NEGOTIATE, UNDEFINED
};


class Cards
{
private:
	CARD_TYPES type;
	int ID;
public:
	Cards();
	~Cards();
	Order* play();
	void setID(int _ID) { ID = _ID; }
	int getID() { return ID; }
	int setType(CARD_TYPES c) { type = c; return 0; }
	CARD_TYPES getType() { return type; }
	int print();

};



class Deck
{
private:
	std::vector<Cards*> cardLibrary;
	std::vector<Cards*> graveyard;
	int DeckCounter;
public:
	Deck();
	~Deck();
	Cards* draw();
	int shuffle();
	Cards* sendToGraveyard(Cards* c);
	std::vector<Cards*>& getGraveyard() { return graveyard;}
	int getRemainingCards() { return (int)cardLibrary.size(); }
};



class Hand
{
private:
	std::vector<Cards*> hand;
public:
	Hand() {};
	~Hand();
	Cards* playCard(); //used to query user input to choose card
	Cards* removeCard(Cards* c); //not sure if i need this
	Cards* playCard(CARD_TYPES t); //used to create an order
	int printHand();
	int placeCardInHand(Cards* c);
	Cards* hasCard(CARD_TYPES t);
	std::vector<Cards*> getHand() { return hand; }
	int getSize() { return (int)hand.size(); }

};