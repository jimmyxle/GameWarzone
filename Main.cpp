#include "Essentials.h"


#define TERRITORY_TEST_0 0
#define MAP_TEST_0 0
#define CONTINENT_TEST_0 0
#define CONTINENT_TEST_1 0
#define CONTINENT_TEST_2 0
#define MAPLOADER_TEST_0 0
#define MAPLOADER_TEST_1 0
#define PLAYER_TEST_0 0
#define PLAYER_TEST_1 0
#define PLAYER_TEST_2 0
#define PLAYER_TEST_3 0
#define CARDS_TEST_0 0
#define CARDS_TEST_1 0
#define CARDS_TEST_2 0
#define ORDERS_TEST_0 0
#define ORDERS_TEST_1 0
#define GAMEENGINE_TEST_0 0
#define GAMEENGINE_TEST_1 0
#define GAMEENGINE_TEST_2 0
#define GAMEENGINE_TEST_3 0
#define GAMEENGINE_TEST_4 0
#define GAMEENGINE_TEST_5 0
#define GAMEENGINE_TEST_6 0
#define DEPLOY_TEST_0 0
#define ADVANCE_TEST_0 0
#define AIRLIFT_TEST_0 0
#define BOMB_TEST_0 0
#define BLOCKADE_TEST_0 0
#define NEGOTIATE_TEST_0 0
#define MAINLOOP_TEST0 0
#define SFML_TEST0 0
#define SFML_TEST1 1





