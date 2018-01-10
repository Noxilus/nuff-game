#include "Slots.h"

InvSlot::InvSlot(Item i, int q) : item(i), quantity(q){}
InvSlot::InvSlot(Item i) : item(i), quantity(1){}
InvSlot::InvSlot() : item(NoItem), quantity(0){}
InvSlot invSlot = InvSlot();
FoodSlot::FoodSlot(Food f, int q) : food(f), quantity(q){}
FoodSlot::FoodSlot(Food f) : food(f), quantity(0){}
FoodSlot::FoodSlot() : food(NoFood), quantity(0){}
FoodSlot foodSlot = FoodSlot();
ArmorSlot::ArmorSlot(Armor a) : armor(a){}
ArmorSlot::ArmorSlot() : armor(NoArmor){}

void ArmorSlot::SetArmor(Armor a){
	if (armor.name == ""){
		armor = a;
	}
	else
	{
		int swap;
		cout << "Slot Full!\nOld Armor:" << armor.name << "\nNew Weapon:" << a.name << "\nSwap out? (Note: Discarded armor will be LOST PERMANENTLY)\n1. Yes\n2. No\n";
		cin >> swap;
		if (swap == 1){
			armor = a;
		}
	}
}

ArmorSlot armorSlot = ArmorSlot();
WeaponSlot::WeaponSlot(Weapon w) : weapon(w){}
WeaponSlot::WeaponSlot() : weapon(NoWeapon){}

void WeaponSlot::SetWeapon(Weapon w){
	if (weapon.name == ""){
		weapon = w;
	}
	else
	{
		int swap;
		cout << "Slot Full!\nOld Weapon:" << weapon.name << "\nNew Weapon:" << w.name << "\nSwap out? (Note: Discarded weapon will be LOST PERMANENTLY)\n1. Yes\n2. No\n";
		cin >> swap;
		if (swap == 1){
			weapon = w;
		}
	}
}

WeaponSlot weaponSlot = WeaponSlot();
//ExtraSlot::ExtraSlot() : isUsed(false), permitted(NoItemType), item(NoItem){}
//const ExtraSlot emptyExtra = ExtraSlot();
