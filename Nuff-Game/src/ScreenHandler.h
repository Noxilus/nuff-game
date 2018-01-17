#ifndef SCREENHANDLER_H_
#define SCREENHANDLER_H_

#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "Types.h"
#include "Maps.h"

using namespace std;

class ScreenHandler {
	HANDLE hInput, hOutput;
	DWORD NumInputs, InputsRead;
	INPUT_RECORD irInput;
public:
	ScreenHandler();
	~ScreenHandler();
	Action GetDir();
	void SetupScreen();
	void DisplayMap(Map *map);
	void ClearScreen();
};

extern ScreenHandler sHandler;

#endif /* SCREENHANDLER_H_ */
