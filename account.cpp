//
//
// created by Marci Ma on 11/29/2019
//
//

#include "account.h"
#include "transaction.h"
#include "fund.h"
#include <iostream>
#include <string>


ostream& operator<<(ostream& out, Account& account){
	out << account.getFirstName() << " " << account.getLastName() <<
		" ID: " << account.getAccountID() << endl;
	for (int I = 0; I < 10; ++I){
		out << " " << account.getFundName(I) << " :$" << account.getBalance(I) << endl;
	}
	return out;
}

// constructor
Account::Account(string firstName, string lastName, int accountID) : 
	firstName{ firstName }, lastName{ lastName }, accountID{accountID} {
	string fundNames[] = { "Money Market", "Prime Money Market","Long-Term Bond",
		"Short-Term Bond","500 Index Fund", "Capital Value Fund",
		"Growth Equity Fund", "Growth Index Fund","Value Fund", "Value Stock Index" };
	for (int I = 0; I < 10; ++I){
		arrayFund[I].setName(fundNames[I]);
	}
}

// destrcutor
Account::~Account(){
}

// return the account ID
int Account::getAccountID() const{
	return accountID;
}

// set the fund ID
void Account::setFundID(int fundID) {
	this->fundID = fundID;
}


// return the balance in the account
int Account::getBalance(int fundID)const {
	return arrayFund[fundID].getBalance();
}

// return the fund titile
string Account::getFundName(int fundID) {
	return arrayFund[fundID].getName();
}

// return the first name
string Account::getFirstName() const {
	return firstName;
}

// return the last name
string Account::getLastName() const {
	return lastName;
}

// add amount to the account (deposit)
void Account::addToAccount(int fundID, int amount){
	arrayFund[fundID].deposit(amount);
}

// withdraw with relative account
//The WidthFromSimilarAcct() function is used during the widthdrawl of two linked accounts.  
void Account::widthFromSimilarAcct(int pFund, int sFund, int amount){
	if (((arrayFund[pFund].getBalance() + arrayFund[sFund].getBalance()) >= amount)){
		int balAvailable = arrayFund[pFund].getBalance();
		arrayFund[pFund].withdraw(balAvailable);
		Transaction addToHistory('W',"","","", getAccountID(), pFund, 0, 0, balAvailable);
		arrayFund[pFund].recordTransaction(addToHistory);
		amount = amount - balAvailable;
		arrayFund[sFund].withdraw(amount);
		Transaction addToHistory2('W', "", "", "", getAccountID(), sFund, 0, 0, amount);
		arrayFund[sFund].recordTransaction(addToHistory2);
	}
	else{
		int balAvailable = arrayFund[pFund].getBalance();
		if (balAvailable > amount){
			arrayFund[pFund].withdraw(balAvailable);
			Transaction addToHistory('W', "", "", "", getAccountID(), pFund, 0, 0, balAvailable);
			arrayFund[pFund].recordTransaction(addToHistory);
			amount = amount - balAvailable;
		}

		if (arrayFund[sFund].balanceCheck(amount)){
			arrayFund[sFund].withdraw(amount);//Take from other Account
			Transaction addToHistory('W', "", "", "", getAccountID(), sFund, 0, 0, amount);
			arrayFund[sFund].recordTransaction(addToHistory);
		}
		else{
			cerr << "ERROR: Not Enought Funds to withdraw " << amount << " " << "from " << getFirstName() << 
				" " << getLastName() << " " << getFundName(sFund) << endl;
			Transaction addToHistory('W',"","","Failed",getAccountID(), sFund, 0, 0, amount);
			arrayFund[sFund].recordTransaction(addToHistory);
		}
	}
}

// take amount from the account (withdraw)
bool Account::minusFunds(int fundID, int amount, Transaction frontTrans){
	if (fundID == 0 || fundID == 1 || fundID == 2 || fundID == 3){
		if (fundID == 0 || fundID == 1){
			if (arrayFund[fundID].balanceCheck(amount)){
				arrayFund[fundID].withdraw(amount);
				arrayFund[fundID].recordTransaction(frontTrans);
				return true;
			}
			else if (((arrayFund[0].getBalance() + arrayFund[1].getBalance()) >= amount)){
				if (fundID == 0){
					widthFromSimilarAcct(0, 1, amount);
				}
				else{
					widthFromSimilarAcct(1, 0, amount);
				}
				return true;
			}
			else{
				error(amount, getFirstName(), getLastName(), fundID);
				if (fundID == 1){
					widthFromSimilarAcct(0, 1, amount);
				}
				else{
					widthFromSimilarAcct(1, 0, amount);
				}
				return false;
			}
		}
		else if (fundID == 2 || fundID == 3){
			if (arrayFund[fundID].balanceCheck(amount)){
				arrayFund[fundID].withdraw(amount);
				arrayFund[fundID].recordTransaction(frontTrans);
				return true;
			}
			else if (((arrayFund[2].getBalance() + arrayFund[3].getBalance()) >= amount)){
				if (fundID == 2){
					widthFromSimilarAcct(2, 3, amount);
				}
				else{
					widthFromSimilarAcct(3, 2, amount);
				}
				return true;
			}
			else{
				error(amount, getFirstName(), getLastName(), fundID);
				if (fundID == 2){
					widthFromSimilarAcct(2, 3, amount);
				}
				else{
					widthFromSimilarAcct(3, 2, amount);
				}
				return false;
			}
		}
		return true;
	}
	else{
		if (arrayFund[fundID].balanceCheck(amount)){
			arrayFund[fundID].withdraw(amount);
			arrayFund[fundID].recordTransaction(frontTrans);
			return true;
		}
		else{
			error(amount, getFirstName(), getLastName(), fundID);
			return false;
		}
	}
}

// show the error messege
void Account::error(int amount, string firstName, string lastName, int fundID){
	cerr << "ERROR: Not Enought Funds to withdraw " << amount << " " << "from " 
		<< firstName << " " << lastName << " " << getFundName(fundID) << endl;
	//create transactoin to record
	Transaction addToHistory('W', "","", "Failed", getAccountID(), fundID, 0, 0, amount);
	//add to history
	arrayFund[fundID].recordTransaction(addToHistory);
}

// record the transaction
void Account::recordTrans(Transaction trans, int fundID){
	arrayFund[fundID].recordTransaction(trans);
}

// print account history
void Account::printHistory(){
	cout << "Transaction History for " << firstName << " " << lastName << " " << "By Fund." << endl;
	for (int I = 0; I < 10; ++I)
		arrayFund[I].printHistory();
}

// print the specific fund history
void Account::printFundHistory(int fundID){
	cout << "Transaction History for " << firstName << " " 
		<< lastName << " " << getFundName(fundID) << " $" << getBalance(fundID) << endl;
	arrayFund[fundID].printHistoryOfFund();
}


