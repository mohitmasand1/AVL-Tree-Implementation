#include "AVLTree.h"
#include <vector>
#include <iostream>

using namespace std;

template <class K, class V>
int AVLTree<K, V>::getHeight(AVLTreeNode<K, V>* rt)
{
	if (rt == nullptr) return -1;
	return rt->height;
}

template <class K, class V>
int AVLTree<K, V>::getBalanceFactor(AVLTreeNode<K, V>* rt)
{
	if (rt == nullptr) return 0;
	return getHeight(rt->left) - getHeight(rt->right);
}

template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::insertNode(AVLTreeNode<K, V>* rt, K key, V val)
{
	if (rt == nullptr) {
		AVLTreeNode<K, V>* temp = new AVLTreeNode<K, V>(key, val);
		return temp;
	}
	if (key < rt->key) {
		AVLTreeNode<K, V>* leftkid = insertNode(rt->left, key, val);
		rt->left = leftkid;
		leftkid->parent = rt;
	}
	else if (key > rt->key) {
		AVLTreeNode<K, V>* rightkid = insertNode(rt->right, key, val);
		rt->right = rightkid;
		rightkid->parent = rt;
	}
	else return rt;

	rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
	int bf = getBalanceFactor(rt);

	if (bf > 1 && key < rt->left->key) {
		return RightRotate(rt);
	}
	else if (bf > 1 && key > rt->left->key) {
		rt->left = LeftRotate(rt->left);
		return RightRotate(rt);
	}
	else if (bf < -1 && key > rt->right->key) {
		return LeftRotate(rt);
	}
	else if (bf < -1 && key < rt->right->key) {
		rt->right = RightRotate(rt->right);
		return LeftRotate(rt);
	}
	return rt;
}

template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::removeNode(AVLTreeNode<K, V>* rt, K key)
{
	if (rt == nullptr)
		return rt;
	if (key < rt->key)
		rt->left = removeNode(rt->left, key);
	else if (key > rt->key)
		rt->right = removeNode(rt->right, key);

	else {
		if ((rt->left == nullptr) || (rt->right == nullptr)) { // if there are less than two children
			AVLTreeNode<K, V>* temp = rt->left ? rt->left : rt->right; // temp = the child that exists
			if (temp == nullptr) { // if there are no children
				temp = rt; // 
				rt = nullptr;
			}
			else { // if one kid
				temp->parent = rt->parent;
				*rt = *temp; // replace node with its subtree
			}
			delete temp;
		}
		else { // if there are two children
			AVLTreeNode<K, V>* temp = LeftMostNode(rt->right); // Successor
			rt->key = temp->key;
			rt->right = removeNode(rt->right, temp->key);
		}
	}

	if (rt == nullptr) return rt;

	rt->height = max(getHeight(rt->left), getHeight(rt->right)) + 1;
	int bf = getBalanceFactor(rt);

	if (bf > 1 && getBalanceFactor(rt->left) >= 0)
		return RightRotate(rt);
	else if (bf > 1 && getBalanceFactor(rt->left) < 0) {
		rt->left = LeftRotate(rt->left);
		return RightRotate(rt);
	}
	else if (bf < -1 && getBalanceFactor(rt->right) <= 0)
		return LeftRotate(rt);
	else if (bf < -1 && getBalanceFactor(rt->right) > 0) {
		rt->right = RightRotate(rt->right);
		return LeftRotate(rt);
	}
	return rt;
}

template <class K, class V>
vector <V> AVLTree<K, V>::Nodevalues(AVLTreeNode<K, V>* rt)
{
	vector <V> ans;
	inOrderVal(rt, ans);
	return ans;
}

template <class K, class V>
vector <K> AVLTree<K, V>::Nodekeys(AVLTreeNode<K, V>* rt)
{
	vector <K> ans;
	inOrderKey(rt, ans);
	return ans;
}

template <class K, class V>
unsigned int AVLTree<K, V>::Treesize(AVLTreeNode<K, V>* rt)
{
	if (rt == nullptr) return 0;

	else return Treesize(rt->left) + Treesize(rt->right) + 1;
}

template <class K, class V>
void AVLTree<K, V>::inOrderKey(AVLTreeNode<K, V>* rt, vector <K>& ans)
{
	if (rt == nullptr) return;
	inOrderKey(rt->left, ans);
	ans.push_back(rt->key);
	inOrderKey(rt->right, ans);
}

