#include <iostream>		
#include <thread>	 
#include <chrono>
#include <conio.h>

using namespace std;			// cout, endl
using namespace this_thread;	// sleep_for
using namespace chrono;			// seconds, milliseconds
const enum State { Sit = 0, Stand = 1, Hungry = 2, Eat = 3 };

int main()
{
	State newState = State::Sit;
	State currentState = State::Sit;
	
	const int eatingSeconds = 300;
	const int standingSeconds = 15;
	int currentEatingSeconds = eatingSeconds;
	int currentStandingSeconds = standingSeconds;

	bool program_running = true;
	cout << "Starting Finite State Machine" << endl;
	cout << "0 - Make spectator sit" << endl;
	cout << "1 - Make spectator's team score" << endl;
	cout << "2 - Make spectator's opponent team score" << endl;
	cout << "3 - Make spectator feel hungry" << endl;
	cout << "Spectator is sitting" << endl;
	do {

		switch (currentState) {

		case State::Sit:
			if (newState != Eat && newState != currentState) currentState = newState;
			break;

		case State::Stand:
			if (newState != Eat && newState != currentState) currentState = newState;

			if (currentStandingSeconds == 0) {
				currentState = Sit;
				newState = Sit;
				currentStandingSeconds = 15;
				cout << "Spectator sits" << endl;
			} else {
				cout << "Seconds left standing: " << currentStandingSeconds << endl;
				currentStandingSeconds--;
			}
			break;

		case State::Hungry:
			cout << "Getting some food..." << endl;
			sleep_for(milliseconds(3000));
			currentState = Eat;
			newState = Eat;
			cout << "Grabbed food" << endl;
			break;

		case State::Eat:

			if (currentEatingSeconds == 0) {
				currentState = Sit;
				newState = Sit;
				currentEatingSeconds = eatingSeconds;
				cout << "Spectator finished eating" << endl;
			} else {
				cout << "Seconds left eating: " << currentEatingSeconds << endl;
				currentEatingSeconds--;
			}
			break;
		}

		// Sleep the current thread for 1000 milliseconds. Can be repalce with seconds(1)
		sleep_for(milliseconds(1000));

		if (_kbhit())
		{
			char input_char = _getch();

			// Check for ESC key. See table here http://www.asciitable.com/
			if (input_char == 27)
			{
				program_running = false;
			}

			if (input_char == 48) { //0
				//Make spectator sit
				cout << "Spectator sits" << endl;
				newState = Sit;
			}
			if (input_char == 49) { //1
				//Make spectator's team score
				cout << "Spectator stands and cheers" << endl;
				newState = Stand;
			}
			if (input_char == 50) { //2
				//Make opponent's team score
				cout << "Spectator stands and booes" << endl;
				newState = Stand;
			}
			if (input_char == 51) { //3
				//Make spectator hungry
				cout << "Spectator starts to feel hungry" << endl;
				newState = Hungry;
			}
		}

	} while(program_running);

	cout << "Ending Finite State Machine" << endl;

	return 0;
}