
/*
Author: Cordell Hurst
Course : CSCI 335 Software Design and Analysis III
Instructor: Stewart Weiss
Assignment 02

This program...
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
	//this->maxheight = 0;

	cout << "AVL Default Constructor.\n";
}
// copy constructor
AVL_Tree::AVL_Tree(const AVL_Tree &tree)
{
	root = clone(tree.root);
}
//Donish
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
//destructor
AVL_Tree::~AVL_Tree()
{
	makeEmpty(root);
}
//Donish
void AVL_Tree::rotateLL(ArborNode *&NodeIn)//rotateWithLeftchild
{
	ArborNode *tempnode = NodeIn->left;
	NodeIn->left = tempnode->right;
	tempnode->right = NodeIn;
	NodeIn->height = max(height(NodeIn->left), height(NodeIn->right)) + 1;
	tempnode->height = max(height(tempnode->left), NodeIn->height) + 1;
	NodeIn = tempnode;
}
//Donish
void AVL_Tree::rotateRR(ArborNode *&NodeIn)//rotateWithRightchild
{
	ArborNode *tempnode = NodeIn->right;
	NodeIn->right = tempnode->left;
	tempnode->left = NodeIn;
	NodeIn->height = max(height(NodeIn->right), height(NodeIn->left)) + 1;
	tempnode->height = max(height(tempnode->right), NodeIn->height) + 1;
	NodeIn = tempnode;
}
//Donish
void AVL_Tree::doubleWithLeftChild(ArborNode *&NodeIn)
{
	rotateRR(NodeIn->left);
	rotateLL(NodeIn);
}
//Donish
void AVL_Tree::doubleWithRightChild(ArborNode *&NodeIn)
{
	rotateLL(NodeIn->right);
	rotateRR(NodeIn);
}
// Search methods:
//Donish
const Tree& AVL_Tree::find(const Tree &x) const
{
	return find(x, root);
}
//Donish
const Tree& AVL_Tree::findMin() const
{
	return findMin(root);
}
//Donish
const Tree& AVL_Tree::findMax() const
{
	return findMax(root);
}




list<Tree> AVL_Tree::findallmatches(const Tree &x) const
{
	if (root == nullptr)
	{
		cout << "Collection is empty.\n";
	}
	else
		return FindAllMatches(x, root);
}
list<Tree> AVL_Tree::FindAllMatches(const Tree &TreeIn, ArborNode *NodeIn) const
{
	if (NodeIn == nullptr)
	{
		list<Tree>
	}
}



//donish
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
//donish
//recursiveness action
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
void AVL_Tree::clear()// empty the tree
{
	makeEmpty(root);
}

//Donish
void AVL_Tree::insert(const Tree& x)// insert element x
{
	//call private recursive func
	insert(x, root);
}
//Donish
void AVL_Tree::remove(const Tree& x)// remove element x
{
	//call private recursive func
	remove(x, root);
}
//Donish
void AVL_Tree::balance(ArborNode *& NodeIn)
{
	if (NodeIn == nullptr)
	{
		return;
	}
	if (height(NodeIn->left) - height(NodeIn->right) > ALLOWED_IMBALANCE)
	{
		if (height(NodeIn->left->left) >= height(NodeIn->right->right))
		{
			rotateLL(NodeIn);
		}
		else
		{
			doubleWithLeftChild(NodeIn);
		}
	}
	else
	{
		if (height(NodeIn->right) - height(NodeIn->left) > ALLOWED_IMBALANCE)
		{
			if (height(NodeIn->right->right) >= height(NodeIn->right->right))
			{
				rotateRR(NodeIn);
			}
			else
			{
				doubleWithRightChild(NodeIn);
			}
		}
	}
	NodeIn->height = max(height(NodeIn->left), height(NodeIn->right)) + 1;
}

//PRIVATE RECURSIVE FUNCTIONS
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
//Donish
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
//donish
const Tree& AVL_Tree::findMin(ArborNode *NodeIn) const
{
	if (NodeIn == nullptr)
	{
		return NO_TREE;
	}
	if (NodeIn->left == nullptr)
	{
		return NodeIn->ArborElement;
	}
	return findMin(NodeIn->left);
}
//donish
const Tree& AVL_Tree::findMax(ArborNode* NodeIn) const
{
	if (NodeIn == nullptr)
	{
		return NO_TREE;
	}
	if (NodeIn->right == nullptr)
	{
		return NodeIn->ArborElement;
	}
	return findMin(NodeIn->right);
}
//Donish
void AVL_Tree::insert (const Tree & TreeIn, ArborNode *&NodeIn)
{
	if (NodeIn == nullptr)
	{
		NodeIn = new ArborNode{TreeIn, nullptr , nullptr, 0}; //Empty Tree, insert as root
	}
	else if (TreeIn < NodeIn->ArborElement)
	{
		insert (TreeIn, NodeIn->left);
	}
	else if (NodeIn->ArborElement < TreeIn)
	{
		insert (TreeIn, NodeIn->right);
	}
	else
	{
		//Duplicate; do nothing
	}
	balance(NodeIn);
}
//Donish
void AVL_Tree::remove (const Tree & TreeIn, ArborNode *&NodeIn)
{
	if (NodeIn == nullptr)
	{
		return; //Item not found
	}
	if (TreeIn < NodeIn->ArborElement)
	{
		remove (TreeIn, NodeIn->left);
	}
	else if (NodeIn->ArborElement < TreeIn)
	{
		remove (TreeIn, NodeIn->right);
	}
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


//Other shtuff
//donish
int AVL_Tree::height(ArborNode *NodeIn) const
{
	return NodeIn == nullptr ? -1 : NodeIn->height;
}
//Done not tested
int AVL_Tree::max(int left, int right)
{
	if (left < right)
		return right;
	else if (right < left)
		return left;
	else
		return left;//both are same value
}

