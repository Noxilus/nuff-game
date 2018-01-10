#include "Items.h"

Item::Item(std::string n, double v, ItemType t) : name(n), value(v), itemType(t){}

ItemRecipe::ItemRecipe(vector<ItemR_Component> comp, Item prod) : components(comp), collected({false}), invIndices({0}), craftable(false), product(prod){}

void ItemRecipe::InitVectors(){
	int numComponents = components.size();
	for (int i = 1; i < numComponents; i++){
		collected.push_back(false);
		invIndices.push_back(0);
	}
}

void ItemRecipe::CheckCollection(){
	int numComponents = components.size();
	int completed = 0;
	for (int i = 0; i < numComponents; i++){
		if (collected[i] == true){
			completed++;
		}
	}
	if (completed == numComponents){
		craftable = true;
	}
	else
	{
		craftable = false;
	}
}

Food::Food(std::string n, double v, double h) : Item(n, v, FoodItem), healthMod(h){}
FoodRecipe::FoodRecipe(vector<FoodR_Component> comp, Food prod) : components(comp), collected({false}), invIndices({0}), craftable(false), product(prod){}

void FoodRecipe::InitVectors(){
	int numComponents = components.size();
	for (int i = 1; i < numComponents; i++){
		collected.push_back(false);
		invIndices.push_back(0);
	}
}

void FoodRecipe::CheckCollection(){
	int numComponents = components.size();
	int completed = 0;
	for (int i = 0; i < numComponents; i++){
		if (collected[i] == true){
		completed++;
		}
	}
	if (completed == numComponents){
		craftable = true;
	}
	else
	{
		craftable = false;
	}
}

Armor::Armor(std::string n, double v, double a, WeaponType we, WeaponType r, ArmorType t) : Item(n, v, ArmorItem), armorMod(a), weakness(we), resistance(r), armorType(t){}
ArmorRecipe::ArmorRecipe(vector<ItemR_Component> comp, Armor b, Armor prod) : components(comp), base(b), collected({false}), invIndices({0}), baseCollected(false), craftable(false), product(prod){}

void ArmorRecipe::InitVectors(){
	int numComponents = components.size();
	for (int i = 1; i < numComponents; i++){
		collected.push_back(false);
	}
}

void ArmorRecipe::CheckCollection(){
	int numComponents = components.size();
	int completed = 0;
	for (int i = 0; i < numComponents; i++){
		if (collected[i] == true){
			completed++;
		}
	}
	if (completed == numComponents){
		craftable = true;
	}
	else
	{
		craftable = false;
	}
}

Weapon::Weapon(std::string n, double v, double d, WeaponType t) : Item(n, v, WeaponItem), damageMod(d), weaponType(t){}
Weapon::Weapon(std::string n, double v, double d, int m, WeaponType t) : Item(n, v, WeaponItem), damageMod(d), weaponType(t), magicDrain(m){}
WeaponRecipe::WeaponRecipe(vector<ItemR_Component> comp, Weapon b, Weapon prod) : components(comp), base(b), collected({false}), invIndices({0}), baseCollected(false), craftable(false), product(prod){}

void WeaponRecipe::InitVectors(){
	int numComponents = components.size();
	for (int i = 1; i < numComponents; i++){
		collected.push_back(false);
	}
}

void WeaponRecipe::CheckCollection(){
	int numComponents = components.size();
	int completed = 0;
	for (int i = 0; i < numComponents; i++){
		if (collected[i] == true){
			completed++;
		}
	}
	if (completed == numComponents){
		craftable = true;
	}
	else
	{
		craftable = false;
	}
}

//Items
Item NoItem = Item("No Item", 0, NoItemType);
Item GrassTuft = Item("Tuft of Grass", 1, Misc);
Item GoldBar = Item("Gold Bar", 1500, Misc);
Item OldBrick = Item("Old Brick", 20, Misc);
Item Stick = Item("Stick", 1, Misc);
Item Leaf = Item("Leaf", 1, Misc);
Item Branch = Item("Branch", 10, Misc);
Item BobcatFur = Item("Bobcat Fur", 40, Misc);
Item FlamingScale = Item("Flaming Scale", 600, Misc);

//Item Recipes
ItemRecipe BranchRecipe = ItemRecipe({{Stick, 2}, {Leaf, 4}}, Branch);

//Food
Food NoFood = Food("No Food", 0, 0);
Food Apple = Food("Apple", 5, 10);
Food Pear = Food("Pear", 7, 8);
Food Banana = Food("Banana", 10, 15);
Food FruitSalad = Food("Fruit Salad", 150, 2000);

//Food Recipes
FoodRecipe FruitSaladRecipe = FoodRecipe({{Apple, 5}, {Pear, 5}, {Banana, 5}},
FruitSalad);

