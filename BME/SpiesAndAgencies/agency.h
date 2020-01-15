#ifndef AGENCY_H_INCLUDED
#define AGENCY_H_INCLUDED

#include "user.hpp"
#include <map>
#include <set>

using namespace std;

//Az �gyn�ks�gek oszt�lya, szint�n a f�ggv�nynevek seg�tenek.

class Agency : public User {
protected:
	//Kapcsolatokhoz i/h az assz.t�mbben.
	map<Agency*, bool> relations;
public:
	Agency(const string&, int);
	~Agency();
	
	void setRelation(Agency*, bool);
	map<Agency*, bool>* getRelations();
	void removeRelation(Agency*);

	void listFriends(ostream&, int);

	friend ostream& operator <<(ostream&, Agency*);
};
#endif //AGENCY_H_INCLUDED