#include "Character.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Items.h"
#include "Maps.h"
#include "NPC.h"
#include "ScreenHandler.h"

using namespace std;

BaseId::BaseId(double h, double m, double a, double r){
	healthMod = h;
	magicMod = m;
	agilityMod = a;
	strengthMod = r;
}

ClassIdentifier::ClassIdentifier(double h, double m, double a, double r, ClassType t) : BaseId(h, m, a, r), type(t){}

ClassIdentifier NoClass = ClassIdentifier(0, 0, 0, 0, NoClassType);
ClassIdentifier KnightClass = ClassIdentifier(0, 0, 10, -10, Knight);
ClassIdentifier WarriorClass = ClassIdentifier(0, 0, -10, 10, Warrior);
ClassIdentifier ThiefClass = ClassIdentifier(-10, 0, 10, 0, Thief);
ClassIdentifier BlacksmithClass = ClassIdentifier(0, -10, 0, 10, Blacksmith);
ClassIdentifier LumberjackClass = ClassIdentifier(0, 0, -10, 0, Lumberjack);
ClassIdentifier MageClass = ClassIdentifier(0, 10, 0, -10, Mage);
ClassIdentifier ArcherClass = ClassIdentifier(10, 0, -10, 0, Archer);

RaceIdentifier::RaceIdentifier(double h, double m, double a, double r, RaceType t) : BaseId(h, m, a, r), type(t){}

RaceIdentifier NoRace = RaceIdentifier( 0, 0, 0, 0, NoRaceType);
RaceIdentifier HumanRace = RaceIdentifier( 20, 0, 5, -10, NoRaceType);
RaceIdentifier WoodElfRace = RaceIdentifier( 5, 10, 10, -15, NoRaceType);
RaceIdentifier OrcRace = RaceIdentifier( 0, -5, -10, 15, NoRaceType);
RaceIdentifier DarkElfRace = RaceIdentifier( 0, 10, 15, -10, NoRaceType);
RaceIdentifier DragonlingRace = RaceIdentifier( -5, 15, 10, 0, NoRaceType);
RaceIdentifier DwarfRace = RaceIdentifier( 5, -10, -5, 10, NoRaceType);

Character::Character() :
		head(armorSlot),
		torso(armorSlot),
		arms(armorSlot),
		legs(armorSlot),
		feet(armorSlot),

		primary(WeaponSlot(CarvingKnife)),
		secondary(weaponSlot),

		charClass(NoClass),
		charRace(NoRace),

		curMap(&highashPlainsA),
		name(""),
		curX(8),
		curY(1),
		gold(0),
		health(200),
		magic(200),
		strength(50),
		agility(50),

		curHealth(health),
		curMagic(magic),
		curStrength(strength),
		curAgility(agility),
		gameOver(false),
		paused(false)
{
	InvSlot inventory[30] = {invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot};
	FoodSlot foodInv[10] = {foodSlot, foodSlot, foodSlot, foodSlot, foodSlot, foodSlot, foodSlot, foodSlot, foodSlot, foodSlot};
}

Character::~Character(){
	delete curMap;
}

void Character::SetName(string n){
	name = n;
	secondary.weapon.name = "Bare Hands";
}

void Character::SetClass(ClassIdentifier newClass){
	charClass = newClass;
}

void Character::SetRace(RaceIdentifier newRace){
	charRace = newRace;
}

void Character::SetStats(){
	double healthMult, magicMult, strengthMult, agilityMult;
	healthMult = (charClass.healthMod + charRace.healthMod + 100)/100;
	magicMult = (charClass.magicMod + charRace.magicMod + 100)/100;
	strengthMult = (charClass.strengthMod + charRace.strengthMod + 100)/100;
	agilityMult = (charClass.agilityMod + charRace.agilityMod + 100)/100;

	health *= healthMult;
	magic *= magicMult;
	strength*= strengthMult;
	agility *= agilityMult;

	curHealth = health;
	curMagic = magic;
	curStrength = strength;
	curAgility = agility;
}

void Character::DisplayStats(){
	cout << "\nStatOverview:" << endl;
	cout << "\nHealth: " << curHealth << "/" << health << "\nMagic: " << curMagic << "/" <<magic << "\nStrength: " << curStrength << "/" << strength << "\nAgility: " << agility << endl;
}

void Character::UseItem(ItemType type, int slotNum, int quantity){
	if (type == FoodItem){
		FoodSlot* target = &foodInv[slotNum];
		if (curHealth + (target->food.healthMod*quantity) > health){
			curHealth = health;
		}
		else
		{
			curHealth += target->food.healthMod*quantity;
		}
		UpdateMap();
		cout << "Ate " << quantity << " " << target->food.name << "(s)." << endl;

		if (target->quantity - quantity == 0){
			target->food = NoFood;
			target->quantity -= 1;
		}
		else
		{
			target->quantity -= quantity;
		}
	}
	else if (type == Misc){
		InvSlot* target = &inventory[slotNum];
		if (target->quantity - quantity == 0){
			target = &invSlot;
		}
		else
		{
			target->quantity -= quantity;
		}
	}
}

void Character::EquipArmor(Armor toEquip){
	ArmorSlot* target = &head;
	ArmorType t = toEquip.armorType;
	if (t == Helmet){
		target = &head;
	}
	else if (t == Tunic || t == Chestplate){
		target = &torso;
	}
	else if (t == Bracers || t == Gauntlets){
		target = &arms;
	}
	else if (t == Pants || t == Greaves){
		target = &legs;
	}
	else if (t == Sabatons || t == Boots){
		target = &feet;
	}
	cout << "Picked up " << toEquip.name << "!" << endl;
	target->SetArmor(toEquip);
}

void Character::UnequipArmor(ArmorSlot* toUnequip){
	toUnequip->armor = NoArmor;
}

void Character::EquipWeapon(Weapon toEquip){
	int choice;
	cout << "Picked up " << toEquip.name << "!" << endl;
	cout << "Current primary weapon: " << primary.weapon.name << "\nCurrent secondary weapon: " << secondary.weapon.name << "\nTo which slot would you like to equip " << toEquip.name << "?\n1. Primary\n2.Secondary" << endl;
	cin >> choice;
	if (choice == 1){
		primary.SetWeapon(toEquip);
	}
	else
	{
		secondary.SetWeapon(toEquip);
	}
}

