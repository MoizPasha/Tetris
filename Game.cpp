#include <iostream>
#include <sfml/graphics.hpp>
#include "game.h"
#include <windows.h>

using namespace std;

int main()
{

	game play(20,10);
	while (play.running())
	{
		play.update();
	}
}
