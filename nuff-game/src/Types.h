#ifndef TYPES_H_
#define TYPES_H_

enum ItemType {
	NoItemType,
	FoodItem,
	Misc,
	WeaponItem,
	ArmorItem
};

enum ArmorType {
	NoArmorType,
	Helmet,
	Tunic,
	Chestplate,
	Bracers,
	Gauntlets,
	Pants,
	Greaves,
	// Robes,
	Sabatons,
	Boots,
	CreatureArmor
};

enum WeaponType {
	NoWeaponType,
	Sword,
	Dagger,
	Hammer,
	Axe,
	Staff,
	Bow,
	Spear,
	Spell,
	CreatureWeapon
};

enum Action {
	Up,
	Down,
	Left,
	Right,
	Pause,
	Eat,
	Forage,
	NoDir
};

enum NPCType {
	Smith,
	Host,
	Vendor,
	BasicNPCType
};

enum EnemyDrop {
	WeaponDrop,
	ArmorDrop,
	ItemDrop,
	FoodDrop,
	NoDrop
};

#endif /* TYPES_H_ */