void Character::UnequipWeapon(WeaponSlot* toUnequip){
	toUnequip->weapon = NoWeapon;
}

void Character::AddItemToInv(Item item, int quantity){
	cout << "Adding: " << item.name << " x" << quantity << "\nEnter the slot for adding the item(s):" << endl;
	int i;
	cin >> i;
	i--;
	InvSlot target = inventory[i];
	if (target.item.name == "No Item"){
		inventory[i] = InvSlot(item, quantity);
	}
	else if (target.item.name == item.name){
		inventory[i].quantity += quantity;
	}
	else
	{
		int swap;
		cout << "Slot full! Swap out " << inventory[i].item.name << " for " << item.name << "? " << inventory[i].item.name << " will be lost forever.\n1. Yes\n2. No" << endl;
		cin >> swap;
		if (swap == 1){
			inventory[i] = InvSlot(item, quantity);
		}
		else
		{
			AddItemToInv(item, quantity);
		}
	}
	cout << "Added " << item.name << " x" << quantity << " to inventory!" << endl;
}

void Character::RemoveItemFromInv(InvSlot* slot, int quantity){
	if (slot->quantity - quantity == 0){
		slot->item = NoItem;
	}
	slot->quantity -= quantity;
}

void Character::AddFoodToInv(Food food, int quantity){
	cout << "Adding: " << food.name << " x" << quantity << "\nEnter the slot for adding the food:" << endl;
	int i;
	cin >> i;
	i--;
	FoodSlot target = foodInv[i];
	if (target.food.name == "No Food"){
		foodInv[i] = FoodSlot(food, quantity);
	}
	else if (target.food.name == food.name){
		foodInv[i].quantity += quantity;
	}
	else
	{
		int swap;
		cout << "Slot full! Swap out " << foodInv[i].food.name << " for " << food.name << "? " << foodInv[i].food.name << " will be lost forever.\n1. Yes\n2. No" << endl;
		cin >> swap;
		if (swap == 1){
			foodInv[i] = FoodSlot(food, quantity);
		}
		else
		{
			AddFoodToInv(food, quantity);
		}
	}
	cout << "Added " << food.name << " x" << quantity << " to inventory!" << endl;
}

void Character::RemoveFoodFromInv(FoodSlot* slot, int quantity){
	if (slot->quantity - quantity == 0){
		slot->food = NoFood;
	}
	slot->quantity -= quantity;
}

void Character::AddGold(int g){
	gold += g;
}

void Character::SwapOutArmor(Armor a, ArmorSlot* slot){
	slot->armor = a;
}

void Character::SwapOutWeapon(Weapon w, WeaponSlot* slot){
	slot->weapon = w;
}

void Character::DisplayInv(string type){
	if (type == "inventory"){
		cout << "Inventory:" << endl;
		for (int i = 0; i < 30; i++){
			InvSlot curSlot = inventory[i];
			cout << i+1 << ". " << curSlot.item.name << " x" << curSlot.quantity << endl;
		}
	}
	else if (type == "food"){
		cout << "Food:" << endl;
		for (int i = 0; i < 10; i++){
			FoodSlot curSlot = foodInv[i];
			cout << i+1 << ". " << curSlot.food.name << " x" << curSlot.quantity << endl;
		}
	}
}

void Character::ResetPos(int x, int y){
	curX = x;
	curY = y;
}

void Character::MoveHandler(){
	Action d = sHandler.GetDir();
	if (d == Pause){
		paused = true;
		PauseMenu();
		cout << "Hit an arrow key to move." << endl;
	}
	else if (d == Eat){
		EatFood();
		cout << "Hit an arrow key to move." << endl;
	}
	else if (d == Forage){
		ForageTile();
		cout << "Hit an arrow key to move." << endl;
	}
	else if (d == Up && curMap->layout[curX-1][curY] != '#'){
		if (curMap->layout[curX-1][curY] == 'S'){
			NPCInteraction(curMap->smith);
		}
		else if (curMap->layout[curX-1][curY] == 'H'){
			NPCInteraction(curMap->host);
		}
		else if (curMap->layout[curX-1][curY] == 'V'){
			NPCInteraction(curMap->vendor);
		}
		else if (curMap->layout[curX-1][curY] == 'C'){
			CraftHandler();
		}
		else if (curMap->layout[curX-1][curY] == 'B'){
			BossInteraction(Up);
		}
		else
		{
			curMap->layout[curX][curY] = ' ';
			curX--;
			Move();
		}
	}
	else if (d == Down && curMap->layout[curX+1][curY] != '#'){
		if (curMap->layout[curX+1][curY] == 'S'){
			NPCInteraction(curMap->smith);
		}
		else if (curMap->layout[curX+1][curY] == 'H'){
			NPCInteraction(curMap->host);
		}
		else if (curMap->layout[curX+1][curY] == 'V'){
			NPCInteraction(curMap->vendor);
		}
		else if (curMap->layout[curX+1][curY] == 'C'){
			CraftHandler();
		}
		else if (curMap->layout[curX+1][curY] == 'B'){
			BossInteraction(Down);
		}
		else
		{
			curMap->layout[curX][curY] = ' ';
			curX++;
			Move();
		}
	}
	else if (d == Left && curMap->layout[curX][curY-1] != '#'){
		if (curMap->layout[curX][curY-1] == 'S'){
			NPCInteraction(curMap->smith);
		}
		else if (curMap->layout[curX][curY-1] == 'H'){
			NPCInteraction(curMap->host);
		}
		else if (curMap->layout[curX][curY-1] == 'V'){
			NPCInteraction(curMap->vendor);
		}
		else if (curMap->layout[curX][curY-1] == 'C'){
			CraftHandler();
		}
		else if (curMap->layout[curX][curY-1] == 'B'){
			BossInteraction(Left);
		}
		else
		{
			curMap->layout[curX][curY] = ' ';
			curY--;
			Move();
		}
	}
	else if (d == Right && curMap->layout[curX][curY+1] != '#'){
		if (curMap->layout[curX][curY+1] == 'S'){
			NPCInteraction(curMap->smith);
		}
		else if (curMap->layout[curX][curY+1] == 'H'){
			NPCInteraction(curMap->host);
		}
		else if (curMap->layout[curX][curY+1] == 'V'){
			NPCInteraction(curMap->vendor);
		}
		else if (curMap->layout[curX][curY+1] == 'C'){
			CraftHandler();
		}
		else if (curMap->layout[curX][curY+1] == 'B'){
			BossInteraction(Right);
		}
		else
		{
			curMap->layout[curX][curY] = ' ';
			curY++;
			Move();
		}
	}
}

