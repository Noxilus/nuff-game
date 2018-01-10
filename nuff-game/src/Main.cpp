#include "Setup.h"
#include <windows.h>
#include <stdio.h>

int main(){
	InitMaps();
	InitNPCWares();
	sHandler.SetupScreen();
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	sHandler.ClearScreen();
	while(true){
		setup.DoTitle();
		setup.StartChoice();
		player.SetMap(allMaps[1]);
		// player.SetMap(testMap);
		player.UpdateMap();
		player.ActionLoop();
	}
	return 0;
}
