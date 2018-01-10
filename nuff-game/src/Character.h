/*
 * Character.h
 *
 *  Created on 2018-01-08
 *      Author: Noah
 *
 * 	Last Update: None
 */

#ifndef SRC_CHARACTER_H_
#define SRC_CHARACTER_H_

#include <string>

class Character {
public:
	// Values
	std::string name;
	int maxHP;
	int curHP;

	// Functions
	Character();
	~Character();

};



#endif /* SRC_CHARACTER_H_ */