//Armor
Armor NoArmor = Armor("No Armor", 0, 0, NoWeaponType, NoWeaponType, NoArmorType);
Armor LeatherCap = Armor("Leather Cap", 30, 0.5, Dagger, Hammer, Helmet);
Armor LeatherTunic = Armor("Leather Tunic", 50, 0.5, Dagger, Hammer, Tunic);
Armor LeatherBracers = Armor("Leather Bracers", 50, 0.5, Dagger, Hammer, Gauntlets);
Armor LeatherGreaves = Armor("Leather Greaves", 50, 0.5, Dagger, Hammer, Pants);
Armor LeatherBoots = Armor("Leather Boots", 50, 0.5, Dagger, Hammer, Boots);
Armor IronHelmet = Armor("Iron Helmet", 60, 0.6, Hammer, Dagger, Helmet);
Armor IronChestplate = Armor("Iron Chestplate", 60, 0.6, Hammer, Dagger, Chestplate);
Armor IronGauntlets = Armor("Iron Gauntlets", 60, 0.6, Hammer, Dagger, Gauntlets);
Armor IronGreaves = Armor("Iron Greaves", 60, 0.6, Hammer, Dagger, Greaves);
Armor IronSabatons = Armor("Iron Sabatons", 60, 0.6, Hammer, Dagger, Sabatons);
Armor GLChestplate = Armor("Golden Leather Chestplate", 3100, 1.2, Hammer, Axe, Chestplate);

//Armor Recipes
ArmorRecipe GLChestplateRecipe = ArmorRecipe({{GoldBar, 2}}, LeatherTunic, GLChestplate);

//Creature Armor
Armor CrimsonScales = Armor("Crimson Scales", 100, 0.4, Axe, Sword, CreatureArmor);
Armor DemonHide = Armor("Demon Hide", 100, 0.3, Sword, Hammer, CreatureArmor);
Armor RockHide = Armor("Rock Hide", 100, 0.5, Hammer, Sword, CreatureArmor);

//Weapons
Weapon NoWeapon = Weapon("No Weapon", 0, 0, NoWeaponType);
Weapon CarvingKnife = Weapon("Carving Knife", 50, 10, Dagger);
Weapon IronDagger = Weapon("Iron Dagger", 60, 20, Dagger);
Weapon IronSword = Weapon("Iron Sword", 60, 20, Sword);
Weapon IronHammer = Weapon("Iron Hammer", 60, 20, Hammer);
Weapon IronAxe = Weapon("Iron Axe", 60, 20, Axe);
Weapon Telekinesis = Weapon("Spell of Telekinesis", 90, 30, 40, Spell);
Weapon WoodenSpear = Weapon("Wooden Spear", 40, 15, Spear);
Weapon FlamesteelDagger = Weapon("Flamesteel Dagger", 120, 40, Dagger);
Weapon FlamesteelSword = Weapon("Flamesteel Sword", 120, 40, Sword);
Weapon FlamesteelHammer = Weapon("Flamesteel Hammer", 120, 40, Hammer);
Weapon FlamesteelAxe = Weapon("Flamesteel Axe", 120, 40, Axe);
Weapon Fireball = Weapon("Spell of Fireball", 180, 60, 50, Spell);
Weapon LargeClub = Weapon("Large Club", 100, 30, Hammer);
Weapon UnholyBlade = Weapon("Unholy Blade", 400, 20, Sword);
Weapon GCKnife = Weapon("Golden Carving Knife", 1700, 80, Dagger);
Weapon RockClub = Weapon("Rock Club", 900, 90, Hammer);

//Weapon Recipes
WeaponRecipe GCKnifeRecipe = WeaponRecipe({{GoldBar, 1}}, CarvingKnife, GCKnife);

//Creature Weapons
Weapon Claws = Weapon("Claws", 0, 15, CreatureWeapon);
Weapon FireBreath = Weapon("Fire Breath", 0, 25, CreatureWeapon);
Weapon RockPummel = Weapon("Rock Pummelling", 0, 25, CreatureWeapon);

//Item Lists
vector<Item> noItemDrops = {};
vector<Item> plainsItems_C = {GrassTuft, OldBrick, Stick, Leaf};
vector<Item> plainsItems_R = {GoldBar};

//Food Lists
vector<Food> noFoodDrops = {};
vector<Food> plainsFood_C = {Apple, Pear};
vector<Food> plainsFood_R = {Banana};

//Armor Lists
vector<Armor> lvl1Armor = {LeatherCap, LeatherTunic, LeatherBracers, LeatherGreaves, LeatherBoots};
vector<Armor> lvl2Armor = {IronHelmet, IronChestplate, IronGauntlets, IronGreaves, IronSabatons};

//Weapon Lists
vector<Weapon> lvl1Weapon = {IronDagger, IronSword, IronHammer, IronAxe, Telekinesis};
vector<Weapon> lvl2Weapon = {FlamesteelDagger, FlamesteelSword, FlamesteelHammer, FlamesteelAxe, Fireball};

//Recipe Lists
vector<ItemRecipe*> itemRecipes = {&BranchRecipe};
vector<FoodRecipe*> foodRecipes = {&FruitSaladRecipe};
vector<ArmorRecipe*> armorRecipes = {&GLChestplateRecipe};
vector<WeaponRecipe*> weaponRecipes = {&GCKnifeRecipe};
