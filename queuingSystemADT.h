#pragma once
#include "queueAsArray.h"
#include <string>
#include <random>
#include <cmath>
#include <vector>
using namespace std;

class customer
{
public:
	void setCustomerID(int newID)
	{
		customerID = newID;
		return;
	}
	//Sets the customer ID to a random value
	int getCustomerID()
	{
		return customerID;
	}
	//Fetches customer ID from unique customer
	void updateWaittime()
	{
		waittime++;
		return;
	}
	//Updates wait time by incrementing by one
	int getWaittime()
	{
		return waittime;
	}
	//Fetches current wait time from customer

	customer()
	{
		customerID = rand() % 65536;
		waittime = 0;
	}
	//Constructor

	customer(int ID, int time)
	{
		customerID = ID;
		waittime = time;
	}
	//Second Constructor

private:
	int customerID;
	int waittime;
};

class customerQueue : public queueType<customer>
{
public:
	int getNumArrivals()
	{
		return numberOfArrivals;
	}
	//Fetches the number of people who arrived during the entire simulation

	int addCustomer(customer newPerson)
	{
		if (!isFullQueue())
		{
			waitingQueue.addQueue(newPerson);
			//cout << waitingQueue.front().getCustomerID() << endl;
			numberOfArrivals++;
			sizeOfQueue++;
			//cout << waitingQueue.front().getCustomerID() << endl;
			return newPerson.getCustomerID();
		}
	}
	//Precond: A new customer is created and a queue exists
	//Postcond: The new customer is inserted at the end of the queue

	customer removeCustomer()
	{
		if (!isEmptyQueue() || getNumCustomersInQueue() > 0)
		{
			customer currentCustomer = waitingQueue.front();
			//int ID = waitingQueue.front().getCustomerID();
			//int time = waitingQueue.front().getWaittime();
			//customer currentCustomer(ID, time);
			//cout << "Customer " << currentCustomer.getCustomerID() << " has left the queue." << endl;
			waitingQueue.deleteQueue();
			sizeOfQueue--;
			return currentCustomer;
		}
	}
	//Precond: A pre-existing, non-empty list exists
	//Postcond: The front customer is removed from the queue and returned, to be used in a server



	//Precond: A non-full customer queue exists
	//Postcond: If a randomly-generated number is greater than a certain number
	//			(Euler's number to the power of -1/(timebetweenArrivals), then a new person
	//			enters the queue. Otherwise, no new people arrive.
	bool hasCustomerArrived()
	{
		mt19937 rng(random_device{}());
		uniform_real_distribution<double> dist(0, 1);
		double chance = dist(rng);
		double lambda = 1.0 / timeBetweenArrivals;
		if (chance > exp(-1 * lambda))
		{
			return true;
		}
		else return false;
	}

	//Precond: One unit of time passes
	//Postcond: Each customer's waittime gets updated, incrementing by one.
	//			This was accomplished by copying the contents of the wait
	//			queue into a new, temporary queue, indivudially updating
	//			each customer's wait time as they pass by, before re-copying
	//			the contents back to the original queue.
	void updateCustomerWaittimes()
	{
		customerQueue tempQueue;
		int length = getNumCustomersInQueue();
		for (int i = 0; i < length; i++)
		{
				customer current = removeCustomer();
				//cout << current.getCustomerID() << endl;
				current.updateWaittime();
				tempQueue.push(current);
		};
		for (int i = 0; i < length; i++)
		{
			customer current = tempQueue.removeCustomer();
			waitingQueue.push(current);
		};
	}

	int getNumCustomersInQueue()
	{
		return sizeOfQueue;
	}

	//Precond: A new unit of time between arrivals is given
	//Postcond: The timeBetweenArrivals variable is updated.
	void setTimeBetweenArrivals(int time)
	{
		timeBetweenArrivals = time;
		return;
	}

	//Precond: The simulation ends
	//Postcond: The function fetches the remaining wait time for each customer, one customer at a time
	int getRemainingWaittime()
	{
		int customerWaittime = waitingQueue.front().getWaittime();
		waitingQueue.pop();
		return customerWaittime;
	}

	//Constructor
	customerQueue(int timeBetweenCustomers = 4)
	{
		setTimeBetweenArrivals(timeBetweenCustomers);
		sizeOfQueue = 0;
	}

private:
	queueType waitingQueue;
	int timeBetweenArrivals;
	int numberOfArrivals;
	int sizeOfQueue;
};

class server
{
public:
	//Sets the server ID
	void setServerID(int newID)
	{
		serverID = newID;
		return;
	}

	//Gets the server ID
	int getServerID()
	{
		return serverID;
	}

	//Sets server status - true if busy
	void setIfBusy(bool status)
	{
		isBusy = status;
	}

	//Fetches server status - true if busy
	bool isServerBusy()
	{
		return isBusy;
	}

	//Sets transaction time
	void setTransactionTime(int time)
	{
		transactionTime = time;
	}

	//Gets transaction time
	int getTransactionTime()
	{
		return transactionTime;
	}

	//Updates transaction time
	int updateTransactionTime()
	{
		cout << "Transaction Time: " << transactionTime << endl;
		transactionTime--;
		//setTransactionTime(transactionTime - 1);
		if (transactionTime == 0)
		{
			isBusy = false;
		}
		cout << "Transaction Time: " << transactionTime << endl;
		return transactionTime;
	}

	//Gets customer's wait time
	int getCustomerWaittime()
	{
		return current.getWaittime();
	}

