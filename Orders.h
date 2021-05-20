#pragma once
#include "Essentials.h"
#define ATTACKER_CHANCE 0.60
#define DEFENDER_CHANCE 0.70


class Order
{

protected:
	int Value;
	std::string name;
	std::string description;
	Map* gameMap;
	int army;
	Player* sourcePlayer;
	Player* targetPlayer;
	Territory* sourceTerritory;
	Territory* targetTerritory;
public:
	Order();
	virtual ~Order();
	friend std::ostream& operator << (std::ostream& out, const Order& o);
	friend std::istream& operator >> (std::istream& in, Order& o);
	friend bool operator > (const Order& first, const Order& second);
	friend bool operator < (const Order& first, const Order& second);
	virtual int execute();
	virtual bool validate();
	virtual int getValue() { return Value; }
	virtual void setValue(int val) { Value = val; }

};


class OrderList
{
private:
	std::vector<Order*> pending;
	std::vector<Order*> history;
	Map* map;

public:
	OrderList();
	~OrderList() {}
	int add(Order* o);
	int remove(int index);
	int move(int index1, int index2);
	int playWholeList();
	std::vector<Order*>& getHistory() { return pending; }
	int setMap(Map* _map) { map = _map; return 0; }
	//int create(CARD_TYPES type);
	bool playNextOrder();
	void sort();


};

class Deploy : public Order
{
private:

public:

	Deploy() = default;
	Deploy(Player* _sourcePlayer, int _Army, Territory* _targetTerritory);
	~Deploy() = default;

	int execute();
	bool validate();
};

class Advance : public Order
{
private:
public:
	Advance() = default;
	Advance(Player* _sourcePlayer, int _Army, Territory* _sourceTerritory,
		Territory* _targetTerritory);
	~Advance() = default;
	int execute();
	bool validate();
	void battle(int defencePower, int attackPower);

};


class Airlift : public Advance
{
public:
	Airlift() = default;
	Airlift(Player* _sourcePlayer, int _Army, Territory* _sourceTerritory,
		Territory* _targetTerritory);
	~Airlift() = default;
	int execute();
	bool validate();
};


class Bomb : public Order
{
private:

public:
	Bomb() = default;
	Bomb(Player* sourcePlayer, Territory* _targetTerritory);
	~Bomb() = default;
	int execute();
	bool validate();

};

class Blockade : public Order
{
private:

public:
	Blockade() = default;
	Blockade(Player* sourcePlayer, Territory* _targetTerritory);
	~Blockade()= default;
	int execute();
	bool validate();

};

class Negotiate : public Order
{
public:
	Negotiate() = default;
	Negotiate(Player* _sourcePlayer, Player* _targetPlayer);
	~Negotiate() = default;
	int execute();
	bool validate();
};