int main(void)
{
	if (TERRITORY_TEST_0)
	{
		Territory* t1 = new Territory();
		Territory* t2 = new Territory(1, "Quebec");
		t1->setNumberOfArmies(10);
		int num = t1->getNumberOfArmies();
		t2->setXY(2, 2);
		int x = t2->getX();
		int y = t2->getY();

		std::string name = t2->getName();
		
		t1->addNeighbor(t2);

		delete t1; 
		delete t2;
	}
	if (MAP_TEST_0)
	{
		Map* m1 = new Map();
		Territory* t1 = m1->createNode(0, "Ontario");
		Territory* t2 = m1->createNode(1, "Quebec");
		Territory* t3 = m1->createNode(2, "Manitoba");
		
		int result = m1->addEdge(t1, t2);
		result = m1->addEdge(t1, t3);
		delete m1;
	}

	if (CONTINENT_TEST_0)
	{
		Map* m1 = new Map();
		Territory* t1 = m1->createNode(0, "Ontario");
		Territory* t2 = m1->createNode(1, "Quebec");
		Territory* t3 = m1->createNode(2, "Manitoba");
		int result = m1->addEdge(t1, t2);
		result = m1->addEdge(t1, t3);

		m1->createContinent("America", 6);
		result = m1->addToContinent(0, t1);
		result = m1->addToContinent(0, t2);
		result = m1->addToContinent(0, t3);

		m1->printBoard();

		if (m1->validate())
			printf("Test passes.\n");
		else
			printf("Test fails.\n");

		delete m1; 
	}

	if (CONTINENT_TEST_1)
	{
		Map* m1 = new Map();
		Territory* t1 = m1->createNode(0, "Ontario");
		Territory* t2 = m1->createNode(1, "Quebec");
		Territory* t3 = m1->createNode(2, "Manitoba");
		int result = m1->addEdge(t1, t2);
		result = m1->addEdge(t1, t3);

		m1->createContinent("America", 6);
		result = m1->addToContinent(0, t1);
		result = m1->addToContinent(0, t2);
		result = m1->addToContinent(0, t3);

		m1->createContinent("Australia", 6);
		result = m1->addToContinent(1, t1);

		if (!m1->validate())
			printf("Test passes.\n");
		else
			printf("Test fails.\n");

		//auto ch = _getch();
		delete m1;
	}
	if (CONTINENT_TEST_2)
	{
		Map* m1 = new Map();
		Territory* t1 = m1->createNode(0, "Ontario");
		Territory* t2 = m1->createNode(1, "Quebec");
		Territory* t3 = m1->createNode(2, "Manitoba");
		int result = m1->addEdge(t1, t2);
		//result = m1->addEdge(t1, t3);

		m1->createContinent("America", 6);
		result = m1->addToContinent(0, t1);
		result = m1->addToContinent(0, t2);
		result = m1->addToContinent(0, t3);

		if (!m1->validate())
			printf("Test passes.\n");
		else
			printf("Test fails.\n");

		//auto ch = _getch();
		delete m1;
	}

	if (MAPLOADER_TEST_0)
	{

		MapLoader* m0 = new MapLoader();
		std::string file_location = MAPFOLDER CANADA;
		m0->readMapData(file_location);
		m0->getMap()->printBoard();

		if (m0->getMap()->validate())
			printf("Test passes.\n");
		else
			printf("Test fails.\n");

	}

	if (MAPLOADER_TEST_1)
	{

		MapLoader* m0 = new MapLoader();
		std::string file_location = MAPFOLDER CANADA_INVALID;
		m0->readMapData(file_location);
		m0->getMap()->printBoard();

		if (!m0->getMap()->validate())
			printf("Test passes.\n");
		else
			printf("Test fails.\n");

	}
	if (PLAYER_TEST_0)
	{
		Player* p0 = new Player();
		Player* p1 = new Player(5);
		Player* p2 = new Player(10);
		p0->addAlliance(p1);
		p1->addAlliance(p2);
		p0->setID(0);
		p1->setID(1);

		if (p0->checkAlliance(p1))
			printf("Test passes.\n");
		else
			printf("Test fails.\n");
		

		if(!p0->checkAlliance(p2))
			printf("Test passes.\n");
		else
			printf("Test fails.\n");
		Map* m1 = new Map();

		Territory* t0 = m1->createNode(0, "Ontario");
		Territory* t1 = m1->createNode(1, "Quebec");
		Territory* t2 = m1->createNode(2, "Manitoba");
		int result = m1->addEdge(t0, t1);
		result = m1->addEdge(t0, t2);


		p0->setMap(m1);
		p1->setMap(m1);

		p0->addTerritory(t0);
		p0->addTerritory(t1);
		p1->addTerritory(t2);

		p0->toDefend();
		p1->toDefend();


		delete p0;
		delete p1;
	}

	if (PLAYER_TEST_1)
	{
		Player* p0 = new Player();
		Player* p1 = new Player(5);
		Player* p2 = new Player(10);
		p0->addAlliance(p1);
		p1->addAlliance(p2);
		p0->setID(0);
		p1->setID(1);

		if (p0->checkAlliance(p1))
			printf("Test passes.\n");
		else
			printf("Test fails.\n");


		if (!p0->checkAlliance(p2))
			printf("Test passes.\n");
		else
			printf("Test fails.\n");
		Map* m1 = new Map();

		Territory* t0 = m1->createNode(0, "Ontario");
		Territory* t1 = m1->createNode(1, "Quebec");
		Territory* t2 = m1->createNode(2, "Manitoba");
		int result = m1->addEdge(t0, t1);
		result = m1->addEdge(t0, t2);


		p0->setMap(m1);
		p1->setMap(m1);

		p0->addTerritory(t0);
		p0->addTerritory(t1);
		p1->addTerritory(t2);

		p0->toAttack();
		p1->toAttack();


		delete p0;
		delete p1;
	}

	if (PLAYER_TEST_2)
	{
		Player* p0 = new Player();
		Player* p1 = new Player(5);
		p0->setID(0);
		p1->setID(1);


		Map* m1 = new Map();
		Territory* t1 = m1->createNode(0, "Ontario");
		Territory* t2 = m1->createNode(1, "Quebec");
		Territory* t3 = m1->createNode(2, "Manitoba");

		int result = m1->addEdge(t1, t2);
		result = m1->addEdge(t1, t3);

		p0->setMap(m1);
		p1->setMap(m1);

		p0->addTerritory(t1);
		p1->addTerritory(t2);

		if (!p0->addTerritory(t2))
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");

		if (!p0->removeTerritory(t2->getID()))
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");

		delete p1;
		delete p0;
		delete m1;


	}

	if (PLAYER_TEST_3)
	{
		Player* p0 = new Player();
		Player* p1 = new Player(5);
		p0->setID(0);
		p1->setID(1);

		Deck* d0 = new Deck();
		d0->shuffle();
		
		p0->drawCard(*d0);
		p1->drawCard(*d0);

		if (p0->getPlayerHand()->getSize() == 1)
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");
		if (p1->getPlayerHand()->getSize() == 1)
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");
		if (d0->getRemainingCards() == 23)
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");

		delete d0;
		delete p1;
		delete p0;



	}

	if (CARDS_TEST_0)
	{
		Cards* c0 = new Cards();
		c0->setType(CARD_TYPES::BOMB);
		if(c0->play() == 0)
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");
		if(c0->getType() == CARD_TYPES(0))
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");

		delete c0;
	}

	if (CARDS_TEST_1)
	{
		Cards *c0, *c1;
		Deck* d0 = new Deck();
		c0 = d0->draw();
		d0->shuffle();
		c1 = d0->draw();

		if(d0->sendToGraveyard(c0))
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");
		if(d0->sendToGraveyard(c1))
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");
		if (!d0->sendToGraveyard(c1))
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");

		if(c0)
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");

		if(c1)
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");
		if(d0->getGraveyard().size() == 2)
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");

		delete d0;

	}

	if (CARDS_TEST_2)
	{
		Deck* d0 = new Deck();
		Hand* h0 = new Hand();
		h0->placeCardInHand(d0->draw());

		d0->shuffle();
		h0->placeCardInHand(d0->draw());
		h0->placeCardInHand(d0->draw());
		h0->placeCardInHand(d0->draw());
		h0->placeCardInHand(d0->draw());

		if(h0->getSize() == 5)
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");
		if(d0->getRemainingCards() == 20)
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");

		d0->sendToGraveyard(h0->playCard());

		if(h0->hasCard(CARD_TYPES::NEGOTIATE))
			printf("Test Passed.\n");
		else
			printf("Test Failed.\n");

		

		delete h0;
		delete d0;

	}

	if (ORDERS_TEST_0)
	{
		Order* o0 = new Order();
		Order* o1 = new Order();
		Order* o2 = new Order();
		std::cout << o0;
		std::cin >> *o0;

		OrderList* ol = new OrderList();
		ol->add(o0);
		ol->add(o1);
		ol->add(o2);
		ol->remove(0);
		ol->move(0, 1);
		ol->playWholeList();
		o0->validate();
		o0->execute();
	}
	if (ORDERS_TEST_1)
	{
		Order* o0 = new Order();
		Order* o1 = new Order();
		Order* o2 = new Order();
		Order* o3 = new Order();
		Order* o4 = new Order();
		o0->setValue(0);
		o1->setValue(23);
		o2->setValue(6);
		o3->setValue(18);
		o4->setValue(24);

		OrderList* ol = new OrderList();
		ol->add(o0);
		ol->add(o1);
		ol->add(o2);
		ol->add(o3);
		ol->add(o4);


		ol->sort();
		printf("");
	}

	if (GAMEENGINE_TEST_0)
	{
		GameEngine* GE = new GameEngine();
		std::string location = GE->getFileLocation();
		printf("%s\n", location.c_str());

		Map* map = GE->createValidMap(location);
		if (map)
			printf("success\n");
	}
	if (GAMEENGINE_TEST_1)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		//GE->reinforcementPhase();
	}
	if (GAMEENGINE_TEST_2)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
	}
	if (GAMEENGINE_TEST_3)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
		GE->issueOrdersPhase();
	}
	if (GAMEENGINE_TEST_4)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
		GE->getGameMap()->ListOfPlayers[0]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[1]->setNumberToDeploy(0);
		GE->issueOrdersPhase();

	}
	if (GAMEENGINE_TEST_5)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
		GE->issueOrdersPhase();
		GE->executeOrdersPhase();

	}


	if (DEPLOY_TEST_0)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
		GE->getGameMap()->ListOfPlayers[0]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[1]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[0]->addTerritory(GE->getGameMap()->CompleteList[0]); //add NB
		GE->getGameMap()->ListOfPlayers[0]->addTerritory(GE->getGameMap()->CompleteList[1]); //add PEI
		GE->getGameMap()->ListOfPlayers[0]->addTerritory(GE->getGameMap()->CompleteList[7]); //add QC
		GE->getGameMap()->ListOfPlayers[0]->addTerritory(GE->getGameMap()->CompleteList[2]); //add NS
		GE->getGameMap()->CompleteList[0]->setNumberOfArmies(20); 


		GE->issueOrdersPhase();

	}
	if (ADVANCE_TEST_0)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
		GE->getGameMap()->ListOfPlayers[0]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[1]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[0]->addTerritory(GE->getGameMap()->CompleteList[0]); //add NB
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[1]); //add PEI
		GE->getGameMap()->CompleteList[0]->setNumberOfArmies(20);
		GE->getGameMap()->CompleteList[1]->setNumberOfArmies(5);


		GE->issueOrdersPhase();
		GE->executeOrdersPhase();

	}
	if (AIRLIFT_TEST_0)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
		GE->getGameMap()->ListOfPlayers[0]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[1]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[0]->addTerritory(GE->getGameMap()->CompleteList[0]); //add NB
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[1]); //add PEI
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[2]); //add PEI
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[3]); //add PEI
		GE->getGameMap()->CompleteList[0]->setNumberOfArmies(20);
		GE->getGameMap()->CompleteList[1]->setNumberOfArmies(5);

		Cards* airliftCard0 = new Cards();
		airliftCard0->setType(CARD_TYPES::AIRLIFT);
		Cards* airliftCard1 = new Cards();
		airliftCard1->setType(CARD_TYPES::AIRLIFT);

		GE->getGameMap()->ListOfPlayers[0]->getPlayerHand()->placeCardInHand(airliftCard0);
		GE->getGameMap()->ListOfPlayers[1]->getPlayerHand()->placeCardInHand(airliftCard1);

		GE->issueOrdersPhase();
		GE->executeOrdersPhase();

	}
	if (BOMB_TEST_0)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
		GE->getGameMap()->ListOfPlayers[0]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[1]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[0]->addTerritory(GE->getGameMap()->CompleteList[0]); //add NB
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[1]); //add PEI
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[2]); //add PEI
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[3]); //add PEI
		GE->getGameMap()->CompleteList[0]->setNumberOfArmies(20);
		GE->getGameMap()->CompleteList[1]->setNumberOfArmies(5);

		Cards* bomb0 = new Cards();
		bomb0->setType(CARD_TYPES::BOMB);
		Cards* bomb1 = new Cards();
		bomb1->setType(CARD_TYPES::BOMB);

		GE->getGameMap()->ListOfPlayers[0]->getPlayerHand()->placeCardInHand(bomb0);
		GE->getGameMap()->ListOfPlayers[1]->getPlayerHand()->placeCardInHand(bomb1);


		GE->issueOrdersPhase();
		GE->executeOrdersPhase();

	}
	if (BLOCKADE_TEST_0)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
		GE->getGameMap()->ListOfPlayers[0]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[1]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[0]->addTerritory(GE->getGameMap()->CompleteList[0]); //add NB
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[1]); //add PEI
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[2]); //add PEI
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[3]); //add PEI
		GE->getGameMap()->CompleteList[0]->setNumberOfArmies(20);
		GE->getGameMap()->CompleteList[1]->setNumberOfArmies(5);

		Cards* blockade0 = new Cards();
		blockade0->setType(CARD_TYPES::BLOCKADE);
		Cards* blockade1 = new Cards();
		blockade1->setType(CARD_TYPES::BLOCKADE);

		GE->getGameMap()->ListOfPlayers[0]->getPlayerHand()->placeCardInHand(blockade0);
		GE->getGameMap()->ListOfPlayers[1]->getPlayerHand()->placeCardInHand(blockade1);


		GE->issueOrdersPhase();
		GE->executeOrdersPhase();

	}
	if (NEGOTIATE_TEST_0)
	{
		GameEngine* GE = new GameEngine();
		GE->startupPhase();
		GE->reinforcementPhase();
		GE->getGameMap()->ListOfPlayers[0]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[1]->setNumberToDeploy(0);
		GE->getGameMap()->ListOfPlayers[0]->addTerritory(GE->getGameMap()->CompleteList[0]); //add NB
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[1]); //add PEI
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[2]); //add PEI
		GE->getGameMap()->ListOfPlayers[1]->addTerritory(GE->getGameMap()->CompleteList[3]); //add PEI
		GE->getGameMap()->CompleteList[0]->setNumberOfArmies(20);
		GE->getGameMap()->CompleteList[1]->setNumberOfArmies(5);

		Cards* negotiate0 = new Cards();
		negotiate0->setType(CARD_TYPES::NEGOTIATE);
		Cards* negotiate1 = new Cards();
		negotiate1->setType(CARD_TYPES::NEGOTIATE);

		GE->getGameMap()->ListOfPlayers[0]->getPlayerHand()->placeCardInHand(negotiate0);
		GE->getGameMap()->ListOfPlayers[1]->getPlayerHand()->placeCardInHand(negotiate1);


		GE->issueOrdersPhase();
		GE->executeOrdersPhase();

	}
	if (MAINLOOP_TEST0)
	{
		GameEngine* GE = new GameEngine();
		GE->mainGameLoop();
	}
	if (SFML_TEST0)
	{
		sf::RenderWindow window(sf::VideoMode(800, 600), "Risk: Warzone", sf::Style::Default);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					std::cout << "window closed " << std::endl;

					window.close();
					break;

				case sf::Event::Resized:
					std::cout << "new width: " << event.size.width << std::endl;
					std::cout << "new height: " << event.size.height << std::endl;
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						std::cout << "Escape key was pressed.\n";
					}
					break;

				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						std::cout << "x:" << event.mouseButton.x;
						std::cout << "\ty: " << event.mouseButton.y << std::endl;
					}

					break;
				}
			}

			window.clear();
			window.display();
		}
	}

	if (SFML_TEST1)
	{
		MapLoader* m0 = new MapLoader();
		std::string file_location = MAPFOLDER CANADA;
		std::string map_image_file = MAPFOLDER "canada\\canada_pic.png";
		//std::string file_location = "C:\\Users\\jimmy\\Documents\\comp345\\maps\\switzerland\\swiss.map";
		//std::string map_image_file = "C:\\Users\\jimmy\\Documents\\comp345\\maps\\switzerland\\swiss_pic.jpg";


		m0->readMapData(file_location);
		m0->getMap()->printBoard();


		sf::Event event;
		std::vector<sf::Sprite*> sprite_vector;
		sf::Texture rectTexture;
		sf::Texture backgroundTexture;
		if (!backgroundTexture.loadFromFile(map_image_file))
		{
			std::cout << "Problem loading map.\n";
			exit(0);
		}
		sf::Vector2 resolution = backgroundTexture.getSize();
		if (!rectTexture.loadFromFile(TEXTUREFOLDER "TerritoryIcon.png"))
		{
			std::cout << "Problem loading texture.\n";
			exit(0);
		}
		sf::Sprite background(backgroundTexture);
	
		sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Risk: Warzone", sf::Style::Titlebar | sf::Style::Close );
		window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2, sf::VideoMode::getDesktopMode().height / 8));

		//create the vector of sprites. Maybe add a sprite to every territory

		for (int i = 0; i < m0->getMap()->CompleteList.size(); i++)
		{
			Territory* temp = m0->getMap()->CompleteList[i];
			int x = temp->getX();
			int y = temp->getY();

			sf::Sprite* spr = new sf::Sprite();
			rectTexture.setSmooth(false);
			spr->setTexture(rectTexture);
			spr->setPosition(sf::Vector2f(x, y));
			sprite_vector.push_back(spr);
		}

		while (window.isOpen())
		{
			/* Draw everything you need to before you display it*/
			window.clear();
			window.draw(background);
			for (int i = 0; i < sprite_vector.size(); i++)
			{
				window.draw(*sprite_vector[i]);
			}
			window.display();

			/* Check user inputs */
			size_t sprite_vector_size = sprite_vector.size();

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					std::cout << "window closed " << std::endl;

					window.close();
					break;

				case sf::Event::Resized:
					std::cout << "new width: " << event.size.width << std::endl;
					std::cout << "new height: " << event.size.height << std::endl;
					break;

				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape)
					{
						std::cout << "Escape key was pressed.\n";
					}
					else if (event.key.code == sf::Keyboard::Q)
					{
						std::cout << "Quit the game. " << std::endl;

						window.close();
						break;
					}

					break;

				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Right)
					{
						//std::cout << "x:" << event.mouseButton.x;
						//std::cout << "\ty: " << event.mouseButton.y << "\t";
						for (int i = 0; i < sprite_vector_size; i++)
						{
							if (sprite_vector[i]->getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
							{
								Territory* temp = m0->getMap()->CompleteList[i];
								std::cout << "Territory: " << temp->getName().c_str() <<"\n";
								std::cout << "Army: " << temp->getNumberOfArmies();

								if(temp->getPlayerOwner())
									std::cout << "\nOwned by: " << temp->getPlayerOwner();

								break;
							}
						}
						std::cout <<"\n";
					}
					break;
				}
			}
		}
	}

	std::cout << "Press <enter> to end.\n" << std::endl;
	auto ch = _getch();

	return 0;
}