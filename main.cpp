#include <cstdlib>
#include <ctime>

#include "Game.h"

int main(int _argCount, char* _args[])
{
	srand(time(nullptr));
	
	Game::GetInstance()->GameLoop();
	Game::DeleteInstance();
	
	return 0;
}