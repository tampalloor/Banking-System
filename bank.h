/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Bank Class
*/
#ifndef BANK_H_
#define BANK_H_
#include "binary_search_tree.h"
#include <queue>
class Bank {
public:
	void Enqueue(const string& file_name);
	void Execute();

	//operator overload
	friend ostream& operator<<(ostream& out, const Bank& obj);

private:
	// Instance Variables
	BSTree accounts_;
	queue<Transaction> transactions_;
	// Private functions
	bool Open(const Transaction& trans);
	bool Deposit(Transaction& trans);
	bool Withdraw(Transaction& trans);
	bool Transfer(Transaction& trans);
	bool History(const Transaction& trans, const bool& show_summary) const;
	// Checkers
	bool CheckInfoOne(const int& account_num, const int& fund_num, const string& name, const string& trans_type) const;
	bool CheckInfoTwo(const int& account_num, const string& name, const string& trans_type) const;
	bool CheckInfoThree(const int& account_num, const int& fund_num, const int& amount, const string& trans_type) const;
};
#endif
