
/*
Author: Cordell Hurst
Course : CSCI 335 Software Design and Analysis III
Instructor: Stewart Weiss
Assignment 02
30 March 2017
This program is tasked to read the input file, parse its lines, construct a Tree object for each line
and make the calls to the Tree_Collection class to insert tree objects into the collection. As each line of data
is read, its 41 fields are separated and the proper subset of nine of them are used to construct the
Tree object. Tree_Collection, uses the "spc_common/tree_id" pair as a unique key for inserting
the Tree objects into the encapsulated AVL tree. The TreeCollection also keeps track of the names of
all species that are stored and in which boroughs the trees are located using <set>. AVL_Tree holds all
complete trees from the census. Any blank feilds that have been declared blank or incorrectly may
invalidate that line of data. the user is asked to provide a species name/tree type in as few as one word
or as many as three. the users input is processed and the species that match or have individual consecutive
words that match are counted and that information is displayed for the user. Data comes from NYC Open Data
and can be visualized @ www.cloudred.com/labprojects/nyctrees
*/

#include <iostream>
#include <string> //for string handling
#include <list> //for lists

#include "AVL.h"

using namespace std;

// default
AVL_Tree::AVL_Tree()
{
	root = NULL;
}
// copy constructor
AVL_Tree::AVL_Tree(const AVL_Tree &tree)
{
	root = clone(tree.root);
}
//destructor
AVL_Tree::~AVL_Tree()
{
	makeEmpty(root);
	delete root;
}

// Search methods:
//Recursive. returns as a Tree. string comparison
const Tree& AVL_Tree::find(const Tree &x) const
{
	return find(x, root);
}
//Recursive. Returns min based on string comparison
const Tree& AVL_Tree::findMin() const
{
	return findMin(root);
}
//Recursive. Returns max based on string comparison
const Tree& AVL_Tree::findMax() const
{
	return findMax(root);
}
//Search for all matches of a particular species based on string comparison
//uses two algorithms, one an iterative search/find and the other an iterative
//in-order traversal modified to start with the object found by the first algo
//and push the found objects into a list. The in-order traversal uses a stack
//returns a list of trees
list<Tree> AVL_Tree::findallmatches(const Tree &x) const
{
	//use an iterative find. once found, use that as new root for loop
	bool done = false;
	Tree tree1 = x;
	list<ArborNode*> NodeStack;
	list<Tree> Outgoing;

	ArborNode *current;
	current = root;

	//initial find algorithm
	while (current != NULL && !samename(tree1, current->ArborElement))
	{
		if (islessname(tree1, current->ArborElement))
			current = current->left;
		else
			current = current->right;
	}

	int i = 0;
	while (!done)//modified iterative in-order traversal using a stack
	{
		if (current != nullptr)
		{
			NodeStack.push_front(current);
			current = current->left;
		}
		else
		{
			if (!NodeStack.empty())
			{
				current = NodeStack.front();
				
				if (samename(tree1, current->ArborElement))
					Outgoing.push_back(current->ArborElement);
				
				NodeStack.pop_front();
				current = current->right;
			}
			else
				done = 1;
		}
	}
	return Outgoing;
}
// Displaying the tree contents:
void AVL_Tree::print(ostream& out) const
{
	if (root == nullptr)
	{
		out << "Empty tree.\n";
	}
	else
		printTree(root, out);
}
//recursiveness action! another way to display the tree contents
void AVL_Tree::printTree(ArborNode *NodeIn, ostream& out) const
{
	if (NodeIn != nullptr)
	{
		printTree(NodeIn->left, out);
		out << NodeIn->ArborElement << endl;
		printTree(NodeIn->right, out);
	}
}

// Tree modifiers:
//empties avl tree
void AVL_Tree::clear()// empty the tree
{
	makeEmpty(root);
}
//calls recursive insert
void AVL_Tree::insert(const Tree& x)// insert element x
{
	//call private recursive func
	insert(x, root);
}
//calls recursive remove function
void AVL_Tree::remove(const Tree& x)// remove element x
{
	//call private recursive func
	remove(x, root);
}