void Character::TileEvent(char tile){
	if (tile == 'E'){
		//Combat
		srand((unsigned) time(NULL));
		int enemyIndex = rand() % curMap->enemyList.size();
		combat.CombatLoop(curMap->enemyList[enemyIndex]);
	}
	else if (tile == 'G'){
		//Gold
		srand((unsigned) time(NULL));
		int goldAddition = rand() % 6 + 5;
		AddGold(goldAddition);
		cout << "Picked up " << goldAddition << " gold!\nTotal Gold: " <<
		gold << "\n";
	}
	else if (tile == 'D'){
		//Item Drop (Miscellaneous, consumable)
		srand((unsigned) time(NULL));
		int iType = rand() % 2;
		if (iType == 0){
			DisplayInv("inventory");
			ItemDrop();
		}
		else
		{
			DisplayInv("food");
			FoodDrop();
		}
	}
	else if (tile == 'R'){
		//Reward Drop (Armor, weapon)
		GearDrop();
	}
}

void Character::ItemDrop(){
	srand((unsigned) time(NULL));
	vector<Item> list;
	int rarity = rand() % 20;
	if (rarity >= 19){
		list = curMap->rareItems;
	}
	else
	{
		list = curMap->commonItems;
	}

	int i = rand() % list.size();
	int q = rand() % 3 + 1;
	AddItemToInv(list[i], q);
}

void Character::FoodDrop(){
	srand((unsigned) time(NULL));
	vector<Food> list;
	int rarity = rand() % 20;
	if (rarity >= 19){
		list = curMap->rareFood;
	}
	else
	{
		list = curMap->commonFood;
	}

	int i = rand() % list.size();
	int q = rand() % 3 + 1;
	AddFoodToInv(list[i], q);
}

void Character::GearDrop(){
	vector<Armor> armorDrops;
	vector<Weapon> weaponDrops;
	switch(curMap->level){
		case 1:
			armorDrops = lvl1Armor;
			weaponDrops = lvl1Weapon;
			break;
		case 2:
			armorDrops = lvl2Armor;
			weaponDrops = lvl2Weapon;
			break;
		default:
			armorDrops = lvl1Armor;
			weaponDrops = lvl1Weapon;
			break;
	}
	srand((unsigned) time(NULL));
	switch(rand() % 2){
		case 0:
			EquipArmor(armorDrops[rand() % armorDrops.size()]);
			break;
		case 2:
			EquipWeapon(weaponDrops[rand() % weaponDrops.size()]);
			break;
		default:
			EquipArmor(armorDrops[rand() % armorDrops.size()]);
			break;
	}
}

void Character::NPCInteraction(NPC* npc){
	int interaction;
	cout << "You are greeted by " << npc->FullName() << ".\n" << npc->name
	<< ": How may I help you?\n";
	if (npc->type == Smith){
		cout << "1. Buy/Sell Weapons\n2. Buy/Sell Armor\n";
		cin >> interaction;
		if (interaction == 1){
			while (true){
				TradePrompt(npc, WeaponItem);
				cout << "Would you like to do more business?\n1. Yes\n2. No\n";
				int c;
				cin >> c;
				if (c != 1){
				break;
				}
			}
		}
		else
		{
			while (true){
				TradePrompt(npc, ArmorItem);
				cout << "Would you like to do more business?\n1. Yes\n2.No\n";
				int c;
				cin >> c;
				if (c != 1){
					break;
				}
			}
		}
	}
	else if (npc->type == Host){
		cout << "1. Buy/Sell Food\n2. Heal\n";
		cin >> interaction;
		if (interaction == 1){
			while (true){
				TradePrompt(npc, FoodItem);
				cout << "Would you like to do more business?\n1. Yes\n2. No\n";
				int c;
				cin >> c;
				if (c != 1){
					break;
				}
			}
		}
		else
		{
			int leftToHeal = health - curHealth;
			int cost = (leftToHeal - (leftToHeal % 10)) / 10;
			cout << "I can heal you up, but it will cost you " << cost << " gold. Would you like to heal?\n1. Yes\n2. No\n";
			int heal;
			cin >> heal;
			if (heal == 1){
				if (gold - cost > 0){
					cout << "Healed up to max health!\n";
					curHealth = health;
					gold -= cost;
				}
				else
				{
					cout << "You don't have enough money for that. Come back later when you have more coin.";
				}
			}
		}
	}
	else if (npc->type == Vendor){
		while (true){
			TradePrompt(npc, Misc);
			cout << "Would you like to do more business?\n1. Yes\n2. No\n";
			int c;
			cin >> c;
			if (c != 1){
				break;
			}
		}
	}
	UpdateMap();
	cout << "Hit an arrow key to move.\n";
}

void Character::CraftHandler(){
	int craftChoice;
	cout << "Would you like to forge a weapon (1), assemble armor (2), cook food (3), or craft an item (4)? - Quit (0)\n";
	cin >> craftChoice;
	switch (craftChoice){
		case 1:
			CraftWeapon();
			break;
		case 2:
			CraftArmor();
			break;
		case 3:
			CraftFood();
			break;
		case 4:
			CraftItem();
			break;
		case 0:
			break;
	}
	cout << "Hit an arrow key to move.\n";
}

