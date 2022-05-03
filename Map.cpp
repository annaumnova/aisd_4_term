// #.. -- the paragraph in the presentation
#include <stdio.h>
#include <iostream>
#include "List.h"
#include "Stack.h"

//consts
const int red = 1;
const int black = 0;

template<typename KEY,typename VALUE>
class Map {
private:
	//rbthree
	class RBtreeNode {
	public:
		KEY key; //the key
		VALUE value; //the value
		RBtreeNode* left; //the pointer to the leftChild
		RBtreeNode* right; //the pointer to the rightChild
		RBtreeNode* parent; //the pointer to the parent
		int color; //red=true=1 and black=false=0

	//friend class Map; //??????????????

		//constructor
		//RBtreeNode(){ 
		//	left = NULL; 
			//right = NULL; 
		//	parent = NULL; 
		//	key = NULL; 
		//	value = 0; 
		//	color = red; 
	//	}
		
		//destructor
	//	~RBtreeNode() {
			
		//}
	};

	RBtreeNode* root; //the root
	RBtreeNode* nil; //the nil (leaf)
	

	//left rorate
	void leftRorate(RBtreeNode* x_node) {
		RBtreeNode* y_node = x_node->right; //first tree: X(root)---Y(rightChild)
		x_node->right = y_node->left;
 
		//??????? #2
		if (y_node->left != nil)
			y_node->left->parent = x_node;
		y_node->parent = x_node->parent;

		//#3-5
		if (x_node->parent == NULL)
			root = y_node;
		else if (x_node == x_node->parent->left)
			x_node->parent->left = y_node;
		else x_node->parent->right = y_node;

		//#6
		y_node->left = x_node;
		x_node->parent = y_node;
	}

	//right rorate
	void rightRorate(RBtreeNode* y_node) {
		RBtreeNode* x_node = y_node->left; //first tree: X(leftChild)---Y(root)
		y_node->left = x_node->right;

		//#2
		if (x_node->right != nil)
			x_node->right->parent = y_node;
		x_node->parent = y_node->parent;

		//#3-5
		if (y_node->parent == NULL)
			root = x_node;
		else if (y_node == y_node->parent->right)
			y_node->parent->right = x_node;
		else y_node->parent->left = x_node;

		//#6
		x_node->right = y_node;
		y_node->parent = x_node;
	}

	//insert the new node and restore properties of rbtree (repaint, rorates)
	void insertNewNode(RBtreeNode* insertedNd) {
		RBtreeNode* p;
		RBtreeNode* grandParent;
		RBtreeNode* inserted_Newnode = insertedNd;

		//repeate if parent has color red, p.1 slide 23
		while (inserted_Newnode->parent->color == red) { //red
			p = inserted_Newnode->parent;
			grandParent = p->parent;

			if (p == grandParent->left) {

				//first case
				if (grandParent->right->color == red) {
					grandParent->left->color = black;
					grandParent->right->color = black;
					grandParent->color = red;
					inserted_Newnode = grandParent;
				}

				//second case
				else if (p->right = inserted_Newnode) {
					inserted_Newnode = p;
					leftRorate(inserted_Newnode);
				}

				//third case
				else {
					p->color = black;
					grandParent->color = red;
					rightRorate(grandParent);
				}
			}
			else { //slide 27 "p == grandParent->right"
				
				if (grandParent->left->color == red) {
					grandParent->left->color = black;
					grandParent->right->color = black;
					grandParent->color = red;
					inserted_Newnode = grandParent;
				}
				else {
					inserted_Newnode = p;
					rightRorate(inserted_Newnode);
					p->color = black;
					grandParent->color = red;
					leftRorate(inserted_Newnode);
				}
			}

		}
		root->color = black;
	}

