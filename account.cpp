/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Account Class
*/
#include "account.h"
string Account::name() const {
	return name_;
}

Account::Account() {
	name_ = "";
	account_id_ = 0;
	for (int i = 0; i < 10; ++i) {
		fund_balance_[i].push_back(Fund(0, i));
	}
}

Account::Account(const string& name, const int& account_number) {
	name_ = name;
	account_id_ = account_number;
	for (int i = 0; i < 10; ++i) {
		fund_balance_[i].push_back(Fund(0, i));
	}
}

void Account::SetName(const string& name) {
	name_ = name;
}

int Account::accountId() const {
	return account_id_;
}

void Account::SetAccountId(const int& account_number) {
	account_id_ = account_number;
}

bool Account::SetAmount(const int& fund_number, const int& amount) {
	if (fund_number > 8) {
		return false;
	}
	fund_balance_[fund_number].data()->AddAmount(amount);
	return true;
}

Account::Account(const Account& other) {
	name_ = other.name_;
	account_id_ = other.account_id_;
	for (int i = 0; i < 10; ++i) {
		fund_balance_[i] = other.fund_balance_[i];
	}
}

bool Account::PrintHistory(const bool& show_summary) const {
	cout << name_ << " with account ID " << account_id_ << endl;
	for (int i = 0; i < 8; ++i) {
		fund_balance_[i].data()->history(show_summary);
	}
	return true;
}

bool Account::PrintHistory(const int& fund_number, const bool& show_summary) const {
	cout << "Fund History for: " << name_ << " " << kFunds[fund_number] << endl;
	return fund_balance_[fund_number].data()->history(show_summary);
}

bool Account::GetAmount(const int& fund_number, int& amount) const {
	if (fund_number > 8) {
		cerr << "ERROR: Fund number: " << fund_number << " is invalid" << endl;
		return false;
	}
	amount = fund_balance_[fund_number].data()->balance();
	return true;
}

Fund* Account::fundBalance(const int& fund_number) {
	return fund_balance_[fund_number].data();
}

bool Account::operator<(const Account& rhs) const {
	return account_id_ < rhs.account_id_;
}

bool Account::operator<=(const Account& rhs) const {
	return account_id_ <= rhs.account_id_;
}

bool Account::operator>(const Account& rhs) const {
	return !(*this <= rhs);
}

bool Account::operator>=(const Account& rhs) const {
	return !(*this < rhs);
}

bool Account::operator==(const Account& rhs) const {
	return account_id_ == rhs.account_id_;
}

ostream& operator<<(ostream& out, const Account& obj) {
	out << obj.name() << " " << obj.accountId() << endl;
	return out;
}