# sleepingBarberProblem
Problem Description
This problem is about simulating a barber shop with the following characteristics. The barber shop has a waiting room with M seats and a separate room with a single barber chair where the barber works. If there are no waiting customers, nor a customer having a haircut, the barber takes a break and sleeps. The moment a customer arrives, s/he wakes the barber up so that they can have their haircut. If another customer arrives while the barber is working, s/he will either sit in the waiting room (if there are available seats) or leave (if no seats are available).

Implementation Details
The only (command line) input for your program will be the number M of seats in the waiting room. The barber needs to be implemented as a thread which runs indefinitely, always performing one of the 3 possible tasks: sleeping, waking up and working. The barber sleeps if there are no awaiting customers.

There must be a thread which is responsible for creating new threads from time to time to simulate new customers arriving in the barber shop. This thread should run an infinite loop creating new threads every 3 seconds. Each created thread need to receive an integer parameter (sequentially incremented) which will serve as the customer ID.

In the beginning of the program, the barber is sleeping and there are no customers in the shop. When a customer arrives, s/he wakes the barber up so that they can have their haircut. The haircut is to be simulated with a thread sleep of N seconds, where N is a random number between 1 and 5, inclusive (i.e. [1,5]). If a new customer (thread) arrives while the barber is busy, they should wait in one of the seats of the waiting room, if one is available, or leave if none is available. Leaving is simulated by simply terminating the execution of the thread.