	//remove the node and save rbtree's properties
	void removeNodeToBeDeleted(RBtreeNode* deletedNd) { //nodeToBeDeleted = x
		RBtreeNode* w; // x's brother
		RBtreeNode* nodeToBeDeleted = deletedNd;

		while (nodeToBeDeleted != nil && nodeToBeDeleted->color == black) {

			if (nodeToBeDeleted->parent->left == nodeToBeDeleted) {
				w = nodeToBeDeleted->parent->right;
				
				//first case
				if (w->color == red) {
					w->color = black;
					nodeToBeDeleted->parent->color = red;
					leftRorate(nodeToBeDeleted->parent);
					w = nodeToBeDeleted->parent->right;
				}

				//second case
				else if (w->left->color == black && w->right->color == black) { //black
					w->color = red;
					nodeToBeDeleted = nodeToBeDeleted->parent;
				}

				//third case
				else if (w->right->color == black) {
					w->left->color = black;
					w->color = red;
					rightRorate(w);
					w = nodeToBeDeleted->parent->right;
				}

				//fourth case
				else {
					w->color = nodeToBeDeleted->parent->color;
					nodeToBeDeleted->parent->color = black;
					w->right->color = black;
					leftRorate(nodeToBeDeleted->parent);
					nodeToBeDeleted = root;
				}
			}
			else { //x is rightChild
				w = nodeToBeDeleted->parent->left;

				//first case
				if (w->color == red) {
					w->color = black;
					nodeToBeDeleted->parent->color = red;
					rightRorate(nodeToBeDeleted->parent);
					w = nodeToBeDeleted->parent->left;
				}

				//second case
				else if (w->left->color == black && w->right->color == black) { //black
					w->color = red;
					nodeToBeDeleted = nodeToBeDeleted->parent;
				}

				//third case
				else if (w->left->color == black) {
					w->right->color = black;
					w->color = red;
					leftRorate(w);
					w = nodeToBeDeleted->parent->left;
				}

				//fourth case
				else {
					w->color = nodeToBeDeleted->parent->color;
					nodeToBeDeleted->parent->color = black;
					w->left->color = black;
					rightRorate(nodeToBeDeleted->parent);
					nodeToBeDeleted = root;
				}

			}
			nodeToBeDeleted->color = black;
		}
	}
	
	//print tree, then print map
	void printTree(RBtreeNode* node, int indent = 0) {
		//indent = 0; //between parents and children, then +1
		if (node != nil) {
			printTree(node->left, indent + 1); //left subtree
			for (int i = 0; i < indent; i++) std::cout << " ";
				std::cout << node->key << " ";
			printTree(node->right, indent + 1); //right subtree
		}
	}

	//find tree, then find map
	RBtreeNode* findTree(RBtreeNode*node, KEY key) {
		if (key == node->key) //key matched with node
			return node;
		if (node == nil) //exist?
			throw std::out_of_range("it doesn't exist in this tree!");
		if (key < node->key) //the left subtree
			return node->left;
		return node->right;
	}

	//avoid C2248; make stack to delete
	void makeStackToDel(RBtreeNode* node, stack<KEY>& stackDel) {
		if (node != nil) {
			stackDel.push_back(node->key);

			//left and right subtrees
			makeStackToDel(node->left, stackDel);
			makeStackToDel(node->right, stackDel);
		}
	}

public:

	//constructor
	Map() {
		nil = new RBtreeNode;
		root = nil;
		nil->left = nullptr;
		nil->right = nullptr;
		nil->color = black;
	}
	
	//destructor
	~Map() {
		clear();
	}

	//add the element with key and value
	void insert(KEY key, VALUE value) {

		RBtreeNode* inserted_NewNode = new RBtreeNode;
		
		//properties of new node
		inserted_NewNode->parent = nullptr;
		inserted_NewNode->color = red;
		inserted_NewNode->left = nil;
		inserted_NewNode->right = nil;
		inserted_NewNode->key = key;
		inserted_NewNode->value = value;

		RBtreeNode* x = root;
		RBtreeNode* y = nullptr; //???nullptr
		

		while (x != nil) { //empty?
			y = x;
			if (inserted_NewNode->key > x->key) //newKey > rootKey
				x = x->right;
			else
				x = x->left; //newKey < rootKey
		}
		inserted_NewNode->parent = y; //leaf's parent is parent of newNode
		
		if (y == nullptr) //empty tree?
			root = inserted_NewNode; // G(V = 1 = newNode, E = 0); 1 element
		else if (inserted_NewNode->key > y->key) //newKey > leafKey we got the rightChild
			y->right = inserted_NewNode;
		else y->left = inserted_NewNode; // we got the leftChild

		//newNode ---> nil = NULL
		inserted_NewNode->left = NULL;
		inserted_NewNode->right = NULL;

		inserted_NewNode->color = red; //recolor

		insertNewNode(inserted_NewNode); //recover after insertion
	}

