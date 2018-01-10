#include "Setup.h"
#include <iostream>

using namespace std;

SetupHandler::SetupHandler() : doneSetup(false), nameText("") {}
SetupHandler::~SetupHandler(){}

void SetupHandler::DoTitle(){
	cout << " ___ __ __ _\n" << " / | ____/ / _____ ____ / /___ __________ (_)___ \n" << "/ /| |/ __ / | / / _ \\/ __ \\/ __/ " << "/ / / ___/ _ \\ / / __ \\\n" << "/ ___ / /_/ /| |/ / __/ / / / /_/ /_/ / /" << " / __/ / / / / /\n" << "/_/ |_\\__,_/ |___/\\___/_/ /_/\\__/\\__,_/_/ \\___/ /_/_/ /_/ \n";
	cout << " __ _ \n" << " / / ____ __ ______ ______(_)___ _\n" << " / / / __ `/ | / / __ `/ ___/ / __ `/\n" << " / /__/ /_/ /| |/ / /_/ / / / / /_/ / \n" << "/_____|__,_/ |___/\\__,_/_/ /_/\\__,_/ \n\n\n";
}

void SetupHandler::StartChoice(){
	cout << "Would you like a tutorial (1) or to jump right into character creation (2)?\n";
	int choice;
	cin >> choice;
	if (choice == 1){
		DoIntro();
	}
	ResetSetup();
	ResetMaps();
	player.ResetStats();
	SetupLoop();
}

void SetupHandler::DoIntro(){
	cout << "In this game, you play as an adventurer in a faraway land: Lavaria. Your goal? To navigate the labyrinthian continent. Along the way you will battle monsters, buy weapons, and battle more monsters.\nCertain keys can be pressed to perform certain actions when outside of action or dialogs:\nArrow Keys - Move character\nEsc - Enter the command screen\nE - Eat food from your inventory\nF - Forage for items nearby\n\nIn the maps, tiles are denoted with single characters:\n@ - You, the player\n# - Wall, cannot be crossed\nE - Random enemy from the area\nD - Random chance at common or rare items or food\nG - Obtainable gold\nB - Area boss, only battleable after all other enemies are defeated.\nR - Armor/Weapon drop, always guarded by the Boss.\nF - Forge entrance/exit\nS - Town Smith, buy/sell weapons and armor\nC - Crafting menu, craft anything via recipes here\nM - Market entrance/exit\nV - Vendor, buy/sell miscellaneous items\nI - Inn entrance/exit\nH - Host, buy/sell food here\n1-9 - Map exits that lead to other maps\n\nEncounterable Map Types:\nWildlands - You will find enemies and gold here\nTowns - Safe from enemies, always contain a forge, market, and inn\nForge - Contains a smith and a crafting menu\nMarket - Contains a vendor\nInn - Contains a Host\n\nPlanned Future Additions:\n - Savefiles (via Host)\n - Many more items, enemies, and maps\n - Storyline\n - 2D Graphics beyond CMD\n - UNIX port\n\n\nIf you ever wish to quit the game, simply close the window\n";
}

void SetupHandler::DoName(){
	int redo;
	cout << "\nWhat is your name?\n";
	cin >> nameText;
	cout << "\nSo your name is " + nameText + "?\n1. Yes, it is\n2. No, it isn't\n";
	cin >> redo;
	switch (redo) {
	case 1:
		player.SetName(nameText);
		break;
	case 2:
		DoName();
		break;
	}
	redo = 0;
}

void SetupHandler::ConfirmSetup(){
	system("pause");
	sHandler.ClearScreen();
}

void SetupHandler::SetupLoop(){
	DoName();
	ConfirmSetup();
}

void SetupHandler::ResetSetup(){
	doneSetup = false;
	nameText = "";
}

void SetupHandler::ResetMaps(){
	int numMaps = allMaps.size();
	for (int i = 0; i < numMaps; i++){
		allMaps[i].ResetValues();
	}
}

SetupHandler setup = SetupHandler();
