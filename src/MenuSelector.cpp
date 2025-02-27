#include "Defines.h"
#include "MenuSelector.h"
#include "MainProgram.h"
#include "GameLogic.h"
#include <assert.h>

SINGLETONFUNCTIONS(MenuSelector);


MenuSelector::MenuSelector(void)
{
	currentMenu = MENU_DISCLAIMER;
	nextMenu = MENU_TITLE;
}

void MenuSelector::SwitchToNext(void)
{
	SwitchToMenu(nextMenu);
}

void MenuSelector::SwitchToMenu(MenuSelector::Menu target)
{
	currentMenu = target;
	if (target == MENU_TITLE)
	{
		MainProgram::getInstance()->SwitchToState(MainProgram::STATE_SPLASHSCREEN);
		nextMenu = MENU_HORSESELECT;
	}
	else if (target == MENU_DISCLAIMER)
	{
		MainProgram::getInstance()->SwitchToState(MainProgram::STATE_SPLASHSCREEN);
		nextMenu = MENU_TITLE;
	}
	else if (target == MENU_RIDERSELECT)
	{
		MainProgram::getInstance()->SwitchToState(MainProgram::STATE_RIDERSELECT);
		nextMenu = MENU_TUTORIAL;
	}
	else if (target == MENU_HORSESELECT)
	{
		MainProgram::getInstance()->SwitchToState(MainProgram::STATE_HORSESELECT);
		nextMenu = MENU_RIDERSELECT;
	}
	else if (target == MENU_RIDING)
	{
		MainProgram::getInstance()->SwitchToState(MainProgram::STATE_RIDING);
		nextMenu = MENU_BETWEENLEVELS;
	}
	else if (target == MENU_BETWEENLEVELS)
	{
		MainProgram::getInstance()->SwitchToState(MainProgram::STATE_SPLASHSCREEN);
		if (GameLogic::getInstance()->GetLevel() < 2)
		{
			nextMenu = MENU_RIDING;
		}
		else
			nextMenu = MENU_HIGHSCORE;
	}
	else if (target == MENU_HIGHSCORE)
	{
		MainProgram::getInstance()->SwitchToState(MainProgram::STATE_HIGHSCORE);
		nextMenu = MENU_TITLE;
	}
	else if (target == MENU_TUTORIAL)
	{
		MainProgram::getInstance()->SwitchToState(MainProgram::STATE_SPLASHSCREEN);
		nextMenu = MENU_RIDING;
	}
	else 
	{
		assert(false);
	}

}