void Character::CraftWeapon(){
	int numRecipes = weaponRecipes.size();
	int numCraftable = 0;
	vector<WeaponRecipe*> craftableRecipes;
	int numComponents;
	WeaponSlot* slot;
	for (int i = 0; i < numRecipes; i++){
		slot = ScanInventory(weaponRecipes[i]);
		if (weaponRecipes[i]->craftable == true){
			craftableRecipes.push_back(weaponRecipes[i]);
			numCraftable++;
		}
	}
	if (numCraftable == 0){
		cout << "You don't have enough materials to craft anything at this time.\n";
	}
	else
	{
		int craftChoice;
		cout << "Choose a recipe:\n";
		for (int i = 0; i < numCraftable; i++){
			numComponents = craftableRecipes[i]->components.size();
			cout << i+1 << ". " << craftableRecipes[i]->product.name;
			for (int j = 0; j < numComponents; j++){
				cout << " " << craftableRecipes[i]->components[j].i.name << " x" << craftableRecipes[i]->components[j].q;
			}
			cout << " " << craftableRecipes[i]->base.name << "\n";
		}
		cin >> craftChoice;
		if (craftChoice > numCraftable){
			craftChoice = numCraftable;
		}
		else if (craftChoice < 0){
			craftChoice = 1;
		}

		if (craftChoice != 0){
			GatherItems(craftableRecipes[craftChoice-1]);
			slot->weapon = craftableRecipes[craftChoice-1]->product;
		}
	}
}

void Character::CraftArmor(){
	int numRecipes = armorRecipes.size();
	int numCraftable = 0;
	vector<ArmorRecipe*> craftableRecipes;
	int numComponents;
	ArmorSlot* slot = armorInv[0];
	for (int i = 0; i < numRecipes; i++){
		slot = ScanInventory(armorRecipes[i]);
		if (armorRecipes[i]->craftable == true){
			craftableRecipes.push_back(armorRecipes[i]);
			numCraftable++;
		}
	}
	if (numCraftable == 0){
		cout << "You don't have enough materials to craft anything at this time.\n";
	}
	else
	{
		int craftChoice;
		cout << "Choose a recipe:\n";
		for (int i = 0; i < numCraftable; i++){
			numComponents = craftableRecipes[i]->components.size();
			cout << i+1 << ". " << craftableRecipes[i]->product.name;
			for (int j = 0; j < numComponents; j++){
				cout << " " <<
				craftableRecipes[i]->components[j].i.name << " x" <<
				craftableRecipes[i]->components[j].q;
			}
			cout << " " << craftableRecipes[i]->base.name << "\n";
		}
		cin >> craftChoice;
		if (craftChoice > numCraftable){
			craftChoice = numCraftable;
		}
		else if (craftChoice < 0){
			craftChoice = 1;
		}
		if (craftChoice != 0){
			GatherItems(craftableRecipes[craftChoice-1]);
			slot->armor = craftableRecipes[craftChoice-1]->product;
		}
	}
}

void Character::CraftItem(){
	int numRecipes = itemRecipes.size();
	int numCraftable = 0;
	vector<ItemRecipe*> craftableRecipes;
	int numComponents;
	for (int i = 0; i < numRecipes; i++){
		ScanInventory(itemRecipes[i]);
		if (itemRecipes[i]->craftable == true){
			craftableRecipes.push_back(itemRecipes[i]);
			numCraftable++;
		}
	}
	if (numCraftable == 0){
		cout << "You don't have enough materials to craft anything at this ntime.\n";
	}
	else
	{
		int craftChoice;
		cout << "Choose a recipe:\n";
		for (int i = 0; i < numCraftable; i++){
			numComponents = craftableRecipes[i]->components.size();
			cout << i+1 << ". " << craftableRecipes[i]->product.name;
			for (int j = 0; j < numComponents; j++){
				cout << " " << craftableRecipes[i]->components[j].i.name << " x" << craftableRecipes[i]->components[j].q;
			}
			cout << "\n0. Quit\n";
		}
		cin >> craftChoice;
		if (craftChoice > numCraftable){
			craftChoice = numCraftable;
		}
		else if (craftChoice < 0){
			craftChoice = 1;
		}
		if (craftChoice != 0){
			GatherItems(craftableRecipes[craftChoice-1]);
			AddItemToInv(craftableRecipes[craftChoice-1]->product, 1);
		}
	}
}

void Character::CraftFood(){
	int numRecipes = foodRecipes.size();
	int numCraftable = 0;
	vector<FoodRecipe*> craftableRecipes;
	int numComponents;
	for (int i = 0; i < numRecipes; i++){
		ScanInventory(foodRecipes[i]);
		if (foodRecipes[i]->craftable == true){
			craftableRecipes.push_back(foodRecipes[i]);
			numCraftable++;
		}
	}
	if (numCraftable == 0){
		cout << "You don't have enough materials to craft anything at this time.\n";
	}
	else
	{
		int craftChoice;
		cout << "Choose a recipe:\n";
		for (int i = 0; i < numCraftable; i++){
			numComponents = craftableRecipes[i]->components.size();
			cout << i+1 << ". " << craftableRecipes[i]->product.name;
			for (int j = 0; j < numComponents; j++){
				cout << " " << craftableRecipes[i]->components[j].f.name << " x" << craftableRecipes[i]->components[j].q;
			}
			cout << "\n";
		}
		cin >> craftChoice;
		if (craftChoice > numCraftable){
			craftChoice = numCraftable;
		}
		else if (craftChoice < 0){
			craftChoice = 1;
		}
		if (craftChoice != 0){
			GatherItems(craftableRecipes[craftChoice-1]);
			AddItemToInv(craftableRecipes[craftChoice-1]->product, 1);
		}
	}
}

void Character::ScanInventory(ItemRecipe* recipe){
	int numComponents = recipe->components.size();
	for (int i = 0; i < numComponents; i++){
		for (int j = 0; j < 30; j++){
			if (inventory[j].item.name == recipe->components[i].i.name && inventory[j].quantity >= recipe->components[i].q){
				recipe->collected[i] = true;
				recipe->invIndices[i] = j;
				break;
			}
		}
	}
	recipe->CheckCollection();
}

