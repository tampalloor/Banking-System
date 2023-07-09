/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Driver -> main()
*/
#include "bank.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	Bank JollyBanker;
	string textFile = argv[1]; //command line
	JollyBanker.Enqueue(textFile);
	JollyBanker.Execute();
	cout << "FINAL BALANCES:" << endl;
	cout << JollyBanker << endl;
	return 0;
}