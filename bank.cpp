/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Bank Class
*/
#include "bank.h"
#include <fstream>

//Reads from input file, then puts in a queue
void Bank::Enqueue(const string& file_name) {
	ifstream in_file;
	in_file.open(file_name);
	if (in_file.is_open()) {
		while (!in_file.eof()) { 
			string line; 
			Transaction temp;
			getline(in_file, line);
			string trans_type = line.substr(0, 1);
			line = line.substr(2);
			string account_id_string = line.substr(0, 4);
			int account_id = stoi(account_id_string);
			temp.SetTransType(trans_type);
			temp.SetAccountNum(account_id);

			if (trans_type == "O") {
				string name = line.substr(5);
				string last_name;
				string first_name;
				int count = 0; 
				while (count < name.length()-1) {
					if (name.at(count) == ' ') {
						last_name = name.substr(0, count);
						first_name = name.substr(count + 1);
						break;
					}
					else {
						count++;
					}
				}
				name = first_name + " " + last_name;
				temp.SetName(name);
				transactions_.push(temp);
			}
			else if (trans_type == "D") {
				line = line.substr(5);
				string fund_string = line.substr(0, 1);
				int fund_num = stoi(fund_string);
				line = line.substr(2);
				int amount = stoi(line);
				temp.SetFundNum(fund_num);
				temp.SetTransAmount(amount);
				transactions_.push(temp);
			}
			else if (trans_type == "W") {
				line = line.substr(5);
				string fund_string = line.substr(0, 1);
				int fund_num = stoi(fund_string);
				line = line.substr(2);
				int amount = stoi(line);
				temp.SetFundNum(fund_num);
				temp.SetTransAmount(amount);
				transactions_.push(temp);
			}
			else if (trans_type == "T") {
				line = line.substr(5);
				string fund_string = line.substr(0, 1);
				int fund_num = stoi(fund_string);
				line = line.substr(2);
				string account_other_id_string = line.substr(0, 4);
				line = line.substr(5);
				int account_other_id = stoi(account_other_id_string); 
				string fund_other_num_string = line.substr(0, 1);
				int fund_other_num = stoi(fund_other_num_string);
				line = line.substr(2);
				int amount = stoi(line);
				temp.SetFundNum(fund_num);
				temp.SetAccountOther(account_other_id);
				temp.SetFundOther(fund_other_num);
				temp.SetTransAmount(amount);
				transactions_.push(temp);
			}
			else if (trans_type == "A") {
				transactions_.push(temp);
			}
			else if (trans_type == "F") {
				line = line.substr(5);
				int fund_num = stoi(line);
				temp.SetFundNum(fund_num);
				transactions_.push(temp);
			}
			else {
				cerr << "ERROR: Invalid Transaction type. " << endl;
			}
		}
	}
}
//Checks if info of the transaction is valid
bool Bank::CheckInfoOne(const int& account_num, const int& fund_num, const string& name, const string& trans_type) const {
	if (account_num < 0 || account_num > 9999) {
		cout << "reached1" << endl;
		cerr << "ERROR Account num: " << account_num << " is invalid for transaction: " << trans_type << endl;
		return false;
	}
	if (fund_num < 0 || fund_num >9) {
		cerr << "ERROR: Fund num: " << fund_num << " is invalid for transaction: " << trans_type << " and account: " << account_num << endl;
		return false;
	}
	if (name.empty()) {
		cerr << "ERROR: Name cannot be empty for transaction: " << trans_type << endl;
		return false;
	}
	return true;
}

bool Bank::CheckInfoTwo(const int& account_num, const string& name, const string& trans_type) const {
	if (account_num < 0 || account_num > 9999) {
		cout << "reached2" << endl;

		cerr << "ERROR Account num: " << account_num << " is invalid for transaction: " << trans_type << endl;
		return false;
	}
	if (name.empty()) {
		cerr << "ERROR: Name cannot be empty for transaction: " << trans_type << endl;
		return false;
	}
	return true;
}
bool Bank::CheckInfoThree(const int& account_num, const int& fund_num, const int& amount, const string& trans_type) const {
	if (account_num < 0 || account_num > 9999) {
		cout << "reached3" << endl;
		cerr << "ERROR Account num: " << account_num << " is invalid for transaction: " << trans_type << endl;

		return false;
	}
	if (fund_num < 0 || fund_num >9) {
		cerr << "ERROR: Fund num: " << fund_num << " is invalid for transaction: " << trans_type << " and account: " << account_num << endl;
		return false;
	}
	if (amount < 0) {
		cerr << "ERROR: Invalid amount of : " << amount << " for account: " << account_num << endl;
		return false;
	}
	return true;
}

