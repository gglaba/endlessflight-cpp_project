#include "GameEngine.h"
#include <time.h>


int main()
{
	srand(static_cast<unsigned int>(time(0)));

	GameEngine game;
	
	game.run();

	return 0;
}