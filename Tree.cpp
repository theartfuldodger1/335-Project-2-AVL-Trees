/*
Author: Cordell Hurst
Course : CSCI 335 Software Design and Analysis III
Instructor: Stewart Weiss
Assignment 02

This program...
*/

#include <iostream> 
#include <string>	//for string handling
#include <algorithm>

#include "Tree.h"

using namespace std;

Tree::Tree(int id, int diam, string status, string health,
	string spc, int zip, string boro, double x, double y)
{
	tree_id = id;
	tree_dbh = diam;
	this->status = status;
	this->health = health;
	spc_common = spc;
	zipcode = zip;
	boroname = boro;
	x_sp = x;
	y_sp = y;
}
//iterates through string input and modifies strings upper case letters to lower case if needed
//Precondition: Valid string of letters
//Postcondition: Returns string with only lower case letters
void toLowerCase(string &wordIn)
{
	for (unsigned int i = 0; i < wordIn.length(); i++)
	{
		if (wordIn[i] == 45)
		{
			wordIn[i] = ' ';
		}
		else
		{
			if ((wordIn[i] >= 'A') && (wordIn[i] <= 'Z')) //looks for upper case
			{
				wordIn[i] = (char)((int)wordIn[i] + 32); //modifies accordingly by replacement
			}
		}
	}
}
//iterates through string input and modifies strings upper case letters to lower case if needed
//Precondition: Valid string of letters
//Postcondition: Returns string with only lower case letters
string toLowerCase(const string & wordIn)
{
	string word_temp = wordIn;

	for (int i = 0; i < word_temp.length(); i++)
	{
		if (word_temp[i] == 45)
		{
			word_temp[i] = ' ';
		}
		else
		{
			if ((word_temp[i] >= 'A') && (word_temp[i] <= 'Z')) //looks for upper case
			{
				word_temp[i] = (char)((int)word_temp[i] + 32); //modifies accordingly by replacement
			}
		}
	}
	return word_temp;
}
//Given two Tree objects, it returns true if and only if they have the same species common name
//(spc_common) and tree_id, (case insensitive).
bool operator==(const Tree & tree1, const Tree & tree2)
{
	string common1 = tree1.spc_common;
	string common2 = tree2.spc_common;

	toLowerCase(common1);
	toLowerCase(common2);

	if (common1 == common2 && tree1.tree_id == tree2.tree_id)
	{
		return true;
	}
	return false;
}
//This compares the two trees using spc_common as the primary key and tree_id as the secondary
//key and returns true if tree1 is less than tree2 in this ordering and false otherwise. (case insensitive)
bool operator<(const Tree & tree1, const Tree & tree2)
{
	string common1 = tree1.spc_common;
	string common2 = tree2.spc_common;

	toLowerCase(common1);
	toLowerCase(common2);

	if (common1 < common2)
	{
		return true;
	}
	else if (common2 < common1)
	{
		return false;
	}
	else
	{
		if (tree1.tree_id < tree2.tree_id)
		{
			return true;
		}
		else //if (tree2.tree_id < tree1.tree_id)
		{
			return false;
		}/*
		 else
		 {
		 return false;
		 }*/
	}
}
//Comma seperated list output per professor
//This prints a Tree object onto the given ostream. Each of the members of the Tree object should
//be printed, with the tree spc_common name rst, then the tree_id.After that the order is not
//specied - it can be whatever the programmer decides as long as it is clear.
ostream& operator<< (ostream & os, const Tree & t)
{
	string bigArseSentenceOfTreeInfo;

	if (t.spc_common == "")
	{
		bigArseSentenceOfTreeInfo += "Unknown";
	}
	else
	{
		bigArseSentenceOfTreeInfo = t.spc_common;//some are blank

	}

	bigArseSentenceOfTreeInfo += "," + t.tree_id;
	bigArseSentenceOfTreeInfo += ", " + t.status;

	if (t.health == "")
	{
		bigArseSentenceOfTreeInfo += ", Not Applicable";
	}
	else
	{
		bigArseSentenceOfTreeInfo += ", " + t.health;//some are blank
	}

	bigArseSentenceOfTreeInfo += ", " + t.tree_dbh;
	bigArseSentenceOfTreeInfo += ", " + t.boroname;
	bigArseSentenceOfTreeInfo += ", ";
	bigArseSentenceOfTreeInfo += t.x_sp;
	bigArseSentenceOfTreeInfo += ", ";
	bigArseSentenceOfTreeInfo += t.y_sp;

	os << bigArseSentenceOfTreeInfo;
	return os;
}
//This returns true if and only if the two trees passed to it have identical spc_common members.
//This differs from operator== because it ignores the tree_id. (case insensitive)
bool samename(const Tree & tree1, const Tree & tree2)
{
	string common1 = tree1.spc_common;
	string common2 = tree2.spc_common;

	toLowerCase(common1);
	toLowerCase(common2);

	if (common1 == common2)
	{
		return true;
	}
	return false;
}
//This returns true if and only the spc_common member of the first Tree object is smaller than
//that of the second as strings.This differs from operator< because it ignores the tree_id. (case
//insensitive). For example, mytree.follows(mimosa) is true if mytree.spc_common == pine
bool islessname(const Tree & tree1, const Tree & tree2)
{
	string common1 = tree1.spc_common;
	string common2 = tree2.spc_common;

	toLowerCase(common1);
	toLowerCase(common2);

	if (common1 < common2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//This returns the spc_common name of the Tree.
string Tree::common_name()
{
	return spc_common;
}
//This returns the name of the borough in which the Tree is located.
string Tree::borough_name()
{
	return boroname;
}
//This returns the value of the tree_dbh member.
double Tree::diameter()
{
	return tree_dbh;
}