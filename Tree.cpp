
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
#include <string>	//for string handling
#include <algorithm>
#include <iomanip>
#include <sstream>

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
//Given two Tree objects, it returns true if and only if they have the same species common name
//(spc_common) and tree_id, (case insensitive).
bool operator==(const Tree &tree1, const Tree &tree2)
{
	string common1 = tree1.spc_common;
	string common2 = tree2.spc_common;

	if (common1 == common2 && tree1.tree_id == tree2.tree_id)
		return true;

	return false;
}
//This compares the two trees using spc_common as the primary key and tree_id as the secondary
//key and returns true if tree1 is less than tree2 in this ordering and false otherwise. (case insensitive)
bool operator<(const Tree & tree1, const Tree & tree2)
{
	string common1 = tree1.spc_common;
	string common2 = tree2.spc_common;

	if (common1 < common2)
		return true;
	else if (common2 < common1)
		return false;
	else
	{
		if (tree1.tree_id < tree2.tree_id)
			return true;
		else //if (tree2.tree_id < tree1.tree_id)
			return false;
	}
}
//Convert int to a string, maintains limited number of digits
string toast(int value)
{
	if (value == 0)
		return "0";
	ostringstream s;
	s.precision(numeric_limits<int>::digits10);
	s << value;
	return s.str();
}
//Removes all trailing zeroes when converting an double to a string
string toast(double value)
{
	if (value == 0)
		return "0";
	ostringstream s;
	s.precision(numeric_limits<double>::digits10);
	s << value;
	return s.str();
}
//Comma seperated list output per professor
//This prints a Tree object onto the given ostream. Each of the members of the Tree object should
//be printed, with the tree spc_common name frst, then the tree_id. After that the order is not
//specifed - it can be whatever the programmer decides as long as it is clear.
ostream& operator<< (ostream & os, const Tree & t)
{
	string xtras = "";
	string bigArseSentenceOfTreeInfo;

	if (t.spc_common == "")
		bigArseSentenceOfTreeInfo += "Unknown";
	else
		bigArseSentenceOfTreeInfo = t.spc_common;//some are blank

	bigArseSentenceOfTreeInfo += ", " + toast(t.tree_id);
	bigArseSentenceOfTreeInfo += ", " + toast(t.tree_dbh);

	if(t.status == "")
		bigArseSentenceOfTreeInfo += ", Unknown";
	else
		bigArseSentenceOfTreeInfo += ", " + t.status;
	
	if (t.health == "")
		bigArseSentenceOfTreeInfo += ", n/a";
	else
		bigArseSentenceOfTreeInfo += ", " + t.health;//some are blank

	if (t.zipcode < 10)//Zip code, leading zero's for short ones!
		xtras = ", 0000";
	else if (t.zipcode < 100)
		xtras = ", 000";
	else if (t.zipcode < 1000)
		xtras = ", 00";
	else if (t.zipcode < 10000)
		xtras = ", 0";
	
	if (t.zipcode > 9999)
			bigArseSentenceOfTreeInfo += ", " + toast(t.zipcode);
	else
		bigArseSentenceOfTreeInfo += xtras + toast(t.zipcode);

	if(t.boroname == "")
		bigArseSentenceOfTreeInfo += ", Unknown";
	else
		bigArseSentenceOfTreeInfo += ", " + t.boroname;

	bigArseSentenceOfTreeInfo += ", ";
	bigArseSentenceOfTreeInfo += toast(t.x_sp);
	bigArseSentenceOfTreeInfo += ", ";
	bigArseSentenceOfTreeInfo += toast(t.y_sp);
	
	os << bigArseSentenceOfTreeInfo;
	return os;
}
//This returns true if and only if the two trees passed to it have identical spc_common members.
//This differs from operator== because it ignores the tree_id. (case insensitive)
bool samename(const Tree & tree1, const Tree & tree2)
{
	string common1 = tree1.spc_common;
	string common2 = tree2.spc_common;
	if (common1 == common2)
		return true;

	return false;
}
//This returns true if and only the spc_common member of the first Tree object is smaller than
//that of the second as strings.This differs from operator< because it ignores the tree_id. (case
//insensitive). For example, mytree.follows("mimosa") is true if mytree.spc_common =="pine"
bool islessname(const Tree & tree1, const Tree & tree2)
{
	string common1 = tree1.spc_common;
	string common2 = tree2.spc_common;

	if (common1 < common2)
		return true;
	else
		return false;
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