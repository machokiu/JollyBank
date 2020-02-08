// 
//
//
// created by Marci Ma on 11/30/2019
// transaction class that store different type of transaction
//
//
//

#include "transaction.h"
#include <iostream>

using namespace std;


ostream& operator<<(ostream& out, const Transaction& trans) {
	if (trans.fail.empty()) {
		if (trans.getTransactionType() == 'D' || trans.getTransactionType() == 'W') {
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() <<
				trans.getFundID() << " " << trans.getAmount() << endl;
		}
		else if (trans.getTransactionType() == 'T') {
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() 
				<< trans.getFundID() << " " << trans.getAmount() << " " 
				<< trans.getTransferAccountID() << trans.getTransferFundID() << endl;
		}
		else {
			if (trans.getTransactionType() == 'D' || trans.getTransactionType() == 'W') {
				out << " " << trans.getTransactionType() << " " << trans.getAccountID() <<
					trans.getFundID() << " " << trans.getAmount() << " (FAILED)" << endl;
			}
			else if (trans.getTransactionType() == 'T') {
				out << " " << trans.getTransactionType() << " " << trans.getAccountID()
					<< trans.getFundID() << " " << trans.getAmount() << " " << trans.getTransferAccountID()
					<< trans.getTransferFundID() << "(FAILED)" << endl;
			}
		}
	}
	return out;
}

// constructor, store each info from the account
Transaction::Transaction(char transactionType, string firstName, string lastName,
	string fail, int accountID, int fundID, int transferAccountID,
	int transferFundID, int amount) 
	: transactionType{ transactionType }, firstName{ firstName }, lastName{ lastName },
	fail{fail}, accountID{ accountID }, fundID{ fundID }, 
	transferAccountID{ transferAccountID }, transferFundID{transferFundID}, amount{amount}{
}

// destructor
Transaction :: ~Transaction() {
}

// check if the transaction fail or not
bool Transaction::isFailed() {
	return fail.empty();
}

// return the transaction type
char  Transaction::getTransactionType() const {
	return transactionType;
}

// return the first name
string Transaction::getFirstName() const {
	return firstName;
}

// return the last name
string Transaction::getLastName() const {
	return lastName;
}

// return the account ID
int Transaction::getAccountID() const {
	return accountID;
}

// return the Fund ID
int Transaction::getFundID() const {
	return fundID;
}

// return the transfer Account ID
int Transaction::getTransferAccountID() const {
	return transferAccountID;
}

// return the transfer Fund ID
int Transaction::getTransferFundID() const {
	return transferFundID;
}

// return the amount
int Transaction::getAmount() const {
	return amount;
}
