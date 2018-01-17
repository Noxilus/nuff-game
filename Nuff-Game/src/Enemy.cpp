#include "Enemy.h"

Enemy::Enemy() :
	head(NoArmor),
	torso(NoArmor),
	arms(NoArmor),
	legs(NoArmor),
	feet(NoArmor),
	weapon(NoWeapon),
	name("No Enemy"),
	health(0),
	strength(0),
	agility(0),
	curHealth(health),
	curStrength(strength),
	curAgility(agility),
	dropType(WeaponDrop),
	wDrop(NoWeapon),
	aDrop(NoArmor),
	iDrop(NoItem),
	fDrop(NoFood),
	dropChance(0){}

Enemy::Enemy(Weapon drop, Armor aHead, Armor aTorso, Armor aArms, Armor aLegs, Armor aFeet, Weapon w, string n, double h, double s, double a, double d) :
	head(aHead),
	torso(aTorso),
	arms(aArms),
	legs(aLegs),
	feet(aFeet),
	weapon(w),
	name(n),
	health(h),
	strength(s),
	agility(a),
	curHealth(health),
	curStrength(strength),
	curAgility(agility),
	dropType(WeaponDrop),
	wDrop(drop),
	aDrop(NoArmor),
	iDrop(NoItem),
	fDrop(NoFood),
	dropChance(d){}

Enemy::Enemy(Armor drop, Armor aHead, Armor aTorso, Armor aArms, Armor aLegs, Armor aFeet, Weapon w, string n, double h, double s, double a, double d) :
	head(aHead),
	torso(aTorso),
	arms(aArms),
	legs(aLegs),
	feet(aFeet),
	weapon(w),
	name(n),
	health(h),
	strength(s),
	agility(a),
	curHealth(health),
	curStrength(strength),
	curAgility(agility),
	dropType(ArmorDrop),
	wDrop(NoWeapon),
	aDrop(drop),
	iDrop(NoItem),
	fDrop(NoFood),
	dropChance(d){}

Enemy::Enemy(Item drop, Armor aHead, Armor aTorso, Armor aArms, Armor aLegs, Armor aFeet, Weapon w, string n, double h, double s, double a, double d) :
	head(aHead),
	torso(aTorso),
	arms(aArms),
	legs(aLegs),
	feet(aFeet),
	weapon(w),
	name(n),
	health(h),
	strength(s),
	agility(a),
	curHealth(health),
	curStrength(strength),
	curAgility(agility),
	dropType(ItemDrop),
	wDrop(NoWeapon),
	aDrop(NoArmor),
	iDrop(drop),
	fDrop(NoFood),
	dropChance(d){}

Enemy::Enemy(Food drop, Armor aHead, Armor aTorso, Armor aArms, Armor aLegs, Armor aFeet, Weapon w, string n, double h, double s, double a, double d) :
	head(aHead),
	torso(aTorso),
	arms(aArms),
	legs(aLegs),
	feet(aFeet),
	weapon(w),
	name(n),
	health(h),
	strength(s),
	agility(a),
	curHealth(health),
	curStrength(strength),
	curAgility(agility),
	dropType(FoodDrop),
	wDrop(NoWeapon),
	aDrop(NoArmor),
	iDrop(NoItem),
	fDrop(drop),
	dropChance(d){}

int Enemy::ArmorReduction(Weapon target){
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

//Enemies
Enemy BasicEnemy = Enemy();
Enemy Bandit = Enemy(IronDagger, LeatherCap, LeatherTunic, LeatherBracers, LeatherGreaves, LeatherBoots, IronDagger, "Bandit", 100, 15, 75, 0.05);
Enemy Bobcat = Enemy(BobcatFur, NoArmor, NoArmor, NoArmor, NoArmor, NoArmor, Claws, "Bobcat", 90, 20, 25, 0.5);
Enemy GoblinSpearman = Enemy(WoodenSpear, IronHelmet, LeatherTunic, NoArmor, LeatherGreaves, LeatherBoots, WoodenSpear, "Goblin Spearman", 75, 20, 60, 0.1);
Enemy CrimsonDrake = Enemy(FlamingScale, CrimsonScales, CrimsonScales, CrimsonScales, CrimsonScales, CrimsonScales, FireBreath, "Crimson Drake", 90, 30, 25, 0.01);

//Bosses
Enemy BrutalOrc = Enemy(LargeClub, IronHelmet, LeatherTunic, NoArmor, LeatherGreaves, LeatherBoots, LargeClub, "Brutal Orc", 125, 400, 10, 1);
Enemy PlainsDemon = Enemy(UnholyBlade, DemonHide, DemonHide, DemonHide, DemonHide, DemonHide, UnholyBlade, "Plains Demon", 125, 45, 90, 0.01);
Enemy SmallGolem = Enemy(RockClub, RockHide, RockHide, RockHide, RockHide, RockHide, RockPummel, "Small Golem", 130, 40, 20, 0.66);

//Region Lists
vector<Enemy> noEnemies = {};
vector<Enemy> plainsEnemies = {Bandit, Bobcat, GoblinSpearman, CrimsonDrake};
