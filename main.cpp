
#include "bank.h"
#include <iostream>
#include <string>


using namespace std;

int main() {
    Bank Bank;
    Bank.readTransaction("BankTransIn.txt");
	Bank.processTransactions();
	Bank.displayAllBankBalances();
    cout << "Done" << endl;
    return 0;
}