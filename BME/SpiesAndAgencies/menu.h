#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "user.hpp"
#include "agency.h"
#include "spy.h"

using namespace std;

//A Menü osztály, igyekeztem a függvényeknek "beszélõ" nevet adni, így látszik, hogy mi-mit hivatott csinálni.
//Folytatás a menu.cpp-ben.

class Menu {

private:
	map<int, Agency*> agencies;
	map<int, Spy*> spies;

	int nextSpyID;
	int nextAgencyID;

	void showSpyOptions();
	void showAgencyOptions();

	void listSpies();
	void listAgencies();


	void readFromFile();
	void saveToFile();

	void addNewSpy();
	void removeSpy();

	void addNewAgency();
	void removeAgency();

	void setSpyAgency();
	void addNewFriend();
	void removeFriend();

	void showAllForSpy();
	void showAllForAgency();

	void setAgencyRelation();

public:
	Menu();

	void show();
};

#endif //MENU_H_INCLUDED