#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>

#include "Enemy.h"
#include "Slots.h"
#include "Types.h"

struct Map;
class NPC;

using namespace std;

struct BaseId {
	double healthMod;
	double magicMod;
	double agilityMod;
	double strengthMod;
	BaseId(double h, double m, double a, double r);
};

struct ClassIdentifier : BaseId {
	ClassType type;
	ClassIdentifier(double h, double m, double a, double r, ClassType t);
};

struct RaceIdentifier : BaseId {
	RaceType type;
	RaceIdentifier(double h, double m, double a, double r, RaceType t);
};

class Character {
public:
	InvSlot inventory[30];
	FoodSlot foodInv[10];
	ArmorSlot head, torso, arms, legs, feet;
	WeaponSlot primary, secondary;
	ClassIdentifier charClass;
	RaceIdentifier charRace;
	Map *curMap;
	string name;
	int curX, curY, gold;
	double health, magic, strength, agility;
	double curHealth, curMagic, curStrength, curAgility;
	bool gameOver, paused;
	ArmorSlot* armorInv[5] = {&head, &torso, &arms, &legs, &feet};
	WeaponSlot* weaponInv[2] = {&primary, &secondary};
	Character();
	~Character();
	void SetName(string n);
	void SetClass(ClassIdentifier newClass);
	void SetRace(RaceIdentifier newRace);
	void SetStats();
	void DisplayStats();
	void UseItem(ItemType type, int slotNum, int quantity);
	void EquipArmor(Armor toEquip);
	void UnequipArmor(ArmorSlot* toUnequip);
	void EquipWeapon(Weapon toEquip);
	void UnequipWeapon(WeaponSlot* toUnequip);
	void AddItemToInv(Item item, int quantity);
	void RemoveItemFromInv(InvSlot* slot, int quantity);
	void AddFoodToInv(Food food, int quantity);
	void RemoveFoodFromInv(FoodSlot* slot, int quantity);
	void AddGold(int g);
	void SwapOutArmor(Armor armor, ArmorSlot* slot);
	void SwapOutWeapon(Weapon weapon, WeaponSlot* slot);
	void DisplayInv(string type);
	void ResetPos(int x, int y);
	void MoveHandler();
	void TileEvent(char tile);
	void ItemDrop();
	void FoodDrop();
	void GearDrop();
	void NPCInteraction(NPC* npc);
	void CraftHandler();
	void CraftWeapon();
	void CraftArmor();
	void CraftItem();
	void CraftFood();
	void ScanInventory(ItemRecipe* recipe);
	void ScanInventory(FoodRecipe* recipe);
	ArmorSlot* ScanInventory(ArmorRecipe* recipe);
	WeaponSlot* ScanInventory(WeaponRecipe* recipe);
	void GatherItems(ItemRecipe* recipe);
	void GatherItems(FoodRecipe* recipe);
	void GatherItems(ArmorRecipe* recipe);
	void GatherItems(WeaponRecipe* recipe);
	void BossInteraction(Action dir);
	int EatSlot();
	int EatAmount(int i);
	void EatFood();
	void ForageTile();
	void CheckExits(char tile);
	void Move();
	void UpdateMap();
	void SetMap(Map &newMap);
	Map &GetMap();
	void ActionLoop();
	int ArmorReduction(Weapon target);
	void PauseMenu();
	void TradePrompt(NPC* npc, ItemType type);
	void TradeItems(NPC* npc, int choice);
	void TradeFood(NPC* npc, int choice);
	void TradeWeapons(NPC* npc, int choice);
	void TradeArmor(NPC* npc, int choice);
	void ResetStats();
};

extern Character player;
extern ClassIdentifier NoClass;
extern ClassIdentifier KnightClass;
extern ClassIdentifier WarriorClass;
extern ClassIdentifier ThiefClass;
extern ClassIdentifier BlacksmithClass;
extern ClassIdentifier LumberjackClass;
extern ClassIdentifier MageClass;
extern ClassIdentifier ArcherClass;
extern RaceIdentifier NoRace;
extern RaceIdentifier HumanRace;
extern RaceIdentifier WoodElfRace;
extern RaceIdentifier OrcRace;
extern RaceIdentifier DarkElfRace;
extern RaceIdentifier DragonlingRace;
extern RaceIdentifier DwarfRace;

class CombatHandler {
	bool playerFled = false;
	bool playerTurn = false;
	Character* c_player;
	Enemy enemy;
public:
	CombatHandler();
	void SetFirst();
	void CombatSetup(Enemy newEnemy);
	void CombatLoop(Enemy newEnemy);
	void PlayerTurn();
	void EnemyTurn();
	void PlayerAttack(WeaponSlot weapon);
	void EnemyAttack();
	void Flee();
	bool DoesEnemyDrop();
	void DropItem();
	void EatFood();
};

extern CombatHandler combat;

#endif /* CHARACTER_H_ */
