#ifndef NPC_H_
#define NPC_H_

#include <string>
#include <vector>

#include "Items.h"
#include "Types.h"

using namespace std;

class NPC {
public:
	string name, flavor;
	NPCType type;
	int gold;
	vector<Item> items = {};
	vector<Food> food = {};
	vector<Weapon> weapons = {};
	vector<Armor> armor = {};
	NPC();
	NPC(string n, string r, int g, NPCType t);
	string FullName();
};

extern void InitNPCWares();
extern NPC BasicNPC;
extern NPC AlnwickSmith, AlnwickHost, AlnwickVendor;

#endif /* NPC_H_ */
