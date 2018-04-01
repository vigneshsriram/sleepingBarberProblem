#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <string>
#include <condition_variable>
#include "barberHeaders.h"

using namespace std;


mutex seatLock; // lock barbers seat
mutex mutexPrint;  // allows only 1 print
mutex mutexSleep;  // control the barber awake or not
condition_variable cv;
int barberSleeping = 1;
int waitingQueue = 0;  //how many customers are waiting
string noPlace = "";  //for customers who have no place left
queue<int>waitLisit; //create a queue for the waiting customers
int breaker = 0;
//refrenced from github
//*****************BARBER*****************************//
// to control barber is awake or sleeping
void Barber::barberLock() {
	// whizzy class with destructor that unlocks mutex
	unique_lock < mutex > lock(mutexSleep);
	//This is to lock the barber when he starts working on 1 customer
	while (barberSleeping && waitingQueue == 0) {

		cout << "\nBarber sleeping" << "\n";
		cout << "Waiting room : " << "\n";
		cv.wait(lock);
	}
}

void Barber::barberWorking() {
	//locks the seat on which barber cuts hair
	lock_guard<mutex> lock(seatLock);
	waitingQueue = waitingQueue - 1; 
	currentClient = waitLisit.front();
	
	if (!waitLisit.empty()) {
		waitLisit.pop();
	}
	int maxTimeInSecs = 5; // To change max duration of haircut change here
	timeToCutHair = rand() % maxTimeInSecs*1000 + 1000;
	this_thread::sleep_for(chrono::milliseconds(timeToCutHair)); //makes the thread go to sleep
	barberSleeping = 1;  //barber sleeps again
}

//This is start the barber thread
void Barber::start() {
	while (true) {
		// wont allow barber to do anything except sleep
		barberLock();

		//wakes up barber and he starts cutting hair of customer
		barberWorking();

		// updates are sent
		lock_guard<mutex> lock(mutexPrint);
		cout << "\nBarber is cutting the hair of customer " << currentClient << "\n";
		cout << "Waiting room : ";
		queue<int>tempQ = waitLisit;
		for (int i = 0;  i < waitLisit.size(); i++) {
			int a = tempQ.front();
			cout <<  a << "\t";
			tempQ.pop();
		}
		cout << "\n" << noPlace;
		noPlace = "";
		
		if (waitLisit.size() == 0 && breaker == 1 && currentClient == 200) {
			cout << "\nNo more customers. Barber sleeps now";
		}

	}
}


//*****************CLIENT/CUSTOMER*****************************//
// generating new Clients
void Client::generateNewClient(int threadNum) {
	thread clientThreads[200];
	Client client;
	for (int i = 0; i < 200; i++) {
		this_thread::sleep_for(chrono::milliseconds(3000)); // this generates a client every 3 secs
		clientThreads[i] = thread(&Client::waitOrLeave, client, i + 1, threadNum); //generates thread i
	}
	for (int i = 0; i < 200; i++) {
		clientThreads[i].join();
		if (i == 199) {
			breaker = 1;
		}
	}

	
}


// client leaves if no place to wait
void Client::leave(int clientNum) {
	lock_guard<mutex> lock(mutexPrint);
	int end = waitLisit.back();
	
	if (clientNum - (end + 1) > 0) {
		noPlace = "Customer " + to_string(end + 1) + " to " + to_string(clientNum) + " are leaving\n";
	}
	else {
		noPlace = "Customer " + to_string(clientNum) + " is leaving\n";
	}
}

//client added to queue if place in queue
void Client::waitInQueue(int queueNumber) {
	unique_lock < mutex > lock(mutexSleep);
	waitingQueue = waitingQueue + 1;
	barberSleeping = 0;
	if (waitingQueue > 0) {
		waitLisit.push(queueNumber); //[ush client in wait list
	}
	
}


//Decides whether the client should wait or leave depending upon the seats available
void Client::waitOrLeave(int id, int totalseats) {
	ID = id;
	totalSeats = totalseats;
	if (waitingQueue >= totalSeats) {
		leave(ID);
	}
	else {
		waitInQueue(ID);
		cv.notify_all();
	}
}



