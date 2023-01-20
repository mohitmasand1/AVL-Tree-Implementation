#include <vector>
#include <iostream>

using namespace std;

// AVL Node Class

template <class K, class V>
class AVLTreeNode {
public:
	// Should have attributes named:
	// parent - pointer to parent
	AVLTreeNode* parent;
	// left - pointer to left child
	AVLTreeNode* left;
	// right - pointer to right child
	AVLTreeNode* right;
	// key - node's key
	K key;
	// value - node's value
	V value;
	// height - node's height
	unsigned height;
	// Constructors ...
	AVLTreeNode(K key, V val) : key(key), value(val), height(0), parent(nullptr), left(nullptr), right(nullptr) {}

};

// AVL Tree class
template <class K, class V>
class AVLTree
{
private:
	// Tree attributes go here
	// Your tree MUST have a root node named root
	AVLTreeNode<K, V>* root;

	// Size of the tree
	unsigned treesize;

	// Pre: Key must not already exist in tree
	// Param: Root of tree, key, and value to insert
	// Post: Given key and value is inserted in the appropriate position as a node
	AVLTreeNode<K, V>* insertNode(AVLTreeNode<K, V>* rt, K key, V val);

	// Pre: Tree should contain the key being removed
	// Param: Root of the tree and the key to be removed 
	// Post: Given key and value is removed from the appropriate position from the tree
	AVLTreeNode<K, V>* removeNode(AVLTreeNode<K, V>* rt, K key);

	vector <V> Nodevalues(AVLTreeNode<K, V>* rt);

	vector <K> Nodekeys(AVLTreeNode<K, V>* rt);

	unsigned int Treesize(AVLTreeNode<K, V>* rt);

	bool isEmpty() { return root == nullptr; }

	void inOrderKey(AVLTreeNode<K, V>* rt, vector <K>& ans);

	void inOrderVal(AVLTreeNode<K, V>* rt, vector <V>& ans);

	AVLTreeNode<K, V>* NodeSearch(AVLTreeNode<K, V>* rt, K key);

	AVLTreeNode<K, V>* LeftRotate(AVLTreeNode<K, V>* x);

	AVLTreeNode<K, V>* RightRotate(AVLTreeNode<K, V>* x);

	int getHeight(AVLTreeNode<K, V>* rt);

	int getBalanceFactor(AVLTreeNode<K, V>* rt);

	AVLTreeNode<K, V>* LeftMostNode(AVLTreeNode<K, V>* rt);

	void deleteTree(AVLTreeNode<K, V>* remove);

	AVLTreeNode<K, V>* copyTree(AVLTreeNode<K, V>* copy);

public:

	AVLTree() : root(nullptr), treesize(0) {};

	AVLTree(const AVLTree& copy);

	AVLTree<K, V>& operator=(const AVLTree<K, V>& assign);

	~AVLTree();

	bool insert(K key, V val);

	bool remove(K key);
	
	V search(K key);

	vector <V> values();

	vector <K> keys();

	unsigned int size();

	void* getRoot() const { return root; };
};