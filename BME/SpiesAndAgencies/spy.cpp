#include "spy.h"
#include <iostream>

using namespace std;

//A spy.h f�ggv�nyeinek megval�s�t�sa.

Spy::Spy(const string& n, int id) : User(n, id)
{
	myAgency = NULL;
}

Spy::~Spy()
{

}

void Spy::setAgency(Agency* ag)
{
	myAgency = ag;
}

Agency* Spy::getAgency()
{
	return myAgency;
}


void Spy::showAgency(ostream& os)
{
	//Hibakezel�s, ha nincs �gyn�ks�ge az adott k�mnek:
	try {
		if (myAgency) {
			os << getName() << "\'s agency: " << myAgency->getName() << endl;

		}
		else {
			throw 1;
		}
	}
	catch (int n) {
		cout << "Error nr." <<n <<": "<< name << "\'s agency was not defined yet!" <<std::endl;
	}
}

void Spy::listFriends(ostream& os, int mode)
{
	if (known_users.size() != 0)
	{
		os << "Known friends: " << endl;
		int i = 1;
		for (list<User*>::iterator it = known_users.begin(); it != known_users.end(); ++it, ++i)
		{
			os << "\t" << i << ".:" << (*it)->getName() << endl;
		}
	}
}


ostream& operator <<(ostream& os, Spy* usr) {
	os << "Name: " << usr->getName() << endl;
	usr->showAgency(os);
	os << "\tNumber of friends: " << usr->known_users.size() << endl;
	usr->listFriends(os, 1);
	return os;
}

