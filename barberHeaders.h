#pragma once

//this contains all the attributes in the barber and client class

class Barber {
	int currentClient; //the client whose hair are being cut currently
	int timeToCutHair; //time taken to cut his hairr
	void barberWorking(); //This function fires when a customer arriver
	void barberLock(); //This function makes the barber
	
public: void start(); // This starts the barber thread
};


class Client {
	int ID; //sets the id of a client/customer
	void waitInQueue(int queueNumber); //called when the client has to wait in the queue
	void leave(int clientNum); //called when there is no space to wait
	void waitOrLeave(int id, int totalSeats); // when the client decides to wait or leave
	int totalSeats; //total seats available in the waiting area
	int generating_time; //time in which a client is generated

public: void generateNewClient(int threadNum); //starts the client thread
};
