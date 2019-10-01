#include "menu.h"
#include <iostream>
#include <fstream>

using namespace std;

//Igazából ez a legbrutálabb oldal, rengeteg esetszétválasztós szépséggel.
//A throw-catch kivételkezelés is leginkább itt kap szerepet.

Menu::Menu()
{
	nextSpyID = nextAgencyID = 0;
}

void Menu::show()
{
	int todo = 0;
	do
	{
		cout << "\n\n-------------------------------" << endl;
		cout << "\tMit szeretnel csinalni?" << endl;
		cout << "-------------------------------" << endl;
		cout << "1) Kem-muveletek" << endl;
		cout << "2) Ugynokseg-muveletek" << endl;
		cout << "3) Adatok beolvasasa fajlbol" << endl;
		cout << "4) Adatok kiirasa fajlba" << endl;
		cout << "0) Kilepni" << endl;

		cin >> todo;
		switch (todo)
		{
		case 1: showSpyOptions(); break;
		case 2: showAgencyOptions(); break;
		case 3: readFromFile(); break;
		case 4: saveToFile(); break;
		}
	} while (todo);
}


void Menu::showAgencyOptions()
{
	cout << "1) Uj ugynokseg letrehozasa" << endl;
	cout << "2) Ugynoksegek listazasa" << endl;
	cout << "3) Reszletes jelentes egy ugynoksegrol" << endl;
	cout << "4) Viszony beallitasa ugynoksegek kozott" << endl;
	cout << "5) Ugynokseg torlese" << endl;
	cout << "0) Visszalepes" << endl;

	int todo = 0;
	cin >> todo;
	switch (todo)
	{
	case 1: addNewAgency(); break;
	case 2: listAgencies(); break;
	case 3: showAllForAgency(); break;
	case 4: setAgencyRelation(); break;
	case 5: removeAgency(); break;
	}
}

void Menu::showSpyOptions()
{
	cout << "1) Uj kem letrehozasa" << endl;
	cout << "2) Kemek listazasa" << endl;
	cout << "3) Reszletes jelentes egy kemrol" << endl;
	cout << "4) Uj ismeretseg ket kem kozott" << endl;
	cout << "5) Ismeretseg torolese kemek kozott" << endl;
	cout << "6) Kem ugynokseghez rendelese" << endl;
	cout << "7) Kem torlese" << endl;
	cout << "0) Visszalepes" << endl;

	int todo = 0;
	cin >> todo;
	switch (todo)
	{
	case 1: addNewSpy(); break;
	case 2: listSpies(); break;
	case 3: showAllForSpy(); break;
	case 4: addNewFriend(); break;
	case 5: removeFriend(); break;
	case 6: setSpyAgency(); break;
	case 7: removeSpy(); break;
	}
}


//Innen indul a rondaság...