//Reading the queue, and checks the transaction type
void Bank::Execute() {
	while (!transactions_.empty()) {
		Transaction trans = transactions_.front();
		if (trans.GetTransType() == "O") {
			Open(trans);
		}
		else if (trans.GetTransType() == "D") {
			Deposit(trans);
		}
		else if (trans.GetTransType() == "W") {
			Withdraw(trans);
		}
		else if (trans.GetTransType() == "T") {
			Transfer(trans);
		}
		else if (trans.GetTransType() == "A") {
			History(trans, false);

		}
		else if (trans.GetTransType() == "F") {
			History(trans, false);

		}
		transactions_.pop();
	}
}

//Opens account
bool Bank::Open(const Transaction& trans) {
	// checks if information of the transaction is valid
	if (CheckInfoTwo(trans.GetAccountNum(), trans.GetName(), trans.GetTransType())) {
		Account temp(trans.GetName(), trans.GetAccountNum());
		// Inserts into the BST (false = duplicate) 
		if (accounts_.Insert(&temp) == false) {
			cerr << "ERROR: Account number: " << trans.GetAccountNum() << " is already open. Transaction refused." << endl;
			return false;
		}
		return true;
	}
	return false;
}

//Deposits into a fund
bool Bank::Deposit(Transaction& trans) {
	// Checks if info is valid
	if (CheckInfoThree(trans.GetAccountNum(), trans.GetFundNum(), trans.GetTransAmount(), trans.GetTransType())) {
		Account* temp;
		// calls the retrieve function is BST if it returns false it means that the account number passed in doesn't exist
		if (accounts_.Retrieve(trans.GetAccountNum(), temp) == false) {
			cerr << "ERROR: Account number:" << trans.GetAccountNum() << "depositing to doesn't exist " << trans.GetAccountNum() << endl;
			return false;
		}
		if (temp->SetAmount(trans.GetFundNum(), trans.GetTransAmount()) == false) {
			cerr << "ERROR: fund number:" << trans.GetFundNum() << " doesn't exist" << endl;
			return false;
		}
		Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
		trans.SetPassed(true);
		temp_fund->RecordTransaction(trans);
		return true;
	}
	return false;
}