void Character::ScanInventory(FoodRecipe* recipe){
	int numComponents = recipe->components.size();
	for (int i = 0; i < numComponents; i++){
		for (int j = 0; j < 10; j++){
			if (foodInv[j].food.name == recipe->components[i].f.name && foodInv[j].quantity >= recipe->components[i].q){
				recipe->collected[i] = true;
				recipe->invIndices[i] = j;
				break;
			}
		}
	}
	recipe->CheckCollection();
}

ArmorSlot* Character::ScanInventory(ArmorRecipe* recipe){
	int numComponents = recipe->components.size();
	for (int i = 0; i < numComponents; i++){
		for (int j = 0; j < 30; j++){
			if (inventory[j].item.name == recipe->components[i].i.name && inventory[j].quantity >= recipe->components[i].q){
			recipe->collected[i] = true;
			recipe->invIndices[i] = j;
			break;
			}
		}
	}
	if (recipe->base.name != ""){
		for (int i = 0; i < 5; i++){
			if (armorInv[i]->armor.name == recipe->base.name){
				recipe->baseCollected = true;
				recipe->CheckCollection();
				return armorInv[i];
			}
		}
	}
	else
	{
		recipe->baseCollected = true;
		recipe->CheckCollection();
		return &armorSlot;
	}
	return &armorSlot;
}

WeaponSlot* Character::ScanInventory(WeaponRecipe* recipe){
	int numComponents = recipe->components.size();
	for (int i = 0; i < numComponents; i++){
		for (int j = 0; j < 30; j++){
			if (inventory[j].item.name == recipe->components[i].i.name && inventory[j].quantity >= recipe->components[i].q){
				recipe->collected[i] = true;
				recipe->invIndices[i] = j;
				break;
			}
		}
	}
	if (recipe->base.name != ""){
		for (int i = 0; i < 2; i++){
			if (weaponInv[i]->weapon.name == recipe->base.name){
				recipe->baseCollected = true;
				recipe->CheckCollection();
				return weaponInv[i];
			}
		}
	}
	else
	{
		recipe->baseCollected = true;
		recipe->CheckCollection();
		return &weaponSlot;
	}
	return &weaponSlot;
}

void Character::GatherItems(ItemRecipe* recipe){
	int numComponents = recipe->components.size();
	for (int i = 0; i < numComponents; i++){
		UseItem(Misc, recipe->invIndices[i], recipe->components[i].q);
		recipe->collected[i] = false;
	}
}

void Character::GatherItems(FoodRecipe* recipe){
	int numComponents = recipe->components.size();
	for (int i = 0; i < numComponents; i++){
		UseItem(FoodItem, recipe->invIndices[i], recipe->components[i].q);
		recipe->collected[i] = false;
	}
}

void Character::GatherItems(ArmorRecipe* recipe){
	int numComponents = recipe->components.size();
	for (int i = 0; i < numComponents; i++){
		UseItem(Misc, recipe->invIndices[i], recipe->components[i].q);
		recipe->collected[i] = false;
	}
}

void Character::GatherItems(WeaponRecipe* recipe){
	int numComponents = recipe->components.size();
	for (int i = 0; i < numComponents; i++){
		UseItem(Misc, recipe->invIndices[i], recipe->components[i].q);
		recipe->collected[i] = false;
	}
}

void Character::BossInteraction(Action dir){
	if (curMap->numEnemies > 0){
		cout << "It seems this enemy will not fight until all others in the area are defeated...\n";
		system("pause");
		UpdateMap();
	}
	else
	{
		combat.CombatLoop(curMap->boss);
		if (!gameOver){
			curMap->layout[curX][curY] = ' ';
			if (dir == Up){
				curX--;
			}
			else if (dir == Down){
				curX++;
			}
			else if (dir == Left){
				curY--;
			}
			else if (dir == Right){
				curY++;
			}
			curMap->layout[curX][curY] = '@';
		}
	}
}

int Character::EatSlot(){
	cout << "Enter the slot of the food you would like to eat: ";
	int fslot;
	cin >> fslot;
	if ((fslot <= 0 || fslot > 10) && foodInv[fslot].food.name == "No Food"){
		cout << "That slot does not exist or is not full.\n";
		fslot = EatSlot();
	}
	return fslot - 1;
}

int Character::EatAmount(int i){
	cout << "How much food would you like to eat? ";
	int amt;
	cin >> amt;
	if (amt <= 0 || amt > foodInv[i].quantity){
		cout << "You cannot eat that amount of food.\n";
		amt = EatAmount(i);
	}
	return amt;
}

void Character::EatFood(){
	bool hasFood = false;
	for (int i = 0; i < 10; i++){
		if (foodInv[i].food.name != "No Food"){
			hasFood = true;
			break;
		}
	}
	if (hasFood){
		DisplayInv("food");
		int s = EatSlot();
		int a = EatAmount(s);
		UseItem(FoodItem, s, a);
	}
	else
	{
		cout << "There is no food to eat!\n";
	}
}

void Character::ForageTile(){
	cout << "You forage through your surroundings.\n";
	srand((unsigned) time(NULL));
	int result = rand() % 19;
	if (result == 0){
		DisplayInv("inventory");
		ItemDrop();
	}
	else if (result == 1){
		DisplayInv("food");
		FoodDrop();
	}
	else
	{
		cout << "There is nothing of use.\n";
	}
}

void Character::CheckExits(char tile){
	if (tile == '1'){
		SetMap(allMaps[curMap->exits[0]]);
	}
	else if (tile == '2' || tile == 'F'){
		SetMap(allMaps[curMap->exits[1]]);
		if (tile == 'F'){
			curX = curMap->forgeX;
			curY = curMap->forgeY;
		}
	}
	else if (tile == '3' || tile == 'M'){
		SetMap(allMaps[curMap->exits[2]]);
		if (tile == 'M'){
			curX = curMap->marketX;
			curY = curMap->marketY;
		}
	}
	else if (tile == '4'|| tile == 'I'){
		SetMap(allMaps[curMap->exits[3]]);
		if (tile == 'I'){
			curX = curMap->innX;
			curY = curMap->innY;
		}
	}
	else if (tile == '5'){
		SetMap(allMaps[curMap->exits[4]]);
	}
	int height = curMap->layout.size();
	int width = curMap->layout[0].size();
	if (curX == 0){
		curX = height-2;
	}
	else if (curX >= height-1){
		curX = 1;
	}
	if (curY == 0){
		curY = width-2;
	}
	else if (curY >= width-1){
		curY = 1;
	}
	// cout << "X: " << curX << "\nY: " << curY << "\n";
}

