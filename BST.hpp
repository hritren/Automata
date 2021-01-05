#pragma once

#include <iostream>
#include <vector>
#include <algorithm> 
#include <string>

using namespace std;

template <typename T>
class BST {
	struct Node {
		Node(T data) :data(data), left(nullptr), right(nullptr) {}
		T data;
		Node* left;
		Node* right;
	};

	Node* root = nullptr;

	void copyFrom_rec(const Node* otherNode, Node*& root);
	void free_rec(Node* root);

	void copyFrom(const BST& other);
	void free();

	bool contains_rec(T n, Node* currentNode, Node*& searched);
	void findMin(Node* root, Node*& minNode);
	bool remove_rec(T n, Node*& currentNode);
	int getHeight(Node* root);

	void createTreeRec(vector<T> v, int start, int end, Node*& root);

	void toVector_rec(Node* currentNode, vector<T>& v) const;

public:
	BST() = default;
	BST(vector<T> v);

	BST(const BST<T>& other);
	BST& operator= (const BST<T>& other);
	~BST();

	bool insert(T n);
	bool contains(T n);
	bool remove(T n);
	vector<T> toVector() const;
};

template<typename T>
BST<T>::~BST() {
	free();
}

template<typename T>
void BST<T>::free_rec(Node* root) {
	if (!root)
		return;
	free_rec(root->left);
	free_rec(root->right);
	delete root;
}

template<typename T>
void BST<T>::free() {
	free_rec(root);
}

template<typename T>
BST<T>::BST(vector<T> v) {
	if (!is_sorted(v.begin(), v.end()))
		throw "Array should be sorted!";
	createTreeRec(v, 0, v.size() - 1, root);
}

template<typename T>
BST<T>::BST(const BST<T>& other) : root(nullptr) {
	copyFrom(other);
}

template<typename T>
BST<T>& BST<T>::operator=(const BST<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
void BST<T>::createTreeRec(std::vector<T> v, int start, int end, Node*& root) {
	if (start > end) {
		root = nullptr;
		return;
	}
	int mid = (start + end) / 2;
	root = new Node(v[mid]);
	createTreeRec(v, start, mid - 1, root->left);
	createTreeRec(v, mid + 1, end, root->right);
}

template<typename T>
void BST<T>::copyFrom_rec(const Node* otherNode, Node*& root) {
	if (!otherNode)
		return;
	root = new Node(otherNode->data);
	copyFrom_rec(otherNode->left, root->left);
	copyFrom_rec(otherNode->right, root->right);
}

template<typename T>
void BST<T>::copyFrom(const BST<T>& other) {
	copyFrom_rec(other.root, root);
}

template<typename T>
int BST<T>::getHeight(Node* root) {
	if (root == nullptr)
		return 0;
	return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

template<typename T>
bool BST<T>::contains_rec(T n, Node* currentNode, Node*& prev) {
	if (!currentNode)
		return false;
	if (n == currentNode->data) {
		return true;
	}
	prev = currentNode;
	if (n > currentNode->data)
		return contains_rec(n, currentNode->right, prev);
	return contains_rec(n, currentNode->left, prev);
}

template<typename T>
bool BST<T>::contains(T n) {
	Node* temp;
	return contains_rec(n, root, temp);
}

template<typename T>
void BST<T>::findMin(Node* root, Node*& minNode) {
	Node* iter = root;
	while (iter != nullptr) {
		minNode = iter;
		iter = iter->left;
	}
}

template<typename T>
bool BST<T>::remove_rec(T n, Node*& currentNode) {
	Node* prev = nullptr;
	bool found = contains_rec(n, currentNode, prev);
	if (!found)
		return false;
	Node*& toDelete = prev == nullptr ? currentNode : n > prev->data ? prev->right : prev->left;

	if (!toDelete->left && !toDelete->right) {
		delete toDelete;
		toDelete = nullptr;
	} else if (!toDelete->left || !toDelete->right) {
		Node* newChild = toDelete->right == nullptr ? toDelete->left : toDelete->right;
		delete toDelete;
		toDelete = newChild;
	} else {
		Node* min;
		findMin(toDelete->right, min);
		swap(toDelete->data, min->data);
		return remove_rec(n, toDelete->right);
	}
	return true;
}

template<typename T>
bool BST<T>::remove(T n) {
	return remove_rec(n, root);
}

template<typename T>
bool BST<T>::insert(T n) {
	if (root == nullptr) {
		root = new Node(n);
		return true;
	}
	Node* prev = nullptr;
	bool found = contains_rec(n, root, prev);
	if (found)
		return false;

	if (n > prev->data)
		prev->right = new Node(n);
	else
		prev->left = new Node(n);
	return true;
}

template<typename T>
vector<T> BST<T>::toVector() const {
	vector<T> v;
	toVector_rec(root, v);
	return v;
}

template<typename T>
void BST<T>::toVector_rec(Node* currentNode, vector<T>& v) const {
	if (!currentNode) {
		return;
	}
	v.push_back(currentNode->data);
	toVector_rec(currentNode->left, v);
	toVector_rec(currentNode->right, v);
}
