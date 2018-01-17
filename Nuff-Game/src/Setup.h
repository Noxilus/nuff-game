#ifndef SETUP_H_
#define SETUP_H_

#include "Character.h"
#include "ScreenHandler.h"

class SetupHandler {
	bool doneSetup;
	std::string nameText;
public:
	SetupHandler();
	~SetupHandler();
	void DoTitle();
	void StartChoice();
	void DoIntro();
	void DoName();
	void ConfirmSetup();
	void SetupLoop();
	void ResetSetup();
	void ResetMaps();
};

extern SetupHandler setup;

#endif /* SETUP_H_ */