void Character::Move(){
	char tile = curMap->layout[curX][curY];
	CheckExits(tile);
	curMap->layout[curX][curY] = '@';
	UpdateMap();
	TileEvent(tile);
	if (!gameOver){
		cout << "Hit an arrow key to move.\n";
	}
}

void Character::UpdateMap(){
	sHandler.DisplayMap(curMap);
	cout << "Health: " << curHealth << "/" << health << " Magic: " << curMagic << "/" << magic << " Gold: " << gold << "\n";
	cout << "Enemies Left in Area: " << curMap->numEnemies << "\n";
}

void Character::SetMap(Map &newMap){
	curMap = &newMap;
	UpdateMap();
}

Map &Character::GetMap(){
	return *curMap;
}

void Character::ActionLoop(){
	cout << "Hit an arrow key to move.\n";
	while (!gameOver){
		MoveHandler();
	}
}

int Character::ArmorReduction(Weapon target){
	int reduction = 0;
	double modifier = 0;
	ArmorSlot armorInv[5] = {head, torso, arms, legs, feet};
	for (int i = 0; i < 5; i++){
		reduction += armorInv[i].armor.armorMod;
		if (armorInv[i].armor.weakness == target.weaponType){
			modifier += 0.25;
		}
		else if (armorInv[i].armor.resistance == target.weaponType){
			modifier -= 0.25;
		}
	}
	reduction /= 5;
	modifier /= 5;
	reduction *= modifier+1;
	return reduction;
}

void Character::PauseMenu(){
	sHandler.ClearScreen();
	cout << " ====Paused====\n\n\nHere you can enter a command to view inventory, armor, weapons, etc.\n";
	while (paused){
		cout << "\n\nEnter a command (type \"help\" for a list of possible commands):\n";
		string cmd;
		cin >> cmd;
		if (cmd == "help"){
			cout << "\nhelp - displays a list of commands\narmor - lists all armor equipped\nweapons - lists equipped weapons\ninv/inventory - lists the inventory\nfood - displays all food\nstats - displays stats\nresume - closes this menu\n";
		}
		else if (cmd == "armor"){
			cout << "\n\nArmor:\nHead: " << head.armor.name << "\nTorso:" << torso.armor.name << "\nArms: " << arms.armor.name << "\nLegs: " << legs.armor.name << "\nFeet: " << feet.armor.name << "\n";
		}
		else if (cmd == "weapons"){
			cout << "\n\nWeapons:\nPrimary: " << primary.weapon.name << "\nSecondary: " << secondary.weapon.name << "\n";
		}
		else if (cmd == "inv" || cmd == "inventory"){
			DisplayInv("inventory");
		}
		else if (cmd == "food"){
			DisplayInv("food");
		}
		else if (cmd == "stats"){
			DisplayStats();
		}
		else if (cmd == "resume"){
			paused = false;
		}
	}
	if (!paused)
	{
		UpdateMap();
	}
}

void Character::TradePrompt(NPC* npc, ItemType type){
	int choice;
	cout << npc->name << ": Are you buying (1) or selling (2)?\n";
	cin >> choice;
	if (type == Misc){
		TradeItems(npc, choice);
	}
	else if (type == FoodItem){
		TradeFood(npc, choice);
	}
	else if (type == WeaponItem){
		TradeWeapons(npc, choice);
	}
	else
	{
		TradeArmor(npc, choice);
	}
}

void Character::TradeItems(NPC* npc, int choice){
	bool exit = false;
	if (choice == 1){
		UpdateMap();
		cout << npc->name << ": Here are my wares...\n";
		int numWares = npc->items.size();
		for (int i = 0; i < numWares; i++){
			cout << i+1 << ". " << npc->items[i].name << " - " << npc->items[i].value << "\n";
		}
		int index;
		cout << "Which one catches your eye? Quit - 0\n";
		buySlotPrompt:
		cin >> index;
		if (index > numWares){
			index = numWares;
		}
		else if (index < 0){
			index = 1;
		}
		else
		{
			exit = true;
			goto EndSale;
		}
		if (npc->items[index-1].name == ""){
			cout << "There is nothing in that slot. Please enter a different slot:\n";
			goto buySlotPrompt;
		}
		if (gold - npc->items[index-1].value < 0){
			cout << "You don't have enough money for this. Please enter a different slot or type 0 to exit:\n";
			goto buySlotPrompt;
		}
		UpdateMap();
		DisplayInv("inventory");
		AddItemToInv(npc->items[index-1], 1);
		gold -= npc->items[index-1].value;
	}
	else
	{
		UpdateMap();
		DisplayInv("inventory");
		int slot, quantity;
		sellSlotPrompt:
		cout << "Enter the slot of the item you wish to sell: ";
		cin >> slot;
		if (slot > 30){
			slot = 30;
		}
		else if (slot < 1){
			slot = 1;
		}
		slot--; //Convert to 0 start for array index referencing
		if (inventory[slot].item.name == ""){
			cout << "There is nothing in that slot. Please enter a different slot:\n";
			goto sellSlotPrompt;
		}
		cout << "Enter the number of that item you wish to sell: ";
		cin >> quantity;
		if (quantity > inventory[slot].quantity){
			quantity = inventory[slot].quantity;
		}
		else if (quantity < 0){
			quantity = 1;
		}
		gold += inventory[slot].item.value*quantity;
		RemoveItemFromInv(&inventory[slot], quantity);
	}
	EndSale:
	if (exit == true){
		cout << "Exited Sale.\n";
	}
}

