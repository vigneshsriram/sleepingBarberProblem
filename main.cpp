#include <iostream>
#include <thread>
#include "barberHeaders.h"
using namespace std;


int main(int argc, char** argv)
{
	int totalSeats;
	if (argc == 2) {
		totalSeats = (int)argv[1];
	}
	else {
		//get seats
		
		cout << "Please enter number of seats in the waiting room : ";
		cin >> totalSeats;

		//Error check for wrong inputs
		if (!cin) {
			cout << "Wrong inputs. Seats set to 5 by default";
			totalSeats = 5;

		}

		if (totalSeats <= 0) {
			cout << "Number of seats cannot be 0 or negative. Seats set to 5 by default";
			totalSeats = 5;
		}

	}
	


	//create the objects
	Barber barber;
	Client client;

	//create threads
	thread barberThread(&Barber::start, barber);
	thread clientThread(&Client::generateNewClient, client, totalSeats);
	barberThread.join();
	clientThread.join();

	return 0;
}
