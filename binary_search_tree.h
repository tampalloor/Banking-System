/**
* Thomas Ampalloor
* CSS342 Program 5
* 
* Binary Search Tree Class
*/
#ifndef BS_TREE_H_
#define BS_TREE_H_
#include "account.h"
class BSTree {
public:
	BSTree();
	~BSTree();
	bool Insert(Account* other);
	bool Retrieve(const int& account_id, Account*& account_ret) const;

	// displays tree
	void Display() const;
	void Empty();
	bool isEmpty() const;

	bool Delete(const int& account_id, Account*& account); 
	BSTree& operator=(const BSTree& tree);
private:
	struct Node
	{
		Account* pAcct;
		Node* right;
		Node* left;
	};
	Node* root_;
	// all helpers
	bool InsertHelpers(Account* other, Node*& curr_root);
	bool RetrieveHelper(const int& account_id, Account*& account_ret, Node* curr_root) const;
	void DisplayHelper(Node* root_node) const;
	void EmptyHelper(Node* curr_root);
	bool DeleteHelper(const int& account_id, Account*& account, Node* current_root);
	Node* RightRootLeftNode(Node* current_node);
	Node* LeftRootRightNode(Node* current_node);
	void AssignmentOperatorHelper(Node* current_node); 
};
#endif
