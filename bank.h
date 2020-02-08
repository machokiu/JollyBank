//
//
// created by Marci Ma on 11/29/2019
//
//
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include <queue>
#include "accounttree.h"
#include "transaction.h"
#include "fund.h"
#include "account.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Bank {
public:
  // default constructor
  Bank();
  // destructor
  ~Bank();

  // read the file and create the transaction
  // and then store the info into the queue
  bool readTransaction(const string& FileName);

  // pop off transaction from the queue
  // get the transaction type and then find the according accounttree pointer
  // process the transaction
  void processTransactions();
  
  // display all the balances
  void displayAllBankBalances() const;

  

private:
  AccountTree Accounts;
  queue<Transaction> transactionQueue;
  
};
#endif // ASS5_BANK_H
