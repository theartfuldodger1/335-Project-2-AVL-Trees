
/*
Author: Cordell Hurst
Course : CSCI 335 Software Design and Analysis III
Instructor: Stewart Weiss
Assignment 02

This program...
*/

#ifndef __AVL_H__
#define __AVL_H__

#include <iostream>
#include <string> //for string handling
#include <list> //for lists

#include "Tree.h"

using namespace std;

//template<typename ArborNode>
class AVL_Tree
{
private:
	struct ArborNode
	{
		Tree ArborElement;
		ArborNode * left;
		ArborNode * right;
		int height = 0;
		
		//ArborNode constructor :
		ArborNode(const Tree &TreeIn, ArborNode *lt, ArborNode *rt, int ht)
			: ArborElement{ TreeIn }, left{ lt }, right{ rt }, height{ ht } { }
		
		ArborNode(const Tree &&TreeIn, ArborNode *lt, ArborNode *rt, int ht)
			: ArborElement{ move(TreeIn) }, left{ lt }, right{ rt }, height{ ht } { }
	};
	ArborNode* clone(ArborNode *NodeIn) const;
	list<Tree> AVL_Tree::FindAllMatches(const Tree &, ArborNode *) const;

	//typedef ArborNode *ArborNode_ptr;
	ArborNode *root;
	static const int ALLOWED_IMBALANCE = 1;
	//unsigned int maxheight;//DO WE NEED THIS???

	int height(ArborNode *NodeIn) const;
	int max(int, int); //returns greater of 2 numbers or returns one if equal

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

public:
	AVL_Tree();                     // default
	AVL_Tree(const AVL_Tree &);		// copy constructor
	~AVL_Tree();					// destructor

	// Search methods:
	const Tree& find(const Tree& x) const;
	const Tree& findMin() const;
	const Tree& findMax() const;
	//search the entire tree for all occurrences of Tree objects that match its Tree argument.
	//I have not provided code for you to implement this.Your task is to gure out how to do
	//it without having to examine every single ArborNode in the tree every time it is called and 
	//without missing any matching objects. Must use the samename() and islessname() methods
	list<Tree> findallmatches(const Tree & x) const;

	// Displaying the tree contents:
	void print(ostream& out) const;

	// Tree modifiers:
	void clear();                // empty the tree
	void insert(const Tree& x);  // insert element
	void remove(const Tree& x);  // remove element
};

#endif /* __AVL_H__ */