//Withdraws from an account
bool Bank::Withdraw(Transaction& trans) {
	// Checks if info is valid
	if (CheckInfoThree(trans.GetAccountNum(), trans.GetFundNum(), trans.GetTransAmount(), trans.GetTransType())) {
		Account* temp;
		// Checks if account number exists
		if (accounts_.Retrieve(trans.GetAccountNum(), temp) == false) {
			cerr << "ERROR: Account:" << trans.GetAccountNum() << "withdrawing to doesn't exist " << endl;
			return false;
		}
		// Checks if fund is 0 or 2 based on that it does the calculations with its paired fund
		if (trans.GetFundNum() == 0 || trans.GetFundNum() == 2) {
			int amount_returned;
			int amount_second;
			if (temp->GetAmount(trans.GetFundNum(), amount_returned) && amount_returned >= trans.GetTransAmount()) {
				temp->SetAmount(trans.GetFundNum(), -1 * trans.GetTransAmount());
				Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
				trans.SetPassed(true);
				temp_fund->RecordTransaction(trans);
				return true;
			}
			if (temp->GetAmount(trans.GetFundNum(), amount_returned) && temp->GetAmount(trans.GetFundNum() + 1, amount_second) && amount_returned + amount_second >= trans.GetTransAmount()) {
				int current_bal = trans.GetTransAmount();
				int temp_bal;
				temp->GetAmount(trans.GetFundNum(), temp_bal);
				current_bal -= temp_bal;
				temp->SetAmount(trans.GetFundNum(), -1 * temp_bal);
				temp->SetAmount(trans.GetFundNum() + 1, -1 * current_bal);
				Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
				Fund* temp_fund_two = temp->fundBalance(trans.GetFundNum() + 1);
				Transaction temp_trans(trans.GetName(), trans.GetTransType(), trans.GetFundNum(), trans.GetAccountNum(), temp_bal);
				Transaction temp_trans_two(trans.GetName(), trans.GetTransType(), trans.GetFundNum() + 1, trans.GetAccountNum(), current_bal);
				temp_trans.SetPassed(true);
				temp_trans_two.SetPassed(true);
				temp_fund->RecordTransaction(temp_trans);
				temp_fund_two->RecordTransaction(temp_trans_two);
				return true;
			}
			cerr << "ERROR: Not enough funds to withdraw " << trans.GetTransAmount()
				<< " from account: " << temp->name() << " " << kFunds[trans.GetFundNum()] << endl;
			Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
			trans.SetPassed(false);
			temp_fund->RecordTransaction(trans);
			return false;
		}
		// Checks if fund is 1 or 3 and does calculations with it's paired fund
		if (trans.GetFundNum() == 1 || trans.GetFundNum() == 3) {
			int amount_returned;
			int amount_second;
			if (temp->GetAmount(trans.GetFundNum(), amount_returned) && amount_returned >= trans.GetTransAmount()) {
				temp->SetAmount(trans.GetFundNum(), -1 * trans.GetTransAmount());
				Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
				trans.SetPassed(true);
				temp_fund->RecordTransaction(trans);
				return true;
			}
			if (temp->GetAmount(trans.GetFundNum(), amount_returned) && temp->GetAmount(trans.GetFundNum() - 1, amount_second) && amount_returned + amount_second >= trans.GetTransAmount()) {
				int current_bal = trans.GetTransAmount();
				int temp_bal;
				temp->GetAmount(trans.GetFundNum(), temp_bal);
				current_bal -= temp_bal;
				temp->SetAmount(trans.GetFundNum(), -1 * temp_bal);
				temp->SetAmount(trans.GetFundNum() - 1, -1 * current_bal);
				Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
				Fund* temp_fund_two = temp->fundBalance(trans.GetFundNum() - 1);
				Transaction temp_trans(trans.GetName(), trans.GetTransType(), trans.GetFundNum(), trans.GetAccountNum(), temp_bal);
				Transaction temp_trans_two(trans.GetName(), trans.GetTransType(), trans.GetFundNum() - 1, trans.GetAccountNum(), current_bal);
				temp_trans.SetPassed(true);
				temp_trans_two.SetPassed(true);
				temp_fund->RecordTransaction(temp_trans);
				temp_fund_two->RecordTransaction(temp_trans_two);
				return true;
			}
			cerr << "ERROR: Not enough funds to withdraw " << trans.GetTransAmount()
				<< " from account: " << temp->name() << " " << kFunds[trans.GetFundNum()] << endl;
			Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
			trans.SetPassed(false);
			temp_fund->RecordTransaction(trans);
			return false;
		}
		// If the fund is not paired it just does it regularly
		int amount_returned;
		if (temp->GetAmount(trans.GetFundNum(), amount_returned) && amount_returned >= trans.GetTransAmount()) {
			temp->SetAmount(trans.GetFundNum(), -1 * trans.GetTransAmount());
			Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
			trans.SetPassed(true);
			temp_fund->RecordTransaction(trans);
			return true;
		}
		cerr << "ERROR: Not enough funds to withdraw " << trans.GetTransAmount()
			<< " from account: " << temp->name() << " " << kFunds[trans.GetFundNum()] << endl;
		Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
		trans.SetPassed(false);
		temp_fund->RecordTransaction(trans);
		return false;
	}
	return false;
}

