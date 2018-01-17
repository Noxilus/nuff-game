#ifndef MAPS_H_
#define MAPS_H_

#include <string>
#include <vector>
#include "Enemy.h"
#include "NPC.h"

using namespace std;

struct Map {
	vector<string> layout, original_layout;
	vector<Item> commonItems, rareItems;
	vector<Food> commonFood, rareFood;
	vector<Enemy> enemyList;
	Enemy boss;
	vector<int> exits; //indices in allMaps array
	string name;
	int level, forgeX, forgeY, marketX, marketY, innX, innY, numEnemies,
	original_numEnemies;
	NPC* smith = &BasicNPC;
	NPC* host = &BasicNPC;
	NPC* vendor = &BasicNPC;
	Map();
	Map(vector<string> l, vector<Item> ci, vector<Item> ri, vector<Food> cf, vector<Food> rf, vector<Enemy> el, Enemy b, vector<int> e, string n, int lvl, int ne);
	Map(vector<string> l, vector<int> e, string n, int lvl, int fx, int fy, int mx, int my, int ix, int iy, int ne, NPC* s, NPC* h, NPC* v);
	~Map();
	void ResetValues();
};

extern void InitMaps();
extern void InitLayouts();
extern Map noMap;
extern Map highashPlainsA, highashPlainsB, highashPlainsC; //Highash Plains
extern Map alnwick, alnwickForge, alnwickMarket, alnwickInn; //Alnwick
extern Map testMap, tbcMap;
extern vector<Map> allMaps;
extern vector<string> blankLayout;
extern vector<string> plainsLayoutA, plainsLayoutB, plainsLayoutC; //Highash Plains
extern vector<string> alnwickLayout; //Major Towns
extern vector<string> forgeLayout, marketLayout, innLayout; //Town Buildings
extern vector<string> testLayout, tbcLayout;

#endif /* MAPS_H_ */
