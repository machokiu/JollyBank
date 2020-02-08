//
//
// created by Marci Ma on 11/29/2019
//
//

#include "bank.h"
#include <queue>
#include "accounttree.h"
#include "transaction.h"
#include "fund.h"
#include "account.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// default constructor
Bank::Bank() = default;

// destructor
Bank::~Bank() = default;

// read the file and create the transaction
// and then store the info into the queue
bool Bank::readTransaction(const string & FileName) {
	ifstream in(FileName);
	string readLine;
	if (!in) {
		cout << "Cannot Open!" << endl;
	}
	while (!in.eof()) {
		getline(in, readLine);
		if (readLine.empty()) {
			break;
		}
		istringstream parseLine(readLine);
		char transactionType;
		parseLine >> transactionType;
		if (transactionType == 'O') {
			string lastName, firstName;
			int accountID;
			parseLine >> firstName >> lastName >> accountID;
			Transaction addToQueue(transactionType, firstName, lastName, "", accountID, 0, 0, 0, 0);
			transactionQueue.push(addToQueue);
		}
		else if (transactionType == 'W' || transactionType == 'D') {
			int accountID, fundID, amount;
			parseLine >> accountID >> amount;
			fundID = accountID % 10;
			accountID = accountID / 10;
			Transaction addToQueue(transactionType, "", "", "", accountID, fundID, 0, 0, amount);
			transactionQueue.push(addToQueue);
		}
		else if (transactionType == 'T') {
			int accountID, fundID, amount, trasnferAccountID, transferFundID;
			parseLine >> accountID >> amount >> trasnferAccountID;
			fundID = accountID % 10;
			accountID = accountID / 10;
			transferFundID = trasnferAccountID % 10;
			trasnferAccountID = trasnferAccountID / 10;
			Transaction addToQueue(transactionType, "", "", "", accountID, 
				fundID, trasnferAccountID, transferFundID, amount);
			transactionQueue.push(addToQueue);
		}
		else if (transactionType == 'H') {
			int accountID;
			parseLine >> accountID;
			Transaction addToQueue(transactionType, "", "", "", accountID, 0, 0, 0, 0);
			transactionQueue.push(addToQueue);
		}
		else {
			cout << "ERROR!" << endl;
		}
	}
	return false;
}

// pop off transaction from the queue
// get the transaction type and then find the according accounttree pointer
// process the transaction
void Bank::processTransactions() {
	while (!transactionQueue.empty()){
		Transaction frontTrans = transactionQueue.front();
		if (frontTrans.getTransactionType() == 'O'){
			Account* account = new Account(frontTrans.getFirstName(), 
				frontTrans.getLastName(), frontTrans.getAccountID());
			Accounts.insert(account);
		}
		else if (frontTrans.getTransactionType() == 'D'){
			int accountID = frontTrans.getAccountID();
			int fundID = frontTrans.getFundID();
			int deposit = frontTrans.getAmount();
			Account* account;
			if (Accounts.retrieve(accountID, account)){
				account->addToAccount(fundID, deposit);
				account->recordTrans(frontTrans, fundID);
			}

		}
		else if (frontTrans.getTransactionType() == 'W'){
			int accountID = frontTrans.getAccountID();
			int fundID = frontTrans.getFundID();
			int withdraw = frontTrans.getAmount();
			Account* account;
			if (Accounts.retrieve(accountID, account))
				account->minusFunds(fundID, withdraw, frontTrans);
		}
		else if (frontTrans.getTransactionType() == 'T'){
			int accountID = frontTrans.getAccountID();
			int transferAcc = frontTrans.getTransferAccountID();
			int fundID = frontTrans.getFundID();
			int transferFund = frontTrans.getTransferFundID();
			int trans = frontTrans.getAmount();
			Account* To, * From;
			if (Accounts.retrieve(accountID, To) && Accounts.retrieve(transferAcc, From)){
				if (To->minusFunds(fundID, trans, frontTrans)){
					From->addToAccount(transferFund, trans);
					From->recordTrans(frontTrans, transferFund);
				}
				else{
					cerr << "ERROR: Not Enought Funds to Transer  " << trans
						<< " " << "from " << From->getAccountID() << 
						fundID << " to " << To->getAccountID() << transferFund << endl;
					Transaction addToHistory('T',"","", "(Failed)", accountID, 
						fundID, transferAcc, transferFund, trans);
					From->recordTrans(addToHistory, transferFund);
				}
			}

		}
		else if (frontTrans.getTransactionType() == 'H'){
			if (frontTrans.getAccountID() >= 10000 && frontTrans.getAccountID() <= 99999){
				Account* account;
				int fundNumPrt = frontTrans.getAccountID() % 10;
				int acctNumSearch = frontTrans.getAccountID() / 10;
				if (Accounts.retrieve(acctNumSearch, account)){
					account->printFundHistory(fundNumPrt);
					cout << endl;
				}
			}
			else if (frontTrans.getAccountID() >= 1000 && frontTrans.getAccountID() <= 9999){
				Account* account;
				int acctNumSearch = frontTrans.getAccountID();
				if (Accounts.retrieve(acctNumSearch, account)){
					account->printHistory();
					cout << endl;
				}
			}
		}
		transactionQueue.pop();
	}
}

// display all the balances
void Bank::displayAllBankBalances() const {
	cout << endl;
	cout << "Processing Done. Final Balances" << endl;
	Accounts.display();
}

