#ifndef SLOTS_H_
#define SLOTS_H_

#include "Items.h"
#include <iostream>

using namespace std;

struct InvSlot {
	Item item;
	int quantity;
	InvSlot();
	InvSlot(Item i);
	InvSlot(Item i, int q);
};

struct FoodSlot {
	Food food;
	int quantity;
	FoodSlot();
	FoodSlot(Food f);
	FoodSlot(Food f, int q);
};

struct ArmorSlot {
	Armor armor;
	ArmorSlot();
	ArmorSlot(Armor a);
	void SetArmor(Armor a);
};

struct WeaponSlot {
	Weapon weapon;
	WeaponSlot();
	WeaponSlot(Weapon w);
	void SetWeapon(Weapon w);
};

extern InvSlot invSlot;
extern FoodSlot foodSlot;
extern ArmorSlot armorSlot;
extern WeaponSlot weaponSlot;

#endif /* SLOTS_H_ */
