/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Fund Class
*/
#include "fund.h"

Fund::Fund() {
	current_fund_ = 0;
	balance_ = 0;
}

Fund::Fund(const int& balance, const int& current_fund) {
	balance_ = balance;
	current_fund_ = current_fund;
}

int Fund::balance() const {
	return balance_;
}

//Adding amount to the current balance
bool Fund::AddAmount(const int& amount) {
	balance_ += amount;
	return true;
}

bool Fund::RecordTransaction(const Transaction& transaction) {
	history_.push_back(transaction);
	return true;
}

/*
 * Prints history of the current fund(0-7) 
 */
bool Fund::history(const bool& show_summary) const {

	if (show_summary) {
		cout << "\t" << kFunds[current_fund_] << ": $" << balance_ << endl;
		return true;
	}
	// If history is empty, then it doesn't print
	if (history_.empty()) {
		return false;
	}
	cout << kFunds[current_fund_] << ": $" << balance_ << endl;
	for (int i = 0; i < history_.size(); ++i) {
		if (history_[i].GetTransType() == "T") {
			if (history_[i].GetPassed() == false) {
				cout << "\t" << history_[i].GetTransType() << " " << history_[i].GetAccountNum() << history_[i].GetFundNum() << " $" << history_[i].GetTransAmount() << " " << history_[i].GetAccountOther() << history_[i].GetFundOther() << "(failed)" << endl;
			}
			cout << "\t" << history_[i].GetTransType() << " " << history_[i].GetAccountNum() << history_[i].GetFundNum() << " $" << history_[i].GetTransAmount() << " " << history_[i].GetAccountOther() << history_[i].GetFundOther() << endl;
		}
		else if (history_[i].GetPassed()) {
			cout << "\t" << history_[i].GetTransType() << " " << history_[i].GetAccountNum() << history_[i].GetFundNum() << " $" << history_[i].GetTransAmount() << endl;
		}
		else {
			cout << "\t" << history_[i].GetTransType() << " " << history_[i].GetAccountNum() << history_[i].GetFundNum() << " $" << history_[i].GetTransAmount() << "(failed)" << endl;
		}
	}
	return true;
}

string Fund::currentFund(const int& fund_number) {
	return kFunds[fund_number];
}