template <class K, class V>
void AVLTree<K, V>::inOrderVal(AVLTreeNode<K, V>* rt, vector <V>& ans)
{
	if (rt == nullptr) return;
	inOrderVal(rt->left, ans);
	ans.push_back(rt->value);
	inOrderVal(rt->right, ans);
}

template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::NodeSearch(AVLTreeNode<K, V>* rt, K key)
{
	if (rt == nullptr) return rt;

	if (rt->key == key) return rt;
	else if (rt->key > key) return NodeSearch(rt->left, key);
	else return NodeSearch(rt->right, key);
}

template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::LeftRotate(AVLTreeNode<K, V>* x)
{
	AVLTreeNode<K, V>* y = x->right;
	x->right = y->left;

	if (y->left != nullptr)
		y->left->parent = x;

	y->parent = x->parent;

	if (x->parent == nullptr)
		root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;

	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	return y;
}

template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::RightRotate(AVLTreeNode<K, V>* x)
{
	AVLTreeNode<K, V>* y = x->left;
	x->left = y->right;

	if (y->right != nullptr)
		y->right->parent = x;

	y->parent = x->parent;

	if (x->parent == nullptr)
		root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;

	y->right = x;
	x->parent = y;

	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

	return y;
}

template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::LeftMostNode(AVLTreeNode<K, V>* rt)
{
	AVLTreeNode<K, V>* curr = rt;
	while (curr->left != nullptr)
		curr = curr->left;

	return curr;
}

template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::copyTree(AVLTreeNode<K, V>* copy)
{
	if (copy == nullptr) return nullptr;

	AVLTreeNode<K, V>* add = new AVLTreeNode<K, V>(copy->key, copy->value);
	add->height = copy->height;
	add->left = copyTree(copy->left);
	if (add->left != nullptr) add->left->parent = add;
	add->right = copyTree(copy->right);
	if (add->right != nullptr) add->right->parent = add;

	return add;
}

template <class K, class V>
void AVLTree<K, V>::deleteTree(AVLTreeNode<K, V>* remove)
{
	if (remove != nullptr) {
		deleteTree(remove->left);
		deleteTree(remove->right);
		delete remove;
		treesize--;
	}
}



////////////////////////////////////////////
 


// Copy Constructor
template <class K, class V>
AVLTree<K, V>::AVLTree(const AVLTree<K, V>& copy)
{
	root = copyTree(copy.root);
	if (copy.root != nullptr)
		root->height = copy.root->height;
	treesize = copy.treesize;
}


// Assignment Operator
template <class K, class V>
AVLTree<K, V>& AVLTree<K, V>::operator=(const AVLTree<K, V>& assign)
{
	if (this != &assign) {
		deleteTree(root);
		root = copyTree(assign.root);
		if (assign.root != nullptr)
			root->height = assign.root->height;
		treesize = assign.treesize;
	}
	return *this;
}


// Destructor
template <class K, class V>
AVLTree<K, V>::~AVLTree()
{
	deleteTree(root);
}


// Insert key/value
template <class K, class V>
bool AVLTree<K, V>::insert(K key, V val)
{
	int oldSize = Treesize(root);
	root = insertNode(root, key, val);
	if (oldSize != Treesize(root)) treesize++;

	return oldSize != treesize;
}


// Remove key/value
template <class K, class V>
bool AVLTree<K, V>::remove(K key)
{
	int oldSize = Treesize(root);
	root = removeNode(root, key);
	if (oldSize != Treesize(root)) treesize--;

	return oldSize != treesize;
}


// Search for value with key
template <class K, class V>
V AVLTree<K, V>::search(K key)
{
	AVLTreeNode<K, V>* tmp = NodeSearch(root, key);
	if (tmp == nullptr) throw std::runtime_error("Key was not found");
	return tmp->value;
}


// Get Values
template <class K, class V>
vector <V> AVLTree<K, V>::values()
{
	return Nodevalues(root);
}


// Get Keys
template <class K, class V>
vector <K> AVLTree<K, V>::keys()
{
	return Nodekeys(root);
}


// Get size
template <class K, class V>
unsigned int AVLTree<K, V>::size()
{
	return treesize;
}