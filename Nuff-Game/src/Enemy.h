#ifndef ENEMY_H_
#define ENEMY_H_

#include "Slots.h"

using namespace std;

class Enemy {
public:
	ArmorSlot head, torso, arms, legs, feet;
	WeaponSlot weapon;
	string name;
	double health, strength, agility;
	double curHealth, curStrength, curAgility;
	EnemyDrop dropType;
	Weapon wDrop;
	Armor aDrop;
	Item iDrop;
	Food fDrop;
	double dropChance;
	Enemy();
	Enemy(Weapon drop, Armor aHead, Armor aTorso, Armor aArms, Armor aLegs,
	Armor aFeet, Weapon w, string n, double h, double s, double a, double d);
	Enemy(Armor drop, Armor aHead, Armor aTorso, Armor aArms, Armor aLegs,
	Armor aFeet, Weapon w, string n, double h, double s, double a, double d);
	Enemy(Item drop, Armor aHead, Armor aTorso, Armor aArms, Armor aLegs,
	Armor aFeet, Weapon w, string n, double h, double s, double a, double d);
	Enemy(Food drop, Armor aHead, Armor aTorso, Armor aArms, Armor aLegs,
	Armor aFeet, Weapon w, string n, double h, double s, double a, double d);
	int ArmorReduction(Weapon target);
};

//Enemies
extern Enemy BasicEnemy;
extern Enemy Bandit;
extern Enemy Bobcat;
extern Enemy SpearGoblin;
extern Enemy CrimsonDrake;

//Bosses
extern Enemy BrutalOrc;
extern Enemy PlainsDemon;
extern Enemy SmallGolem;

//Region Lists
extern vector<Enemy> noEnemies;
extern vector<Enemy> plainsEnemies;

#endif /* ENEMY_H_ */
