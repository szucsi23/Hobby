#include <iostream>
#include <string>
#include <list>
#include <map>
#include <set>

#include "agency.h"

using namespace std;

//Az agency.h függvényei megírva.

Agency::Agency(const string& n, int id) : User(n, id) {}

void Agency::setRelation(Agency* other, bool isFriendly)
{
	if (other == this) return;
	relations.insert(pair<Agency*, bool>(other, isFriendly));
}

Agency::~Agency()
{

}

void Agency::removeRelation(Agency* a)
{
	
	relations.erase(a);
}

map<Agency*, bool>* Agency::getRelations()
{
	return &relations;
}


void Agency::listFriends(ostream& os, int mode)
{
	cout << getName() << "\'s contacts: " << endl;
	int i = 1;

	map<Agency*, bool>::iterator it = relations.begin();
	if (it == relations.end())
	{
		cout << "\t " << getName() << " does not have any contact yet." << endl;
	}
	else while (it != relations.end())
	{
		cout << "\t" << i << ".: " << it->first->getName() << ", status: " << (it->second ? "friendly" : "enemy") << endl;
		++it;
		++i;
	}
}


ostream& operator <<(ostream& os, Agency* usr) {
	os << "Name: " << usr->getName() << endl;
	os << "\tNumber of contacts: " << usr->relations.size() << endl;
	usr->listFriends(os, 1);
	return os;
}