#ifndef GAMELOGIC_H
#define GAMELOGIC_H
//#include "GameObject.h"

class GameLogic
{
public:
	// Colision, between gameobjects, like the player, enemies, bullets and the level
	// High score, keeping track of how long the player has survived, also saving old times
	// Enviromental hazards for the player, keeping track of how certain objects in the enviroment will affect the player, i.e. quicksand and ice.
	// Current level, What object and texture should be loaded
	// UI info (life remaning, enemy counter. etc)
	// Leveling system (if implemented)
	// Staying within bounds, handling what will happen if an object goes out of bounds
	// Bullet info, how long the bullet will last
	// Menu handling?, what option is the player selecting
	// Velocity info?, how fast is the player/enemy going
	// Player state(dead), what happens when the player reaches 0 lives.
	GameLogic();
	~GameLogic();

private:


};

#endif // !GAMELOGIC_H