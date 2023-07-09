/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Account Class
*/
#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <string>
#include <iostream>
#include "transaction.h"
#include <vector>

#include "fund.h"
using namespace std;
const int kMoneyMarket = 0;
const int kPrimeMoneyMarket = 1;
const int kLongTermBond = 2;
const int kShortTermBond = 3;
class Account {
public:
	// Constructors
	Account();
	Account(const string& name, const int& account_number);
	Account(const Account& other);

	// Getters and Setters
	void SetName(const string& name);
	void SetAccountId(const int& account_number);
	bool SetAmount(const int& fund_number, const int& amount);
	string name() const;
	int accountId() const;

	//histories
	bool PrintHistory(const bool& show_summary) const;
	bool PrintHistory(const int& fund_number, const bool& show_summary) const;
	bool GetAmount(const int& fund_number, int& amount) const;
	Fund* fundBalance(const int& fund_number);

	//opator overloads
	bool operator<(const Account& rhs) const;
	bool operator<=(const Account& rhs) const;
	bool operator>(const Account& rhs) const;
	bool operator>=(const Account& rhs) const;
	bool operator==(const Account& rhs) const;
	friend ostream& operator<<(ostream& out, const Account& obj);
private:
	//instance variables
	string name_;
	int account_id_;
	vector<Fund> fund_balance_[10];
};
#endif