void Character::TradeFood(NPC* npc, int choice){
	bool exit = false;
	if (choice == 1){
		UpdateMap();
		cout << npc->name << ": Here are my wares...\n";
		int numWares = npc->food.size();
		for (int i = 0; i < numWares; i++){
			cout << i+1 << ". " << npc->food[i].name << " - " << npc->food[i].value << "\n";
		}
		int index;
		cout << "Which one catches your eye? Quit - 0\n";
		buySlotPrompt:
		cin >> index;
		if (index > numWares){
			index = numWares;
		}
		else if (index < 0){
			index = 1;
		}
		else if (index == 0){
			exit = true;
			goto EndSale;
		}
		if (npc->food[index-1].name == ""){
			cout << "There is nothing in that slot. Please enter a different slot or type 0 to exit:\n";
			goto buySlotPrompt;
		}
		if (gold - npc->food[index-1].value < 0){
			cout << "You don't have enough money for this. Please enter a different slot or type 0 to exit:\n";
			goto buySlotPrompt;
		}
		UpdateMap();
		DisplayInv("food");
		AddFoodToInv(npc->food[index-1], 1);
		gold -= npc->food[index-1].value;
	}
	else
	{
		UpdateMap();
		DisplayInv("food");
		int slot, quantity;
		sellSlotPrompt:
		cout << "Enter the slot of the item you wish to sell: ";
		cin >> slot;
		if (slot > 10){
			slot = 10;
		}
		else if (slot < 1){
			slot = 1;
		}
		slot--; //Convert to 0 start for array index referencing
		if (foodInv[slot].food.name == ""){
			cout << "There is nothing in that slot. Please enter a different slot:\n";
			goto sellSlotPrompt;
		}
		cout << "Enter the number of that item you wish to sell: ";
		cin >> quantity;
		if (quantity > foodInv[slot].quantity){
			quantity = foodInv[slot].quantity;
		}
		else if (quantity < 0){
			quantity = 1;
		}
		gold += foodInv[slot].food.value*quantity;
		RemoveFoodFromInv(&foodInv[slot], quantity);
	}
	EndSale:
	if (exit == true){
		cout << "Exited Sale.\n";
	}
}

void Character::TradeWeapons(NPC* npc, int choice){
	bool exit = false;
	if (choice == 1){
		UpdateMap();
		cout << npc->name << ": Here are my wares...\n";
		int numWares = npc->weapons.size();
		for (int i = 0; i < numWares; i++){
			cout << i+1 << ". " << npc->weapons[i].name << " - " <<
					npc->weapons[i].value << "\n";
		}
		int index;
		cout << "Which one catches your eye? Quit - 0\n";
		buySlotPrompt:
		cin >> index;
		if (index > numWares){
			index = numWares;
		}
		else if (index < 0){
			index = 1;
		}
		else
		{
			exit = true;
			goto EndSale;
		}
		if (npc->weapons[index-1].name == ""){
			cout << "There is nothing in that slot. Please enter a different slot:\n";
			goto buySlotPrompt;
		}
		if (gold - npc->weapons[index-1].value < 0){
			cout << "You don't have enough money for this. Please enter a different slot or type 0 to exit:\n";
			goto buySlotPrompt;
		}
		UpdateMap();
		EquipWeapon(npc->weapons[index-1]);
		gold -= npc->weapons[index-1].value;
	}
	else
	{
		UpdateMap();
		// cout << "\n\nArmor:\n1. Head: " << head.armor.name << "\n2. Torso:" << torso.armor.name << "\n3. Arms: " << arms.armor.name << "\n4. Legs: " <<legs.armor.name << "\n5. Feet: " << feet.armor.name << "\n";
		cout << "\n\nWeapons:\n1. Primary: " << primary.weapon.name <<"\n2. Secondary: " << secondary.weapon.name << "\n";
		int slot;
		sellSlotPrompt:
		cout << "Enter the slot of the item you wish to sell: ";
		cin >> slot;
		if (slot > 2){
			slot = 2;
		}
		else if (slot < 1){
			slot = 1;
		}
		slot--; //Convert to 0 start for array index referencing
		if (weaponInv[slot]->weapon.name == ""){
			cout << "There is nothing in that slot. Please enter a different slot:\n";
			goto sellSlotPrompt;
		}
		UnequipWeapon(weaponInv[slot]);
	}
	EndSale:
	if (exit == true){
		cout << "Exited Sale.\n";
	}
}

void Character::TradeArmor(NPC* npc, int choice){
	bool exit = false;
	if (choice == 1){
		UpdateMap();
		cout << npc->name << ": Here are my wares...\n";
		int numWares = npc->armor.size();
		for (int i = 0; i < numWares; i++){
			cout << i+1 << ". " << npc->armor[i].name << " - " << npc->armor[i].value << "\n";
		}
		int index;
		cout << "Which one catches your eye? Quit - 0\n";
		buySlotPrompt:
		cin >> index;
		if (index > numWares){
			index = numWares;
		}
		else if (index < 0){
			index = 1;
		}
		else if (index == 0){
			goto EndSale;
			exit = true;
		}
		if (npc->armor[index-1].name == ""){
			cout << "There is nothing in that slot. Please enter a different slot:\n";
			goto buySlotPrompt;
		}
		if (gold - npc->armor[index-1].value < 0){
			cout << "You don't have enough money for this. Please enter a different slot or type 0 to exit:\n";
			goto buySlotPrompt;
		}
		UpdateMap();
		EquipArmor(npc->armor[index-1]);
		gold -= npc->armor[index-1].value;
	}
	else
	{
		UpdateMap();
		cout << "\n\nArmor:\n1. Head: " << head.armor.name << "\n2. Torso:" << torso.armor.name << "\n3. Arms: " << arms.armor.name << "\n4. Legs: " << legs.armor.name << "\n5. Feet: " << feet.armor.name << "\n";
		// cout << "\n\nWeapons:\n1. Primary: " << primary.weapon.name << "\n2. Secondary: " << secondary.weapon.name << "\n";
		int slot;
		sellSlotPrompt:
		cout << "Enter the slot of the item you wish to sell: ";
		cin >> slot;
		if (slot > 5){
			slot = 5;
		}
		else if (slot < 1){
			slot = 1;
		}
		slot--; //Convert to 0 start for array index referencing
		if (armorInv[slot]->armor.name == ""){
			cout << "There is nothing in that slot. Please enter a different slot:\n";
			goto sellSlotPrompt;
		}
		UnequipArmor(armorInv[slot]);
	}
	EndSale:
	if (exit == true){
		cout << "Exited Sale.\n";
	}
}

