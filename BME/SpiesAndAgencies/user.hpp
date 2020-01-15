#ifndef USER_HPP_INCLUDED
#define USER_HPP_INCLUDED

#include <iostream>
#include <string>
#include <list>

using namespace std;

// Õ volna az õsosztály, a spy.h, és az agency.h örököl tõle.

class User {
protected:
	const int id;
	const string name;
	list<User*> known_users;
public:
	User(const string& n, int i) : name(n), id(i) {}

	virtual ~User() {}

	void addNewFriend(User* u) {
		known_users.push_back(u);
	}

	void removeFriend(User* u) {
		known_users.remove(u);
	}

	int getId()
	{
		return id;
	}

	list<User*>* getFriendList()
	{
		return &known_users;
	}

	virtual void listFriends(ostream&, int) = 0;

	string getName()
	{
		return name;
	}
};
#endif //USER_HPP_INCLUDED