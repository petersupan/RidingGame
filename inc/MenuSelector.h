#ifndef MENUSELECTOR_H
#define MENUSELECTOR_H

#include "Singleton.h"

class MenuSelector
{
public:
	enum Menu
	{
		MENU_TITLE,
		MENU_DISCLAIMER,
		MENU_RIDERSELECT,
		MENU_HORSESELECT,
		MENU_TUTORIAL,
		MENU_RIDING,
		MENU_BETWEENLEVELS,
		MENU_HIGHSCORE
	};

	void SwitchToMenu(Menu target);

	Menu GetCurrentMenu(void) { return currentMenu; }
	void SwitchToNext(void);
	void SetNext(Menu next) { nextMenu = next; }
	Menu GetNextMenu() { return nextMenu; }

	SINGLETONDECLARATIONS(MenuSelector);

private:
	Menu currentMenu;
	Menu nextMenu;
};


#endif

