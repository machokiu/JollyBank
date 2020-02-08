//
//
// created by Marci Ma on 11/30/2019
// fund class that store relvant fund process
//
//

#ifndef ASS5_FUND_H
#define ASS5_FUND_H

#include "transaction.h"
#include <vector>


class Fund {

public:
	// constructor, balance set to 0
	Fund(int balance = 0);
	// destructor 
	~Fund();

	// minus the amount
	bool withdraw(int amount);
	// add the amount
	bool deposit(int amount);
	// check the fund balance to ensure user can withdraw the amount
	bool balanceCheck(int amount);
	// store the transaction to history
	bool recordTransaction(Transaction trans);
	//The printHistory() function checks to see if the size of the vector is equal to 0
   	void printHistory();
	//the printHistoryOfFund() function prints the history of a specific fund
	void printHistoryOfFund();
	// set the Fund Name
	void setName(string name);
	// return the fund Name
	string getName() const;
	// return the current balance
	int getBalance() const;


private:
	string fundName;
	int balance;
	vector<Transaction> history;
};


#endif //ASS5_FUND_H