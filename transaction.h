// 
//
//
// created by Marci Ma on 11/30/2019
// transaction class that store different type of transaction
//
//
//


#ifndef ASS5_TRANSACTION_H
#define ASS5_TRANSACTION_H

#include <string>
#include <iostream>

using namespace std;

class Transaction{
	friend ostream& operator<<(ostream& out, const Transaction& trans);
public:
	// constructor, store each info from the account
	Transaction(char transactionType, string firstName, string lastName, string Fail, int accountID, 
		int fundID, int transferAccountID, int transferFundID, int amount);
	// destructor
	~Transaction();
	
	// check if the transaction fail or not
	bool isFailed();
	// return the transaction type
	char getTransactionType() const;
	// return the first name
	string getFirstName() const;
	//return the last name
	string getLastName() const;
	// return the account ID
	int getAccountID() const;
	// return the Fund ID
	int getFundID() const;
	// return the transfer Account ID
	int getTransferAccountID() const;
	// return the transfer Fund ID
	int getTransferFundID() const;
	// return the amount
	int getAmount() const;

private:
	char transactionType;
	string firstName;
	string lastName;
	string fail;
	int accountID, fundID, transferAccountID, transferFundID, amount;
};


#endif //ASS5_TRANSACTION_H