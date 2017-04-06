
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

#ifndef __AVL_H__
#define __AVL_H__

#include <iostream>
#include <string>
#include <list>

#include "Tree.h"

using namespace std;

class AVL_Tree
{
private:
	struct ArborNode
	{
		Tree ArborElement;
		ArborNode * left;
		ArborNode * right;
		int height = 0;
		
		//ArborNode constructors :
		ArborNode(const Tree &TreeIn, ArborNode *lt, ArborNode *rt, int ht)
			: ArborElement{ TreeIn }, left{ lt }, right{ rt }, height{ ht } { }
		
		ArborNode(const Tree &&TreeIn, ArborNode *lt, ArborNode *rt, int ht)
			: ArborElement{ move(TreeIn) }, left{ lt }, right{ rt }, height{ ht } { }
	};
	ArborNode* clone(ArborNode *NodeIn) const;

	ArborNode *root;
	static const int ALLOWED_IMBALANCE = 1;

	int height(ArborNode *NodeIn) const;
	int max(int, int); //returns greater of 2 numbers or returns either if equal

	void balance(ArborNode *&NodeIn);
	void doubleWithLeftChild(ArborNode *&NodeIn);
	void doubleWithRightChild(ArborNode *&NodeIn);
	void insert(const Tree &TreeIn, ArborNode *&NodeIn);
	void makeEmpty(ArborNode *&NodeIn);
	void printTree(ArborNode *NodeIn, ostream& out = cout) const;
	void remove(const Tree &TreeIn, ArborNode *&NodeIn);
	void rotateLL(ArborNode *&NodeIn);
	void rotateRR(ArborNode *&NodeIn);

	const Tree& find(const Tree &TreeIn, ArborNode *NodeIn) const;
	const Tree& findMin(ArborNode* NodeIn) const;
	const Tree& findMax(ArborNode* NodeIn) const;

	void displayInOrder(ArborNode *) const;
	void displayPreOrder(ArborNode *) const;
	void displayPostOrder(ArborNode *) const;

public:
	AVL_Tree();                     // default
	AVL_Tree(const AVL_Tree &);		// copy constructor
	~AVL_Tree();					// destructor

	// Search methods:
	const Tree& find(const Tree& x) const;
	const Tree& findMin() const;
	const Tree& findMax() const;
	//searches the entire tree for all occurrences of Tree objects that match its Tree argument.
	//Does NOT have to examine every single ArborNode in the tree every time it is called and 
	//does so without missing any matching objects. Uses samename() method.
	list<Tree> findallmatches(const Tree & x) const;

	// Displaying the tree contents:
	void print(ostream& out) const;

	// Tree modifiers:
	void clear();                // empty the tree
	void insert(const Tree& x);  // insert element
	void remove(const Tree& x);  // remove element

	void printAll();//disabled internally.
};

#endif /* __AVL_H__ */