void Menu::readFromFile()
{
	cout << "FIGYELEM! Az adatbazis frissitese torli az eddigi adatokat!" << endl;
	cout << "Biztosan ezt szeretned? (i/n) ";
	char folytat;
	cin >> folytat;
	if (folytat != 'i') return;

	else
	{
		cout << "Add meg az adatokat tartalmazo fajl nevet! ";
		string filename;
		cin >> filename;

		ifstream input(filename.c_str());
		if (input.is_open())
		{
			spies.clear();
			agencies.clear();

//Jól látszik a file szerkezet a függvény felépítésében.
			
			//Kém beolvasás:
			int spy_count;
			input >> spy_count;
			nextSpyID = spy_count;
			for (int i = 0; i<spy_count; ++i)
			{
				int id;
				string name;
				input >> id >> name;
				if (id >= nextSpyID)
				{
					nextSpyID = id + 1;
				}
				spies.insert(pair<int, Spy*>(id, new Spy(name, id)));
			}
			//Kém kapcsolatok beolvasása:
			int rel_count_spy;
			input >> rel_count_spy;
			for (int i = 0; i<rel_count_spy; ++i)
			{
				int id1, id2;
				input >> id1 >> id2;
				spies[id1]->addNewFriend(spies[id2]);
			}
			//Ügynökség beolvasás:
			int agency_count;
			input >> agency_count;
			nextAgencyID = agency_count;
			for (int i = 0; i<agency_count; ++i)
			{
				int id;
				string name;
				input >> id >> name;
				if (id >= nextAgencyID)
				{
					nextAgencyID = id + 1;
				}
				agencies.insert(pair<int, Agency*>(id, new Agency(name, id)));
			}
			//Ügynökség kapcsolatok:
			int rel_count_agency;
			input >> rel_count_agency;
			for (int i = 0; i<rel_count_agency; ++i)
			{
				int id1, id2;
				input >> id1 >> id2;
				bool baratok;
				input >> baratok;
				agencies[id1]->setRelation(agencies[id2], baratok);
			}
			//Kém-Ügynökség viszonyok:
			int spy_ag_count;
			input >> spy_ag_count;
			for (int i = 0; i<spy_ag_count; ++i)
			{
				int id_s, id_a;
				input >> id_s >> id_a;
				spies[id_s]->setAgency(agencies[id_a]);
			}

			input.close();
			cout << "Az adatok sikeresen beolvasva!" << endl;
			cout << spy_count << " kem es " << agency_count << " ugynokseg hozzaadva az adatbazishoz." << endl;

		}
		else
		{
			cout << "Hiba a fajl megnyitasakor!" << endl;
		}
	}
}



void Menu::saveToFile()
{
	cout << "Add meg a menteni kivant fajl nevet! ";
	string filename;
	cin >> filename;

	//Az írás mechanikája gyakorlatilag az olvasással azonos.

	ofstream output(filename.c_str());
	if (output.is_open())
	{
		//Kémek kiírása:
		int spy_count = spies.size();
		output << spy_count << endl;

		int rel_count_spy = 0;
		int spy_ag_count = 0;
		for (map<int, Spy*>::iterator it = spies.begin(); it != spies.end(); ++it)
		{
			rel_count_spy += it->second->getFriendList()->size();
			if (it->second->getAgency() != NULL) ++spy_ag_count;
			output << it->first << " " << it->second->getName() << endl;
		}

		output << rel_count_spy << endl;

		//
		//Kém kapcsolatok:
		for (map<int, Spy*>::iterator it = spies.begin(); it != spies.end(); ++it)
		{
			list<User*>* current_friends = it->second->getFriendList();
			for (list<User*>::iterator it2 = current_friends->begin(); it2 != current_friends->end(); ++it2)
			{
				output << it->first << " " << (*it2)->getId() << endl;
			}
		}
		//Ügynökségek kiírása:
		int agency_count = agencies.size();

		output << agency_count << endl;

		int rel_count_agency = 0;
		for (map<int, Agency*>::iterator it = agencies.begin(); it != agencies.end(); ++it)
		{
			rel_count_agency += it->second->getRelations()->size();
			output << it->first << " " << it->second->getName() << endl;
		}
		//Ügynökségek kapcsolatai:
		output << rel_count_agency << endl;
		for (map<int, Agency*>::iterator it = agencies.begin(); it != agencies.end(); ++it)
		{
			map<Agency*, bool>* current_friends = it->second->getRelations();
			for (map<Agency*, bool>::iterator it2 = current_friends->begin(); it2 != current_friends->end(); ++it2)
			{
				output << it->first << " " << it2->first->getId() << " " << it2->second << endl;
			}
		}
		//Kém-Ügynökség viszonyok:
		output << spy_ag_count << endl;
		for (map<int, Spy*>::iterator it = spies.begin(); it != spies.end(); ++it)
		{
			if (it->second->getAgency() != NULL)
			{
				output << it->second->getId() << " " << it->second->getAgency()->getId() << endl;
			}
		}

		output.close();
		cout << "Az adatok sikeresen kimentve!" << endl;
		cout << spy_count << " kem es " << agency_count << " ugynokseg hozzaadva a kimeneti fajlhoz." << endl;

	}
	else
	{
		cout << "Hiba a fajl megnyitasakor!" << endl;
	}
}