	//Gets customer ID
	int getCustomerID()
	{
		//cout << "Current Customer: " << current.getCustomerID() << endl;
		return current.getCustomerID();
	}

	//Add customer to server
	void retrieveCustomer(customer newGuy, int newTransTime)
	{
		//cout << transactionTime << endl;
		if (!isServerBusy())
			cout << "Server " << getServerID() << " currently has Customer " << getCustomerID() << endl;
		else
		{
			current = newGuy;
			setTransactionTime(newTransTime);
			//cout << "Transaction Time: " << transactionTime << endl;
			cout << "Customer Time: " << current.getWaittime() << endl;
			setIfBusy(true);
		}
	}

	//Constructor
	server(int servID = 0, int defaultTransTime = 1)
	{
		serverID = servID;
		transactionTime = defaultTransTime;
		isBusy = false;
	}

private:
	int serverID;
	bool isBusy;
	int transactionTime;
	customer current;
};

class serverList
{
public:
	//Adds a server to the list
	void addServer(const server newServer)
	{
		list.push_back(newServer);
	}

	//Precond: A server list full of free and/or busy server is created
	//Postcond: Returns -1 if all the servers are busy. Otherwise returns the first server available.
	int findFreeServer()
	{
		for (server current : list)
		{
			if (!current.isServerBusy())
				return current.getServerID();
			//else
				//cout << "I see this as a busy server." << endl;
		}
		return -1;
	}

	//Sets the initial transaction time for servers upon recieving a customer
	void setServerTransTime(int newTime)
	{
		serverTransTime = newTime;
	}

	//Assigns customer to a free server
	void assignCustomer(customer currCustomer, int servID)
	{
		//cout << "Test Run: " << servID << endl;
		for (server current : list)
		{
			if (current.getServerID() == servID)
			{
				//cout << "Customer " << currCustomer.getCustomerID() << " is being assigned at Server " << servID << endl;
				current.retrieveCustomer(currCustomer, serverTransTime);
				return;
			}
		}
	}

	//Precond: One time unit passes
	//Postcond: Transaction times are updated for each server
	void updateServerTimes()
	{
		for (server current : list)
		{
			current.setTransactionTime(current.updateTransactionTime());
			if (current.getTransactionTime() <= 0)
			{
				customersServed++;
				totalWaittime += current.getCustomerWaittime();
				current.setIfBusy(false);
				cout << "Customer " << current.getCustomerID() << " departs Server " << current.getServerID() << endl;
			}
			else //else statement used for testing/debugging
			{
				current.setIfBusy(true);
			}
		}
	}

	//Fetches total number of customers served
	int getTotalCustServed()
	{
		return customersServed;
	}

	//Fetches total waittime passed
	double getTotalWaittime()
	{
		return totalWaittime;
	}

	//Calculates average waittime
	double calcAverageTime()
	{
		return customersServed / totalWaittime;
	}

	//Constructor
	serverList(int numServers = 1, int transTime = 1)
	{
		serverCount = numServers;
		serverTransTime = transTime;
		for (int i = 0; i < serverCount; i++)
		{
			//cout << i << endl;
			server newServer(i, serverTransTime);
			addServer(newServer);
		}
	}

private:
	int serverCount;
	int serverTransTime;
	int customersServed;
	double totalWaittime;
	double avgWaittime;
	vector<server> list;
};

class queuingSystem
{
public:
	//Fetches the simulation's parameters, namely
	//	the time units to measure to, the transaction time
	//	between the customer and server, the average arrival
	//	time between customers, and how many servers to use.
	//	Also creates the customer queue and server list
	queuingSystem(int units, int trans, int arrival, int servers = 1)
	{
		timeUnits = units;
		transactionTime = trans;
		averageArrivalTime = arrival;
		numServers = servers;
		customerQueue newQueue(averageArrivalTime);
		serverList newList(numServers, transactionTime);
		queue = newQueue;
		list = newList;

		mainLoop();
	}

	//The main loop for the simulation
	void mainLoop()
	{
		for (int timeIndex = 0; timeIndex < timeUnits; timeIndex++)
		{
			cout << "Interval: " << timeIndex << endl;
			list.updateServerTimes();
			int freeServ = list.findFreeServer();
			if (queue.getNumCustomersInQueue() > 0)
				queue.updateCustomerWaittimes();
			if (queue.hasCustomerArrived())
			{
				customer newCust;
				cout << "New customer: " << queue.addCustomer(newCust) << endl;
				//cout << "Customer ID: " << queue.removeCustomer().getCustomerID() << endl;
			}
			cout << "Free Server: " << freeServ << endl;
			if (freeServ != -1 && queue.getNumCustomersInQueue() > 0)
			{
				customer nextCustomer = queue.removeCustomer();
				//cout << "Customer " << nextCustomer.getCustomerID() << " to Server " << freeServ << endl;
				list.assignCustomer(nextCustomer, freeServ);
			}
		}
		printResults();
	}

	//Prints out the results
	void printResults()
	{
		cout << "Number of customers left: " << queue.getNumCustomersInQueue() << endl;
		cout << "Number of customers arrived: " << queue.getNumArrivals() << endl;
		cout << "Number of customers with completed transactions: " << list.getTotalCustServed() << endl;
		cout << "Average wait time: " << list.calcAverageTime() << " units of time." << endl;
	}

private:
	int timeUnits; //Time limit
	int transactionTime; //Transaction time between customer, server
	int averageArrivalTime; //Avg arrival time of customers to queue
	int numServers; //Number of sevrers active
	customerQueue queue;
	serverList list;
};