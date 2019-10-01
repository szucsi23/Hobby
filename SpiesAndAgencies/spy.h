#ifndef SPY_H_INCLUDED
#define SPY_H_INCLUDED

#include "user.hpp"
#include "agency.h"

using namespace std;

//A k�meket kezel� oszt�ly, a f�ggv�ny nevek alapj�n lethat�, hogy mit csin�lnak.

class Spy : public User {
protected:
	Agency* myAgency;
public:
	Spy(const string&, int);

	~Spy();

	void setAgency(Agency*);

	Agency* getAgency();

	void showAgency(ostream&);

	void listFriends(ostream&, int);


	friend ostream& operator <<(ostream&, Spy*);
};
#endif //SPY_H_INCLUDED