void Menu::addNewSpy()
{
	cout << "Add meg az uj kem nevet: ";
	string name;
	cin >> name;
	spies.insert(pair<int, Spy*>(nextSpyID, new Spy(name, nextSpyID)));
	nextSpyID++;

}


void Menu::removeSpy()
{
	if (spies.size() == 0)
	{
		cout << "Sajnos nincs eleg kem ehhez a muvelethez!" << endl;
	}
	else
	{
		cout << "Add meg a kem azonositojat, akit torolni szeretnel: " << endl;
		listSpies();
		int a;
		cin >> a;

		//Ha nem létezõ azonosítót adunk meg, hibakezelés:
		try
		{
			if (!spies.count(a))
			{
				throw 1;
			}
			Spy* current = spies[a];
			list<User*>* friendlist = current->getFriendList();
			for (list<User*>::iterator it = friendlist->begin(); it != friendlist->end(); ++it)
			{
				(*it)->removeFriend(current);
			}
			spies.erase(a);
		}
		catch (int n)
		{
			cout << "Error nr.:" << n << " Hibas azonosito!" << endl;
		}
	}
}


void Menu::listSpies()
{
	map<int, Spy*>::iterator it = spies.begin();
	if (it == spies.end())
	{
		cout << "Meg nincsenek kemek!" << endl;
	}
	else
	{
		cout << "A nyilvantartasban szereplo kemek: " << endl;
		cout << "\t(ID)\t->\t(Nev)\t->\t(Ugynokseg)" << endl << endl;
		for (; it != spies.end(); ++it)
		{
			cout << "\t" << it->first << "\t->\t" << it->second->getName() << "\t->\t" << (it->second->getAgency() ? it->second->getAgency()->getName() : "<unknown>") << endl;
		}
	}
}

void Menu::listAgencies()
{
	map<int, Agency*>::iterator it = agencies.begin();
	if (it == agencies.end())
	{
		cout << "Meg nincsenek ugynoksegek!" << endl;
	}
	else
	{
		cout << "A nyilvantartasban szereplo ugynokesegek: " << endl;
		cout << "\t(ID)\t->\t(Nev)" << endl << endl;
		for (; it != agencies.end(); ++it)
		{
			cout << "\t" << it->first << "\t->\t" << it->second->getName() << endl;
		}
	}
}

void Menu::addNewFriend()
{
	if (spies.size()<2)
	{
		cout << "Sajnos nincs eleg kem ehhez a muvelethez!" << endl;
	}
	else
	{
		cout << "Add meg a ket azonositot, akik kozott az ismerettseg letrejon!";
		listSpies();
		int a, b;
		cin >> a >> b;
		try
		{
			if (!(spies.count(a) && spies.count(b)))
			{
				throw 1;
			}
			//Nobody's forever alone!
			spies[a]->addNewFriend(spies[b]);
			spies[b]->addNewFriend(spies[a]);
		}
		catch (int n)
		{
			cout << "Error nr.:" << n << " Hibas azonosito!" << endl;
		}
	}
}

void Menu::removeFriend()
{
	if (spies.size()<2)
	{
		cout << "Sajnos nincs eleg kem ehhez a muvelethez!" << endl;
	}
	else
	{
		cout << "Add meg a ket azonositot, akik kozott az ismerettseget torolni akarod!" << endl;
		listSpies();
		int a, b;
		cin >> a >> b;

		//Hibakezelés, ha nem létezõ barátságot akarunk törölni:
		try
		{
			if (!(spies.count(a) && spies.count(b)))
			{
				throw 1;
			}
			spies[a]->removeFriend(spies[b]);
			spies[b]->removeFriend(spies[a]);
		}
		catch (int n)
		{
			cout << "Error nr.:" << n << " Hibas azonosito!" << endl;
		}

	}
}

void Menu::addNewAgency()
{
	cout << "Add meg az uj ugynokseg nevet: ";
	string name;
	cin >> name;
	agencies.insert(pair<int, Agency*>(nextAgencyID, new Agency(name, nextAgencyID)));
	++nextAgencyID;
}