void Character::ResetStats(){
	head = armorSlot;
	torso = armorSlot;
	arms = armorSlot;
	legs = armorSlot;
	feet = armorSlot;
	primary = WeaponSlot(CarvingKnife);
	secondary = weaponSlot;
	charClass = NoClass;
	charRace = NoRace;
	curMap = &highashPlainsA;
	name = "";
	curX = 8;
	curY = 1;
	gold = 0;
	health = 200;
	magic = 200;
	strength = 50;
	agility = 50;
	curHealth = health;
	curMagic = magic;
	curStrength = strength;
	curAgility = agility;
	gameOver = false;
	paused = false;
	InvSlot inventory[30] = {InvSlot(Stick, 100), InvSlot(Leaf, 100),
	invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot, invSlot,
	invSlot, invSlot, invSlot, invSlot,
	invSlot, invSlot, invSlot, invSlot, invSlot, invSlot,
	invSlot, invSlot, invSlot, invSlot,
	invSlot, invSlot, invSlot, invSlot, invSlot, invSlot};
	FoodSlot foodInv[10] = {foodSlot, foodSlot, foodSlot, foodSlot,
	foodSlot, foodSlot, foodSlot, foodSlot, foodSlot, foodSlot};
}

Character player = Character();

CombatHandler::CombatHandler() : c_player(&player), enemy(BasicEnemy){}

void CombatHandler::SetFirst(){
	if (c_player->agility >= enemy.agility){
		// cout << "PLAYER FIRST\n";
		playerTurn = true;
	}
	else
	{
		// cout << "ENEMY FIRST\n";
		playerTurn = false;
	}
}

void CombatHandler::CombatSetup(Enemy newEnemy){
	enemy = newEnemy;
	SetFirst();
	cout << "An enemy " << enemy.name << " has attacked!\n";
}

void CombatHandler::CombatLoop(Enemy newEnemy){
	CombatSetup(newEnemy);
	// cout << "COMBAT SETUP COMPLETE\n";
	while(c_player->curHealth > 0 && enemy.curHealth > 0 && !playerFled){
		// cout << "COMBAT IN PROGRESS\n";
		if (playerTurn){
			PlayerTurn();
		}
		else
		{
			EnemyTurn();
		}
		system("pause");
		c_player->UpdateMap();
	}
	if (c_player->curHealth <= 0){
		sHandler.ClearScreen();
		cout << "GAME OVER\n";
		c_player->gameOver = true;
		system("pause");
		sHandler.ClearScreen();
	}
	else if (enemy.curHealth <= 0){
		cout << "Defeated " << enemy.name << "!\n";
		if (DoesEnemyDrop()){
			DropItem();
		}
		if (c_player->curMap->numEnemies > 0){
			c_player->curMap->numEnemies--;
		}
	}
	playerFled = false;
}

void CombatHandler::PlayerTurn(){
	int combatChoice;
	cout << "Enemy: " << enemy.name << " " << enemy.curHealth << "/" <<
			enemy.health << "\n";
	cout << "What will you do?\n1. Primary Attack - " << c_player->primary.weapon.name << "\n2. Secondary Attack - " << c_player->secondary.weapon.name << "\n3. Item\n4. Flee\n";
	cin >> combatChoice;
	switch (combatChoice) {
	case 1:
		PlayerAttack(c_player->primary);
		break;
	case 2:
		PlayerAttack(c_player->secondary);
		break;
	case 3:
		EatFood();
		break;
	case 4:
		Flee();
		break;
	}
	playerTurn = false;
}

void CombatHandler::EnemyTurn(){
	cout << "The enemy attacks!\n";
	EnemyAttack();
	playerTurn = true;
}

void CombatHandler::PlayerAttack(WeaponSlot weapon){
	if (c_player->curMagic-weapon.weapon.magicDrain >= 0){
		int damage = (c_player->strength*0.5 + weapon.weapon.damageMod) - (enemy.ArmorReduction(weapon.weapon));
		c_player->curMagic -= weapon.weapon.magicDrain;
		enemy.curHealth -= damage;
		cout << "Attacked " << enemy.name << " with " << weapon.weapon.name << " for " << damage << "HP!\n";
	}
	else
	{
		cout << "You don't have enough magic!\n";
		PlayerTurn();
	}
}

void CombatHandler::EnemyAttack(){
	int damage = (enemy.strength*0.5 + enemy.weapon.weapon.damageMod) - (c_player->ArmorReduction(enemy.weapon.weapon));
	c_player->curHealth -= damage;
	cout << enemy.name << " attacked with " << enemy.weapon.weapon.name << " for " << damage << " HP!\n";
}

void CombatHandler::Flee(){
	cout << "Fled from the " << enemy.name << " as it fled from you!\n";
	playerFled = true;
	c_player->curMap->numEnemies--;
}

bool CombatHandler::DoesEnemyDrop(){
	srand((unsigned) time(NULL));
	int result = rand() % 100 + 1;
	double maxVal = 100*enemy.dropChance;
	if (result <= maxVal){
		return true;
	}
	else
	{
		return false;
	}
}
void CombatHandler::DropItem(){
	if (enemy.dropType == WeaponDrop){
		cout << "The enemy dropped a weapon!\n";
		c_player->EquipWeapon(enemy.wDrop);
	}
	else if (enemy.dropType == ArmorDrop){
		cout << "The enemy dropped some armor!\n";
		c_player->EquipArmor(enemy.aDrop);
	}
	else if (enemy.dropType == ItemDrop){
		cout << "The enemy dropped an item!\n";
		c_player->DisplayInv("inventory");
		c_player->AddItemToInv(enemy.iDrop, 1);
	}
	else if (enemy.dropType == FoodDrop){
		cout << "The enemy dropped some food!\n";
		c_player->DisplayInv("food");
		c_player->AddFoodToInv(enemy.fDrop, 1);
	}
}

void CombatHandler::EatFood(){
	c_player->EatFood();
}

CombatHandler combat = CombatHandler();