// Transfers money
bool Bank::Transfer(Transaction& trans) {
	// Checks if information is valid
	if (CheckInfoThree(trans.GetAccountNum(), trans.GetFundNum(), trans.GetTransAmount(), trans.GetTransType()) && CheckInfoThree(trans.GetAccountOther(), trans.GetFundOther(), trans.GetTransAmount(), trans.GetTransType())) {
		Account* temp;
		Account* temp_to;
		// Checks if account number exists
		if (accounts_.Retrieve(trans.GetAccountNum(), temp) == false) {
			cerr << "ERROR: Account " << trans.GetAccountNum() << " transferring from doesn't exist " << endl;
			return false;
		}
		if (accounts_.Retrieve(trans.GetAccountOther(), temp_to) == false) {
			cerr << "ERROR: Account " << trans.GetAccountOther() << " transferring from doesn't exist " << endl;
			return false;
		}
		int amount, amount_linked;
		temp->GetAmount(trans.GetFundNum(), amount);
		temp->GetAmount(trans.GetFundNum() + 1, amount_linked);
		// If not enough in the main fund
		if (amount < trans.GetTransAmount()) {
			// Checks if linked has money to cover the transfer if not enough then print error else
			if (amount + amount_linked < trans.GetTransAmount()) {
				cerr << "ERROR: Not Enough funds to transfer " << trans.GetTransAmount() <<
					" from " << temp->name() << " to " << temp_to->name() << endl;
				trans.SetPassed(false);
				Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
				temp_fund->RecordTransaction(trans);
				return false;
			}
			if (trans.GetFundNum() == 0 || trans.GetFundNum() == 2) {
				temp->SetAmount(trans.GetFundNum(), -1 * amount);
				Transaction temp_trans = Transaction(" ", "W", trans.GetFundNum() + 1, trans.GetAccountNum(), trans.GetTransAmount() - amount);
				// Calls withdraw on the paired account
				Withdraw(temp_trans);
				temp_to->SetAmount(trans.GetFundOther(), trans.GetTransAmount());
				trans.SetPassed(true);
				Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
				Fund* temp_other = temp->fundBalance(trans.GetFundOther());
				temp_fund->RecordTransaction(trans);
				temp_other->RecordTransaction(trans);
				return true;
			}
			if (trans.GetFundNum() == 1 || trans.GetFundNum() == 3) {
				temp->SetAmount(trans.GetFundNum(), -1 * amount);
				Transaction temp_trans = Transaction(" ", "W", trans.GetFundNum() - 1, trans.GetAccountNum(), trans.GetTransAmount() - amount);
				// calls withdraw on the paired account
				Withdraw(temp_trans);
				temp_to->SetAmount(trans.GetFundOther(), trans.GetTransAmount());
				trans.SetPassed(true);
				Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
				Fund* temp_other = temp->fundBalance(trans.GetFundOther());
				temp_fund->RecordTransaction(trans);
				temp_other->RecordTransaction(trans);
				return true;
			}
		}
		temp->SetAmount(trans.GetFundNum(), -1 * trans.GetTransAmount());
		temp_to->SetAmount(trans.GetFundOther(), trans.GetTransAmount());
		trans.SetPassed(true);
		Fund* temp_fund = temp->fundBalance(trans.GetFundNum());
		Fund* temp_other = temp->fundBalance(trans.GetFundOther());
		temp_fund->RecordTransaction(trans);
		temp_other->RecordTransaction(trans);
		return true;
	}
	return false;
}

// Prints history
bool Bank::History(const Transaction& trans, const bool& show_summary) const {
	if (CheckInfoThree(trans.GetAccountNum(), 0, 0, trans.GetTransType())) {
		Account* temp;
		if (accounts_.Retrieve(trans.GetAccountNum(), temp) == false) {
			cerr << "ERROR: Account to show history doesn't exist " << endl;
			return false;
		}
		// Fund is -1 if the history transaction doesn't require a specific fund
		if (trans.GetFundNum() == -1) { //TODO: THIS WOULD BE FOR A
			return temp->PrintHistory(show_summary);
		}
		cout << endl;
		return temp->PrintHistory(trans.GetFundNum(), show_summary); //F
	}
	return false;
}

ostream& operator<<(ostream& out, const Bank& obj) {
	obj.accounts_.Display();
	return out;
}