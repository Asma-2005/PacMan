#include "Level1_Map.h"
#include "Graph.h"


Level1_Map::Level1_Map() {
	int level[] = {
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
   0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,
   0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,
   0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,
   0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,
   0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,
   0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,
   0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,1,0,
   0,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,0,
   0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
   0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,
   0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,
   0,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,
   0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,
   0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,
   0,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1,0,
   0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,
   0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,
   0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	};


	map.load(sf::Vector2u(90, 90), level, 20, 20);
		



}

void Level1_Map::drawMap(sf::RenderWindow& window) {
		
	window.draw(map);


}