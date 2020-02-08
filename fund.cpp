//
//
// created by Marci Ma on 11/30/2019
// fund class that store relvant fund process
//
//

#include "fund.h"
#include <vector>

// constructor, balance set to 0
Fund::Fund(int balance) :balance{balance}{
}

// destructor 
Fund::~Fund(){
}

// minus the amount
bool Fund::withdraw(int amount) {
	balance -= amount;
	return true;
}

// add the amount
bool Fund::deposit(int amount){
	balance += amount;
	return true;
}
// check the fund balance to ensure user can withdraw the amount
bool Fund::balanceCheck(int amount){
	return (balance >= amount);
}

// store the transaction to history
bool Fund::recordTransaction(Transaction trans){
	history.push_back(trans);
	return true;
}

//The printHistory() function checks to see if the size of the vector is equal to 0
//If if is equal to 0, it does not print anything.  If the vector is filled it 
//then cycles through it and prints the transactions
void Fund::printHistory(){
	if (history.empty())
		return;
	else{
		cout << fundName << ": $" << balance << endl;
		for (int I = 0; I < history.size(); ++I){
			cout << " " << history[I]<< endl;
		}
	}
}

//the printHistoryOfFund() function prints the history of a specific fund
void Fund::printHistoryOfFund(){
	for (int I = 0; I < history.size(); ++I)
		cout << " " << history[I] << endl;
}

// set the Fund Name
void Fund::setName(string name){
	this->fundName = name;
}

// return the fund Name
string Fund::getName() const{
	return fundName;
}

// return the current balance
int Fund::getBalance() const {
	return balance;
}