	//find the element with key
	RBtreeNode* find(KEY key) {
		return findTree(root, key);
	}

	//delete the element with key
	void remove(KEY key) {

		RBtreeNode* nodeToDel = nil;
		nodeToDel = find(key);

		RBtreeNode* x;
		RBtreeNode* y = nodeToDel;

		//origin color
		int originColor;
		originColor = nodeToDel->color;

		if (nodeToDel->left == NULL){ //#3 slide 31

			x = nodeToDel->right;

			//replace x and nodeToDel
			if (nodeToDel->parent == nullptr) // root -- nodeToDel -(right)- x
				root = x;
			else if (nodeToDel == nodeToDel->parent->left) // root -(left)- nodeToDel -(right)- x 
				nodeToDel->parent->left = x;
			else nodeToDel->parent->right = x; // root -(right)- nodeToDel -(right)- x 
			x->parent = nodeToDel->parent;
		}
		else if (nodeToDel->right == NULL) { //#4
			
			x = nodeToDel->right;

			//replace x and nodeToDel
			if (nodeToDel->parent == nullptr) // root -- nodeToDel -(right)- x
				root = x;
			else if (nodeToDel == nodeToDel->parent->left) // root -(left)- nodeToDel -(right)- x 
				nodeToDel->parent->left = x;
			else nodeToDel->parent->right = x; // root -(right)- nodeToDel -(right)- x 
			x->parent = nodeToDel->parent;
		}
		else { //children are NOT NULL, #5 slide 34

			//the leftmost element in the right subtree
			y = nodeToDel->right;
			while (y->left == nil)
				y = y->left;

			originColor = y->color;

			x = y->right;

			if (y->parent == nodeToDel)
				x->parent = y;
			else { 
				//replace y's rightChild to y
				if (y->parent == nullptr) 
					root = y->right;
				else if (y == y->parent->left) 
					y->parent->left = y->right;
				else y->parent->right = y->right; 
				y->right->parent = y->parent;

				y->right = nodeToDel->right;
				y->right->parent = y;
			}

			//replace y and nodeToDel
			if (nodeToDel->parent == nullptr)
				root = y;
			else if (nodeToDel == nodeToDel->parent->left)
				nodeToDel->parent->left = y;
			else nodeToDel->parent->right = y;
			y->parent = nodeToDel->parent;

			y->left = nodeToDel->left;
			y->left->parent = y;

			y->color = nodeToDel->color; //origin color
		}
		delete nodeToDel;

		if (originColor == black) //#6 slide 34
			removeNodeToBeDeleted(x);
	}

	//clear the map
	void clear() {
		stack<KEY> stackDel;
		makeStackToDel(root, stackDel); //make stack, write in stack nodes and keys

		//clear operation
		while (stackDel.getSize()) {
			remove(stackDel.getTop());
			stackDel.pop();
		}
	}

	//return list of keyes
	List<KEY> get_keys(RBtreeNode* node, List<KEY>& listNode) {

		if (node != nil) {
			listNode.insert(node->key);
			get_keys(node->left, listNode);
			get_keys(node->right, listNode);
		}

		get_keys(root, listNode);
		return listNode;
	}

	//return list of values
	List<VALUE> get_values(RBtreeNode* node, List<VALUE>& listNode) {

		if (node != nil) {
			listNode.insert(node->value);
			get_values(node->left, listNode);
			get_values(node->right, listNode);
		}

		get_values(root, listNode);
		return listNode;
	}

	//outputting
	void print() {
		return printTree(root);
	}
};