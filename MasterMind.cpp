#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Kezdeti beállító függvény:
char setup() {

	int dice = rand() % 6 + 1;

	switch (dice) {
	case 1:
		return 'R';

	case 2:
		return 'O';

	case 3:
		return 'Y';

	case 4:
		return 'G';

	case 5:
		return 'B';

	case 6:
		return 'V';
	}


}
//Válasz ellenõrzõ függvény:
bool check(char guess[], char secret[]) {

	bool Checked[4];
	for (int i = 0; i < 4; i++) Checked[i] = false;
	int RightColour = 0;
	int RightPlace = 0;

	//Jó szín és jó hely ellenõrzése.
	for (int i = 0; i < 4; i++) {
		if (secret[i] == guess[i]) {
			RightPlace++;
			Checked[i] = true;
		}
	}

	//Jó szín, de rossz hely ellebõrzése.
	for (int i = 0; i < 4; i++) {
		if (Checked[i] == false) {
			if (secret[i] == guess[0] || secret[i] == guess[1] || secret[i] == guess[2] || secret[i] == guess[3]) {
				RightColour++;
				Checked[i] = true;
			}
		}
	}

	if (RightPlace == 4) {
		cout << endl;
		cout << "********************************" << endl;
		cout << "*       Congratulations!       *" << endl;
		cout << "*  You are a true MasterMind!  *" << endl;
		cout << "********************************" << endl;
		return true;
	}
	else {
		cout << endl;
		cout << RightPlace << " guesses are the RIGHT COLOUR and in the RIGHT PLACE." << endl;
		cout << RightColour << " guesses are the RIGHT COLOUR but in the WRONG PLACE." << endl;
		cout << endl;
		return false;
	}
}

int main() {

	srand(time(NULL));
	char secret[4];
	char guess[4];
	int TurnCount = 1;
	bool GameEnd = false;

	cout << "Welcome to the MasterMind game!" << endl;
	cout << endl;
	cout << "I have four colours for you to find out." << endl;
	cout << endl;
	cout << "You can choose from the following: Red, Orange, Yellow, Green, Blue, Violet" << endl;
	cout << "Use the first letters of the respective colours as indicators. (R, O, Y, G, B, V)" << endl;
	cout << endl;
	cout << "If you can find out my secret in less than 10 rounds, you win!" << endl;
	cout << "Let the game begin!" << endl;

	//Kezdeti beállítás:
	for (int i = 0; i < 4; i++) {
		secret[i] = setup();

		//ellenõrzés magamnak
		//cout << secret[i] << " ";
	}

	//Maga a játék.
	while (GameEnd == false) {

		cout << endl;
		cout << "--------------------------------------------------------" << endl;
		cout << endl;
		if (TurnCount < 10) {
			cout << "You are in the " << TurnCount << ". turn." << endl;
		}
		else {
			cout << "You are in the LAST turn." << endl;
		}

		//Felhasználó tippel:
		for (int i = 0; i < 4; i++) {
			cout << "Guess for the " << i + 1 << ". colour:";
			cin >> guess[i];
			//Valós válasz ellenõrzése:
			if (guess[i] != 'R' && guess[i] != 'O' && guess[i] != 'Y' && guess[i] != 'G' && guess[i] != 'B' && guess[i] != 'V') {
				cout << "Invalid guess. Try again!";
				i--;
			}
		}
		//Ellenõrzés
		GameEnd = check(guess, secret);

		TurnCount++;
		if (TurnCount > 10) {
			cout << endl;
			cout << "Sorry, but you have ran out of guesses." << endl;
			GameEnd = true;
		}

	}

	cout << endl;
	cout << "Thank you, for playing with me!" << endl;
	cout << endl;
	cout << endl;
	cout << "..........Press ENTER to exit the program.........." <<endl;

	cin.get();
	cin.get();
	return 0;
}