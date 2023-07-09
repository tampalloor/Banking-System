/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Fund Class
*/
#ifndef FUND_H_
#define FUND_H_
#include <iostream>
#include <vector>
#include "transaction.h"
using namespace std;
//all funds
const static string kFunds[10] = { "Money Market","Prime Money Market","Long-Term Bond","Short-Term Bond","500 Index Fund","Capital Value Fund","Growth Equity Fund","Growth Index Fund"};
class Fund {
public:
	// constructors
	Fund();
	Fund(const int& balance, const int& current_fund);


	// Modification functions
	bool AddAmount(const int& amount);
	bool RecordTransaction(const Transaction& transaction);
	//Getters
	string currentFund(const int& fund_number);
	int balance() const;
	bool history(const bool& show_summary) const;
private:
	int current_fund_;
	int balance_;
	vector<Transaction> history_;
};
#endif
