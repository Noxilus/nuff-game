#include "NPC.h"

NPC::NPC() : name(""), flavor(""), type(BasicNPCType), gold(0){}
NPC::NPC(string n, string r, int g, NPCType t) : name(n), flavor(r), type(t), gold(g){}

string NPC::FullName(){
	return name + flavor;
}

NPC BasicNPC = NPC();
NPC AlnwickSmith = NPC("Garush", " of the Iron Hammer", 1000, Smith);
NPC AlnwickHost = NPC("Neria", " the Fair", 1000, Host);
NPC AlnwickVendor = NPC("Cerkue", " the Snake", 1000, Vendor);

void InitNPCWares(){
	AlnwickSmith.weapons.push_back(IronAxe);
	AlnwickSmith.weapons.push_back(IronSword);
	AlnwickSmith.weapons.push_back(IronDagger);
	AlnwickSmith.weapons.push_back(IronHammer);
	AlnwickSmith.flavor = " of the Iron Hammer"; //Backup flavor initialization; flavor was originally spitting out nonsense
	AlnwickSmith.armor.push_back(LeatherCap);
	AlnwickSmith.armor.push_back(LeatherTunic);
	AlnwickSmith.armor.push_back(LeatherBracers);
	AlnwickSmith.armor.push_back(LeatherGreaves);
	AlnwickSmith.armor.push_back(LeatherBoots);
	AlnwickHost.food = {Apple, Pear, Banana, FruitSalad};
	AlnwickVendor.items = {Stick, Leaf, Branch, BobcatFur, GoldBar};
}
