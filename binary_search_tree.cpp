/**
* Thomas Ampalloor
* CSS342 Program 5
*
* Binary Search Tree Class
*/
#include "binary_search_tree.h"

BSTree::BSTree() {
	root_ = nullptr;
}

BSTree::~BSTree() {
	Empty();
}

bool BSTree::Insert(Account* other) {
	return InsertHelpers(other, root_);
}

// Inserts a node (no duplicates)
bool BSTree::InsertHelpers(Account* other, Node*& curr_root) {
	if (curr_root == nullptr) {
		curr_root = new Node();
		curr_root->pAcct = new Account(*other);
		curr_root->left = nullptr;
		curr_root->right = nullptr;
		return true;
	}
	if (*curr_root->pAcct == *other) {
		return false;
	}
	if (*curr_root->pAcct > *other) {
		return  InsertHelpers(other, curr_root->left);
	}
	return InsertHelpers(other, curr_root->right);
}
bool BSTree::Retrieve(const int& account_id, Account*& account_ret) const {
	return RetrieveHelper(account_id, account_ret, root_);
}

// Retrieves node
bool BSTree::RetrieveHelper(const int& account_id, Account*& account_ret, Node* curr_root) const {
	if (curr_root == nullptr) {
		account_ret = nullptr;
		return false;
	}
	if (curr_root->pAcct->accountId() == account_id) {
		account_ret = curr_root->pAcct;
		return true;
	}

	if (curr_root->pAcct->accountId() > account_id) {
		return RetrieveHelper(account_id, account_ret, curr_root->left);
	}
	return RetrieveHelper(account_id, account_ret, curr_root->right);
}

void BSTree::Display() const {
	DisplayHelper(root_);
}
// Prints the tree
void BSTree::DisplayHelper(Node* root_node) const {
	if (root_node != nullptr) {
		DisplayHelper(root_node->left);
		root_node->pAcct->PrintHistory(true);
		DisplayHelper(root_node->right);
	}
}
void BSTree::Empty() {
	EmptyHelper(root_);
}
// Empties a tree
void BSTree::EmptyHelper(Node* curr_root) {
	if (curr_root == nullptr) {
		return;
	}
	EmptyHelper(curr_root->left);
	EmptyHelper(curr_root->right);
	delete curr_root->pAcct;
	curr_root->pAcct = nullptr;
	delete curr_root;
	curr_root = nullptr;
}


bool BSTree::isEmpty() const {
	return root_ == nullptr;
}

bool BSTree::Delete(const int& account_id, Account*& account)
{
	return DeleteHelper(account_id, account, root_);
}

bool BSTree::DeleteHelper(const int& account_id, Account*& account, Node* current_root)
{
	if (isEmpty()) {
		return false; 
	}
	if (current_root->pAcct->accountId() == account_id) {
		if (current_root->right == nullptr && current_root->left == nullptr) {
			current_root->pAcct = nullptr; 
			current_root = nullptr;

			return true;
		}
		else if (current_root->right == nullptr && current_root->left != nullptr) {
			Node* left_root = current_root->left; 
			Node* newRoot = LeftRootRightNode(left_root);
			current_root->pAcct = nullptr;
			current_root = newRoot;
			newRoot = nullptr; 
			return true;
		}
		else if (current_root->right != nullptr && current_root->left == nullptr) {
			Node* right_root = current_root->right; 
			Node* newRoot = RightRootLeftNode(right_root);	
			current_root->pAcct = nullptr;
			current_root = newRoot;
			newRoot = nullptr; 
			return true;
		}
		else if(current_root->right != nullptr && current_root->left != nullptr) {
			Node* right_root = current_root->right;
			Node* newRoot = RightRootLeftNode(right_root);
			current_root->pAcct = nullptr; 
			current_root = newRoot; 
			newRoot = nullptr;
			return true; 
		}
	}
	else if (current_root->pAcct->accountId() > account_id) {
		return DeleteHelper(account_id, account, current_root->left);
	}
	else if(current_root->pAcct->accountId() < account_id) {
		return DeleteHelper(account_id, account, current_root->right);
	}

	return false; 
}

BSTree::Node* BSTree::RightRootLeftNode(Node* current_node)
{
	bool inWhile = false; 
	while (current_node->left != nullptr) {
		current_node = current_node->left; 
		inWhile = true; 
	}
	if (current_node->right != nullptr && inWhile) {
		if (current_node->left != nullptr) {
			return RightRootLeftNode(current_node->left);
		}
	}
	return current_node; 
}

BSTree::Node* BSTree::LeftRootRightNode(Node* current_node)
{
	bool inWhile = false; 
	while (current_node->right != nullptr) {
		current_node = current_node->left;
		inWhile = true; 
	}
	if (current_node->left != nullptr && inWhile) {
		if (current_node->right != nullptr) {
			return RightRootLeftNode(current_node->left);
		}
	}
	return current_node;
}

BSTree& BSTree::operator=(const BSTree& tree)
{
	Empty();
	if (!tree.isEmpty()) {
		this->Insert(tree.root_->pAcct);
	}
	if (tree.root_->left != nullptr) {
		AssignmentOperatorHelper(tree.root_->left);

	}
	if (tree.root_->right != nullptr) {
		AssignmentOperatorHelper(tree.root_->right);

	}
	
	return *this;
}

void BSTree::AssignmentOperatorHelper(Node* current_node)
{
	this->Insert(current_node->pAcct);
	if (current_node->left != nullptr) {
		AssignmentOperatorHelper(current_node->left);
	}
	if (current_node->right != nullptr) {
		AssignmentOperatorHelper(current_node->right);
	}

}