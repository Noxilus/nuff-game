#include "ScreenHandler.h"

#define VK_E 69
#define VK_F 70

using namespace std;

ScreenHandler::ScreenHandler() : hInput(GetStdHandle(STD_INPUT_HANDLE)), hOutput(GetStdHandle(STD_OUTPUT_HANDLE)), NumInputs(0), InputsRead(0){}
ScreenHandler::~ScreenHandler(){}

void ScreenHandler::SetupScreen(){
	SetConsoleTitle("Adventures in Lavaria");
	SetConsoleTextAttribute(hOutput, 116);
	const SMALL_RECT windowSize = {0, 0, 100, 100};
	SetConsoleWindowInfo(hOutput, true, &windowSize);
}

Action ScreenHandler::GetDir(){
	/* Following code modified from user93353 on StackOverflow */
	/* Modifications: changed console logging to return values, removed VK_ESCAPE check, added default case */
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD NumInputs = 0;
	DWORD InputsRead = 0;
	INPUT_RECORD irInput;
	// bool running = true;
	GetNumberOfConsoleInputEvents(hInput, &NumInputs);
	ReadConsoleInput(hInput, &irInput, 1, &InputsRead);
	if (irInput.Event.KeyEvent.bKeyDown){
		// cout << irInput.Event.KeyEvent.wVirtualKeyCode << "\n";
		switch (irInput.Event.KeyEvent.wVirtualKeyCode){
		case VK_ESCAPE:
			// cout << "\nEscape";
			return Pause;
		case VK_LEFT:
			// cout << "\nLeft";
			return Left;
		case VK_UP:
			// cout << "\nUp";
			return Up;
		case VK_RIGHT:
			// cout << "\nRight";
			return Right;
		case VK_DOWN:
			// cout << "\nDown";
			return Down;
		case VK_E:
			// cout << "\nEat";
			return Eat;
		case VK_F:
			// cout << "\nForage";
			return Forage;
		default:
			// cout << "\nNot Arrow Key";
			return NoDir;
		}
	}
	return NoDir;
}

void ScreenHandler::DisplayMap(Map *map){
	ClearScreen();
	// cout << "Screen cleared" << "\n";
	cout << map->name << "\n" << "Esc - Commands E - Eat F - Forage }- Outside of dialog/combat ONLY\n";
	int y = map->layout.size();
	// cout << "Height of map: " << y;
	for (int i = 0; i < y; i++){
		cout << map->layout[i] << "\n";
	}
}

void ScreenHandler::ClearScreen(){
	system("cls");
}

ScreenHandler sHandler = ScreenHandler();
