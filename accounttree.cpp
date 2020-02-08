//
//
// created by Marci Ma on 11/29/2019
//
//

#include "accounttree.h"


AccountTree::AccountTree() = default;

// Delete all nodes in BST
AccountTree::~AccountTree() = default;

// Insert new account
bool AccountTree::insert(Account *Account) {
	int insertAccountID = Account->getAccountID();
	if (insertAccountID < 1000 || insertAccountID > 9999){
		cerr << "ERROR: Account Number Not Valid" << endl;
		return false;
	}

	if (Root == NULL){
		Root = new Node(Account);
		return true;
	}
	else
	{
		Node* current = Root;
		recursiveInsert(current, Account);
	}
	return false;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *Acc) const {
	Node* Curr = Root;
	bool Search = false;

	while (!Search){
		if (Curr != NULL && AccountNumber == Curr->Account->getAccountID()){
			Search = true;
			Acc = Curr->Account;
			return Search;
		}
		else if (Curr != NULL && AccountNumber > Curr->Account->getAccountID()){
			Curr = Curr->Right;
		}
		else if (Curr != NULL && AccountNumber < Curr->Account->getAccountID()){
			Curr = Curr->Left;
		}
		else{
			Search = true;
		}
	}
	cerr << "ERROR: Account Number " << AccountNumber << " Cannot Be Found" << endl;
	return false;
}

// Display information on all accounts
void AccountTree::display() const {
	if (Root == NULL)
		cerr << "ERROR: ACCOUNT LIST IS EMPTY" << endl;
	printTree(Root);
}

// delete all information in AccountTree
void AccountTree::clear() {
	delete Root;
	Root = NULL;
}

// check if tree is empty
bool AccountTree::isEmpty() const {
	return (Root->Left == NULL && Root->Right == NULL);
}

// helper function to print the whole tree
void AccountTree::printTree(Node* Curr) const {
	if (Curr->Right != NULL && Curr->Left != NULL){
		printTree(Curr->Right);
		cout << *(Curr->Account) << endl;
		printTree(Curr->Left);
	}
	else if (Curr->Left != NULL){
		cout << *(Curr->Account) << endl;
		printTree(Curr->Left);
	}
	else if (Curr->Right != NULL){
		cout << *(Curr->Account) << endl;
		printTree(Curr->Right);
	}
	else{
		cout << *(Curr->Account) << endl;
	}
}

// keep insert
bool AccountTree::recursiveInsert(Node* Curr, Account* Acc){
	if (Acc->getAccountID() > Curr->Account->getAccountID()){
		if (Curr->Right == NULL){
			Node* inTree = new Node(Acc);
			Curr->Right = inTree;
			return true;
		}
		else{
			return recursiveInsert(Curr->Right, Acc);
		}

	}
	else if(Acc->getAccountID() < Curr->Account->getAccountID()){
		if (Curr->Left == NULL){
			Node* inTree = new Node(Acc);
			Curr->Left = inTree;
			return true;
		}
		else{
			return recursiveInsert(Curr->Left,Acc);
		}
	}
	else{
		cerr << "ERROR: Account " << Acc->getAccountID()
			<< " is already open. Transaction refused." << endl;
		return false;
	}
}