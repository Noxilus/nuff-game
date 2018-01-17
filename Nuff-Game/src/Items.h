#ifndef ITEMS_H_
#define ITEMS_H_

#include <string>
#include <vector>
#include <iostream>
#include "Types.h"

using namespace std;

struct Item {
	std::string name;
	double value;
	ItemType itemType;
	Item(std::string n, double v, ItemType t);
};

struct ItemR_Component {
	Item i;
	int q;
};

struct ItemRecipe {
	vector<ItemR_Component> components;
	vector<bool> collected;
	vector<int> invIndices;
	bool craftable;
	Item product;
	ItemRecipe(vector<ItemR_Component> comp, Item prod);
	void InitVectors();
	void CheckCollection();
};

struct Food : Item {
	double healthMod;
	Food(std::string n, double v, double h);
};

struct FoodR_Component {
	Food f;
	int q;
};

struct FoodRecipe {
	vector<FoodR_Component> components;
	vector<bool> collected;
	vector<int> invIndices;
	bool craftable;
	Food product;
	FoodRecipe(vector<FoodR_Component> comp, Food prod);
	void InitVectors();
	void CheckCollection();
};

struct Armor : Item {
	double armorMod;
	WeaponType weakness;
	WeaponType resistance;
	ArmorType armorType;
	Armor(std::string n, double v, double a, WeaponType we, WeaponType r, ArmorType t);
};

struct ArmorRecipe {
	vector<ItemR_Component> components;
	Armor base;
	vector<bool> collected;
	vector<int> invIndices;
	bool baseCollected;
	bool craftable;
	Armor product;
	ArmorRecipe(vector<ItemR_Component> comp, Armor b, Armor prod);
	void InitVectors();
	void CheckCollection();
};

struct Weapon : Item {
	double damageMod;
	WeaponType weaponType;
	int magicDrain = 0;
	Weapon(std::string n, double v, double d, WeaponType t);
	Weapon(std::string n, double v, double d, int m, WeaponType t);
};

struct WeaponRecipe {
	vector<ItemR_Component> components;
	Weapon base;
	vector<bool> collected;
	vector<int> invIndices;
	bool baseCollected;
	bool craftable;
	Weapon product;
	WeaponRecipe(vector<ItemR_Component> comp, Weapon base, Weapon prod);
	void InitVectors();
	void CheckCollection();
};

//Items
extern Item NoItem;
extern Item GoldBar;
extern Item OldBrick;
extern Item Stick;
extern Item Leaf;
extern Item Branch;
extern Item BobcatFur;
extern Item FlamingScale;

//Item Recipes
extern ItemRecipe BranchRecipe;

//Food
extern Food NoFood;
extern Food Apple;
extern Food Pear;
extern Food Banana;
extern Food FruitSalad;

//Food Recipes
extern FoodRecipe FruitSaladRecipe;

//Armor
extern Armor NoArmor;
extern Armor LeatherCap, LeatherTunic, LeatherBracers, LeatherGreaves, LeatherBoots;
extern Armor IronHelmet, IronChestplate, IronGauntlets, IronGreaves, IronSabatons;
extern Armor GLChestplate;

//Armor Recipes
extern ArmorRecipe GLChestplateRecipe;

//Creature Armor
extern Armor CrimsonScales;
extern Armor DemonHide;
extern Armor RockHide;

//Weapons
extern Weapon NoWeapon;
extern Weapon CarvingKnife;
extern Weapon IronDagger;
extern Weapon IronSword;
extern Weapon IronHammer;
extern Weapon IronAxe;
extern Weapon Telekinesis;
extern Weapon WoodenSpear;
extern Weapon FlamesteelDagger;
extern Weapon FlamesteelSword;
extern Weapon FlamesteelHammer;
extern Weapon FlamesteelAxe;
extern Weapon Fireball;
extern Weapon LargeClub;
extern Weapon UnholyBlade;
extern Weapon GCKnife;
extern Weapon RockClub;

//Weapon Recipes
extern WeaponRecipe GCKnifeRecipe;

//Creature Weapons
extern Weapon Claws;
extern Weapon FireBreath;
extern Weapon RockPummel;

//Item Lists
extern vector<Item> noItemDrops;
extern vector<Item> plainsItems_C;
extern vector<Item> plainsItems_R;

//Food Lists
extern vector<Food> noFoodDrops;
extern vector<Food> plainsFood_C;
extern vector<Food> plainsFood_R;

//Armor Lists
extern vector<Armor> lvl1Armor;
extern vector<Armor> lvl2Armor;

//Weapon Lists
extern vector<Weapon> lvl1Weapon;
extern vector<Weapon> lvl2Weapon;

//Recipe Lists
extern vector<ItemRecipe*> itemRecipes;
extern vector<FoodRecipe*> foodRecipes;
extern vector<ArmorRecipe*> armorRecipes;
extern vector<WeaponRecipe*> weaponRecipes;

#endif /* ITEMS_H_ */