void Menu::removeAgency()
{
	if (agencies.size() == 0)
	{
		cout << "Sajnos nincs eleg ugynokseg ehhez a muvelethez!" << endl;
	}
	else
	{
		cout << "Add meg az ugynokseg azonositojat, amit torolni szeretnel: " << endl;
		listAgencies();
		int a;
		cin >> a;

		//Hibakezelés, ha nem létezõ ügynökséget akarunk törölni:
		try
		{
			if (!agencies.count(a))
			{
				throw 1;
			}
			Agency* current = agencies[a];

			for (map<int, Spy*>::iterator it = spies.begin(); it != spies.end(); ++it)
			{
				if (it->second->getAgency() == current)
				{
					it->second->setAgency(NULL);
				}
			}
			for (map<int, Agency*>::iterator it = agencies.begin(); it != agencies.end(); ++it)
			{
				it->second->removeRelation(current);
			}
			agencies.erase(a);
		}
		catch (int n)
		{
			cout << "Error nr.:" << n << " Hibas azonosito!" << endl;
		}
	}
}

void Menu::setSpyAgency()
{
	if (agencies.size() == 0 || spies.size() == 0)
	{
		cout << "Sajnos nincs eleg kem/ugynokseg ehhez a muvelethez!" << endl;
	}
	else
	{
		cout << "Add meg a kem, majd az ugynokseg azonositojat!" << endl;
		listSpies();
		listAgencies();
		int a, b;
		cin >> a >> b;

		//Hibakezelés, ha nem létezõ kapcsolatot akarunk törölni:
		try
		{
			if (!(spies.count(a) && agencies.count(b)))
			{
				throw 1;
			}
			spies[a]->setAgency(agencies[b]);
		}
		catch (int n)
		{
			cout << "Error nr.:" << n << " Hibas azonosito!" << endl;
		}
	}
}


void Menu::showAllForSpy()
{
	if (spies.size() == 0)
	{
		cout << "Sajnos nincs eleg kem ehhez a muvelethez!" << endl;
	}
	else
	{
		cout << "Add meg a kem azonositojat: " << endl;
		listSpies();
		int a;
		cin >> a;
		try
		{
			if (!spies.count(a))
			{
				throw 1;
			}
			Spy* current = spies[a];
			cout << current;

		}
		catch (int n)
		{
			cout << "Error nr.:" << n << " Hibas azonosito!" << endl;
		}
	}
}

void Menu::showAllForAgency()
{
	if (agencies.size() == 0)
	{
		cout << "Sajnos nincs eleg ugynokseg ehhez a muvelethez!" << endl;
	}
	else
	{
		cout << "Add meg az ugynokseg azonositojat: " << endl;
		listAgencies();
		int a;
		cin >> a;
		try
		{
			if (!agencies.count(a))
			{
				throw 1;
			}
			cout << agencies[a];
		}
		catch (int n)
		{
			cout << "Error nr.:" << n << " Hibas azonosito!" << endl;
		}
	}
}


void Menu::setAgencyRelation()
{
	if (agencies.size()<2)
	{
		cout << "Sajnos nincs eleg ugynokseg ehhez a muvelethez!" << endl;
	}
	else
	{
		cout << "Add meg a ket azonositot, akik kozott a viszony letrejon!" << endl;
		listAgencies();
		int a, b;
		cin >> a >> b;
		//Hibakezelés, ha nem létezõ elemek között akarunk kapcsolatot létrehozni:
		try
		{
			if (!(agencies.count(a) && agencies.count(b)))
			{
				throw 1;
			}
			cout << "Baratsagos a ket ugynokseg? (i/n)";
			char f;
			cin >> f;
			bool friendly = f == 'i';
			agencies[a]->setRelation(agencies[b], friendly);
			agencies[b]->setRelation(agencies[a], friendly);
		}
		catch (int n)
		{
			cout << "Error nr.:" << n << " Hibas azonosito!" << endl;
		}
	}
}