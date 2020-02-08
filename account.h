//
//
// created by Marci Ma on 11/29/2019
//
//

#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include "transaction.h"
#include "fund.h"
#include <iostream>
#include <string>

using namespace std;

const int FUND_MAX = 10;

class Account {

	friend ostream& operator << (ostream& out, Account& acct);

 public:
	 // constructor
	 Account(string firstName, string lastName, int accountID);
	 // destructor
	 ~Account();
	 
	 // add amount to the account (deposit)
	 void addToAccount(int fundID, int amount);
	 // take amount from the account (withdraw)
	 bool minusFunds(int fundID, int amount, Transaction frontTrans);
	 // record the transaction
	 void recordTrans(Transaction trans, int fundID);
	 // withdraw with relative account
	 void widthFromSimilarAcct(int pFund, int sFund, int amount);
	 // print account history
	 void printHistory();
	 // print the specific fund history
	 void printFundHistory(int fundID);
	 // show the error messege
	 void error(int amount, string firstName, string lastName, int fundID);

	 // return the account ID
	 int getAccountID() const;
	 // return the balance in the account
	 int getBalance(int fundID)const;
	 // return the fund titile
	 string getFundName(int fundID);
	 // return the first name
	 string getFirstName() const;
	 // return the last name
	 string getLastName()const;
	 // set the fund ID
	 void setFundID(int fundID);
		  
private:
	string firstName, lastName;
	int accountID;
	int fundID;
	Fund arrayFund[FUND_MAX];
};
#endif // ASS5_ACCOUNT_H