//PRIVATE RECURSIVE FUNCTIONS
//Copy constructor accessed by regular copy constructor
AVL_Tree::ArborNode* AVL_Tree::clone(ArborNode *NodeIn) const
{
	if (NodeIn == nullptr)
	{
		return nullptr;
	}
	else
	{
		return new ArborNode{ NodeIn->ArborElement, clone(NodeIn->left), clone(NodeIn->right), NodeIn->height };
	}
}
//donish
//Internal recursive delete
void AVL_Tree::makeEmpty(ArborNode *&NodeIn)
{
	if (NodeIn != nullptr)
	{
		makeEmpty(NodeIn->left);
		makeEmpty(NodeIn->right);
		delete NodeIn;
	}
	NodeIn = nullptr;
}
//Printing method that demonstrates 3 different print algorithms. This is called by disabled internally
//displayInOrder
//displayPreOrder
//displayPostOrder
void AVL_Tree::printAll()
{
	//this->displayInOrder(root);
	//cout << "Print In Order Complete\n";
	//this->displayPreOrder(root);
	//cout << "Print Pre Order Complete\n";
	//this->displayPostOrder(root);
	//cout << "Print Post Order Complete\n";
}
//Recursive printing methods:
void AVL_Tree::displayInOrder(ArborNode *nodein) const
{
	if (nodein)
	{
		displayInOrder(nodein->left);
		cout << nodein->ArborElement << endl;
		displayInOrder(nodein->right);
	}
}
void AVL_Tree::displayPreOrder(ArborNode *nodein) const
{
	if (nodein)
	{
	cout << nodein->ArborElement << endl;
	displayPreOrder(nodein->left);
	displayPreOrder(nodein->right);
	}
}
void AVL_Tree::displayPostOrder(ArborNode *nodein) const
{
	if (nodein)
	{
		displayPostOrder(nodein->left);
		displayPostOrder(nodein->right);
		cout << nodein->ArborElement << endl;
	}
}
//Recursive find() Returns Tree object if found. otherwise empty tree
const Tree& AVL_Tree::find(const Tree &TreeIn, ArborNode *NodeIn) const
{
	if (NodeIn == nullptr)
		return NO_TREE;
	else if (TreeIn < NodeIn->ArborElement)
		return find(TreeIn, NodeIn->left);
	else if (NodeIn->ArborElement < TreeIn)
		return find(TreeIn, NodeIn->right);
	else
		return NodeIn->ArborElement; //Match!
}
//recursive findMin(). Returns Tree object if found. otherwise empty tree
const Tree& AVL_Tree::findMin(ArborNode *NodeIn) const
{
	if (NodeIn == nullptr)
		return NO_TREE;
	if (NodeIn->left == nullptr)
		return NodeIn->ArborElement;
	return findMin(NodeIn->left);
}
//Recursive findMax(). Returns Tree object if found. otherwise empty tree
const Tree& AVL_Tree::findMax(ArborNode* NodeIn) const
{
	if (NodeIn == nullptr)
		return NO_TREE;
	if (NodeIn->right == nullptr)
		return NodeIn->ArborElement;
	return findMin(NodeIn->right);
}
//Recursive insert w/balance call
void AVL_Tree::insert (const Tree &TreeIn, ArborNode *&NodeIn)
{
	if (NodeIn == nullptr)
		NodeIn = new ArborNode{TreeIn, nullptr , nullptr, 0};//insert as leaf
	else if (TreeIn < NodeIn->ArborElement)
		insert (TreeIn, NodeIn->left);
	else if (NodeIn->ArborElement < TreeIn)
		insert (TreeIn, NodeIn->right);
	else
		//Duplicate; do nothing
	balance(NodeIn);
}
//Recursive remove w/ balance call
void AVL_Tree::remove (const Tree &TreeIn, ArborNode *&NodeIn)
{
	if (NodeIn == nullptr)
		return; //Item not found
	if (TreeIn < NodeIn->ArborElement)
		remove (TreeIn, NodeIn->left);
	else if (NodeIn->ArborElement < TreeIn)
		remove (TreeIn, NodeIn->right);
	else if (NodeIn->left != nullptr && NodeIn->right != nullptr) //Two children
	{
		NodeIn->ArborElement = findMin(NodeIn->right);
		remove (NodeIn->ArborElement, NodeIn->right);
	}
	else
	{
		ArborNode *oldNode = NodeIn;
		NodeIn = (NodeIn->left != nullptr) ? NodeIn->left : NodeIn->right;
		delete oldNode;
	}
	balance (NodeIn);
}

//Tree Adjustment functions. All AVL nodes created with height info to facilitate
//Balances AVL Tree, keeps order integrity
void AVL_Tree::balance(ArborNode *&NodeIn)
{
	if (NodeIn == nullptr)
		return;
	if (height(NodeIn->left) - height(NodeIn->right) > ALLOWED_IMBALANCE)
	{
		if (height(NodeIn->left->left) >= height(NodeIn->left->right))
			rotateLL(NodeIn);
		else
			doubleWithLeftChild(NodeIn);
	}
	else
	{
		if (height(NodeIn->right) - height(NodeIn->left) > ALLOWED_IMBALANCE)
		{
			if (height(NodeIn->right->right) >= height(NodeIn->right->left))
				rotateRR(NodeIn);
			else
				doubleWithRightChild(NodeIn);
		}
	}
	NodeIn->height = max(height(NodeIn->left), height(NodeIn->right)) + 1;
}
//Rotate left
void AVL_Tree::rotateLL(ArborNode *&NodeIn)//rotateWithLeftchild
{
	ArborNode *tempnode = NodeIn->left;
	NodeIn->left = tempnode->right;
	tempnode->right = NodeIn;
	NodeIn->height = max(height(NodeIn->left), height(NodeIn->right)) + 1;
	tempnode->height = max(height(tempnode->left), NodeIn->height) + 1;
	NodeIn = tempnode;
}
//Rotate right
void AVL_Tree::rotateRR(ArborNode *&NodeIn)//rotateWithRightchild
{
	ArborNode *tempnode = NodeIn->right;
	NodeIn->right = tempnode->left;
	tempnode->left = NodeIn;
	NodeIn->height = max(height(NodeIn->right), height(NodeIn->left)) + 1;
	tempnode->height = max(height(tempnode->right), NodeIn->height) + 1;
	NodeIn = tempnode;
}
//Double rotation, calls RL
void AVL_Tree::doubleWithLeftChild(ArborNode *&NodeIn)
{
	rotateRR(NodeIn->left);
	rotateLL(NodeIn);
}
//Double Rotation, calls LR
void AVL_Tree::doubleWithRightChild(ArborNode *&NodeIn)
{
	rotateLL(NodeIn->right);
	rotateRR(NodeIn);
}

//Other
//Returns height of AVL node for rotations and balance
int AVL_Tree::height(ArborNode *NodeIn) const
{
	return NodeIn == nullptr ? -1 : NodeIn->height;
}
//simple greater than, less than function
int AVL_Tree::max(int left, int right)
{
	if (left < right)
		return right;
	else if (right < left)
		return left;
	else
		return left;//both are same value
}

