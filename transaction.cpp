/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Transaction Class
*/
#include "transaction.h"
#include <string>

Transaction::Transaction() {
	name_ = "";
	trans_type_ = "";
	fund_num_ = -1;
	account_num_ = 0;
	trans_amount_ = 0;
	account_other_ = 0;
	fund_other_ = -1;
	passed_ = false;
}

Transaction::Transaction(const string& name, const string& transaction_type, const int& fund_number, const int& account_number, const int& amount) {
	name_ = name;
	trans_type_ = transaction_type;
	fund_num_ = fund_number;
	account_num_ = account_number;
	trans_amount_ = amount;
	account_other_ = 0;
	fund_other_ = -1;
	passed_ = false;
}

Transaction::Transaction(const int& account_number, const int& account_other, const int& amount, const int& fund_number, const int& fund_other, const string& transaction_type) {
	name_ = "";
	trans_type_ = transaction_type;
	fund_num_ = fund_number;
	account_num_ = account_number;
	trans_amount_ = amount;
	account_other_ = account_other;
	fund_other_ = fund_other;
	passed_ = false;
}

string Transaction::GetTransType() const {
	return trans_type_;
}

void Transaction::SetTransType(const string& transaction_type) {
	trans_type_ = transaction_type;
}

int Transaction::GetFundNum() const {
	return fund_num_;
}

void Transaction::SetFundNum(const int& fund_number) {
	fund_num_ = fund_number;
}

int Transaction::GetAccountNum() const {
	return account_num_;
}

void Transaction::SetAccountNum(const int& account_number) {
	account_num_ = account_number;
}

int Transaction::GetTransAmount() const {
	return trans_amount_;
}

void Transaction::SetTransAmount(const int& transaction_amount) {
	trans_amount_ = transaction_amount;
}

void Transaction::SetName(const string& name) {
	name_ = name;
}

string Transaction::GetName() const {
	return name_;
}

void Transaction::SetPassed(const bool& passed) {
	passed_ = passed;
}

bool Transaction::GetPassed() const {
	return passed_;
}

int Transaction::GetFundOther() const {
	return fund_other_;
}

void Transaction::SetFundOther(const int& fund_other) {
	fund_other_ = fund_other;
}

int Transaction::GetAccountOther() const {
	return account_other_;
}

void Transaction::SetAccountOther(const int& account_other) {
	account_other_ = account_other;
}

ostream& operator<<(ostream& out, const Transaction& obj) {
	out << "Name: " << obj.GetName() << "Account Number: " << obj.GetAccountNum() << endl;
	return out;
}

// Reads in the stream and based on transaction type it returns a transaction object
istream& operator>>(istream& in, Transaction& trans) {
	string trans_type;
	string fName;
	string lName;
	int account_num;
	int amount;
	int account_other;
	int fund_num;
	int fund_other;
	in >> trans_type;
	if (trans_type == "O") {
		in >> lName >> fName >> account_num;
		string name = fName + " " + lName;
		trans = Transaction(name, trans_type, -1, account_num, 0);
	}
	else if (trans_type == "D" || trans_type == "W") {
		in >> account_num >> amount;
		if (account_num > 9999 || account_num < -9999) {
			fund_num = (int)(account_num % 10);
			account_num = (int)(account_num / 10);
		}
		else {
			fund_num = -1;
			account_num = (int)(account_num / 10);
		}
		trans = Transaction(" ", trans_type, fund_num, account_num, amount);
	}
	else if (trans_type == "T") {
		in >> account_num >> amount >> account_other;
		if ((account_num > 9999 || account_num < -9999) && (account_other > 9999 || account_other < -9999)) {
			fund_num = (int)(account_num % 10);
			account_num = (int)(account_num / 10);
			fund_other = (int)(account_other % 10);
			account_other = (int)(account_other / 10);
		}
		else {
			fund_num = -1;
			account_num = (int)(account_num / 10);
			fund_other = -1;
			account_other = (int)(account_other / 10);
		}
		trans = Transaction(account_num, account_other, amount, fund_num, fund_other, trans_type);
	}
	else if (trans_type == "H") {
		in >> account_num;
		if (to_string(account_num).length() == 5) {
			fund_num = (int)(account_num % 10);
			account_num = (int)(account_num / 10);
		}
		else {
			fund_num = -1;
		}
		trans = Transaction(" ", trans_type, fund_num, account_num, 0);
	}
	else {

	}
	return in;
}