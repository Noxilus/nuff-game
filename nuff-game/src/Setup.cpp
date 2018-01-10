#include "Setup.h"
#include <iostream>

using namespace std;

SetupHandler::SetupHandler() : doneClass(false), doneRace(false), doneSetup(false), nameText(""), classText(""), raceText("") {}
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

void SetupHandler::DoClass(){
	int classChoice, redo;
	if (!doneClass){
		cout << "\nPlease choose a class (enter the number):\n1. Knight: +agility -strength\n2. Warrior: +strength -agility\n3. Thief: +agility -health\n4. Blacksmith: +strength -magic\n5. Lumberjack: +stamina -agility\n6. Mage: +magic -strength\n7. Archer: +health -agility\n";
	}
	else
	{
		cout << "\nPlease reenter a class:\n";
	}
	cin >> classChoice;
	switch (classChoice) {
	case 1:
		classText = "Knight";
		player.SetClass(KnightClass);
		break;
	case 2:
		classText = "Warrior";
		player.SetClass(WarriorClass);
		break;
	case 3:
		classText = "Thief";
		player.SetClass(ThiefClass);
		break;
	case 4:
		classText = "Blacksmith";
		player.SetClass(BlacksmithClass);
		break;
	case 5:
		classText = "Lumberjack";
		player.SetClass(LumberjackClass);
		break;
	case 6:
		classText = "Mage";
		player.SetClass(MageClass);
		break;
	case 7:
		classText = "Archer";
		player.SetClass(ArcherClass);
		break;
	default:
		classText = "Knight";
		player.SetClass(KnightClass);
		break;
	}
	cout << "\nYou chose " + classText + ". Is this your final decision?\n1.Yes, let's continue\n2.No, let me reselect\n";
	cin >> redo;
	switch (redo) {
	case 2:
		doneClass = true;
		DoClass();
		break;
	default:
		doneClass = true;
		break;
	}
	classChoice = 0;
	redo = 0;
}

void SetupHandler::DoRace(){
	int raceChoice, redo;
	if (!doneRace){
		cout << "\nPlease choose a race (enter the number):\n1. Human +20% health +5% agility -5% stamina -10% strength\n2. Wood Elf +5% health +10% magic +10% agility -15% strength\n3. Orc +10% stamina +15% strength -5% magic -10% agility\n4. Dark Elf +10% magic +15% agility -5% stamina -10% strength\n5. Dragonling +15% magic +10% agility -5% health -10% stamina\n6. Dwarf +5% health +10% stamina +10% strength -10% magic -5% agility\n";
	}
	else
	{
		cout << "\nPlease reenter a race:\n";
	}
	cin >> raceChoice;
	switch (raceChoice) {
	case 1:
		raceText = "Human";
		player.SetRace(HumanRace);
		break;
	case 2:
		raceText = "Wood Elf";
		player.SetRace(WoodElfRace);
		break;
	case 3:
		raceText = "Orc";
		player.SetRace(OrcRace);
		break;
	case 4:
		raceText = "Dark Elf";
		player.SetRace(DarkElfRace);
		break;
	case 5:
		raceText = "Dragonling";
		player.SetRace(DragonlingRace);
		break;
	case 6:
		raceText = "Dwarf";
		player.SetRace(DwarfRace);
		break;
	default:
		raceText = "Human";
		player.SetRace(HumanRace);
		break;
	}
	cout << "\nYou chose " + raceText + ". Is this your final decision?\n1. Yes, let's continue\n2. No, let me reselect\n";
	cin >> redo;
	switch (redo) {
	case 2:
		doneRace = true;
		DoRace();
		break;
	default:
		doneRace = true;
		break;
	}
	raceChoice = 0;
	redo = 0;
}

void SetupHandler::ConfirmSetup(){
	cout << "\nAh... so you are " << nameText << " the " << raceText << " " << classText << ".\n";
	player.SetStats();
	system("pause");
	sHandler.ClearScreen();
}

void SetupHandler::SetupLoop(){
	DoName();
	DoClass();
	DoRace();
	ConfirmSetup();
}

void SetupHandler::ResetSetup(){
	doneClass = false;
	doneRace = false;
	doneSetup = false;
	nameText = "";
	classText = "";
	raceText = "";
}

void SetupHandler::ResetMaps(){
	int numMaps = allMaps.size();
	for (int i = 0; i < numMaps; i++){
		allMaps[i].ResetValues();
	}
}

SetupHandler setup = SetupHandler();
