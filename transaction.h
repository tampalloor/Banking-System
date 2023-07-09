/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Transaction Class
*/
#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <iostream>
using namespace std;
class Transaction {
public:
	//constructors
	Transaction();
	Transaction(const string& name, const string& transaction_type, const int& fund_number, const int& account_number, const int& amount);
	Transaction(const int& account_number, const int& account_other, const int& amount, const int& fund_number, const int& fund_other, const string& transaction_type);

	//getters and setters
	string GetTransType() const;
	void SetTransType(const string& transaction_type);
	int GetFundNum() const;
	void SetFundNum(const int& fund_number);
	int GetAccountNum() const;
	void SetAccountNum(const int& account_number);
	int GetTransAmount() const;
	void SetTransAmount(const int& transaction_amount);
	void SetName(const string& name);
	string GetName()const;
	void SetPassed(const bool& passed);
	bool GetPassed() const;
	int GetFundOther() const;
	void SetFundOther(const int& fund_other);
	int GetAccountOther() const;
	void SetAccountOther(const int& account_other);

	//operator overloads
	friend ostream& operator<<(ostream& out, const Transaction& obj);
	friend istream& operator>>(istream& in, Transaction& trans);

private:
	//instance variables
	string name_;
	string trans_type_;
	int fund_num_;
	int fund_other_;
	int account_other_;
	int account_num_;
	int trans_amount_;
	bool passed_;
};

#endif
