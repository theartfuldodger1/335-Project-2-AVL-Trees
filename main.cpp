
/*
Author: Cordell Hurst
Course : CSCI 335 Software Design and Analysis III
Instructor: Stewart Weiss
Assignment 02

This program...
*/

#include <iostream>
#include <string>	//for string handling
#include <list>		//for lists
#include <fstream>	//for advanced file operations - ifstream/ofstream

#include "Tree_Collection.h"

using namespace std;

void switchGo();

////THIS LINE!
int main(int argc, char* argv[])
{	
	/*
	It is the task of the main program to read the input le, parse its lines, construct a Tree object for each line
	and make the calls to the TreeCollection class to insert that object into the collection. As each line of data
	is read, its 41 elds must be separated, and the proper subset of nine of them must be used to construct the
	Tree object. The TreeCollection will use the (spc_common, tree_id) pair as the unique key for inserting
	the Tree objects into its encapsulated AVL tree. The TreeCollection will also keep track of the names of
	all species that it stored, and in which boroughs the trees are located.
	*/
	double x;
	double y;
	int diam;
	int id;
	int zip;
	string boro;
	string health;
	string spc;
	string status;
	/*
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <Filename>\n A filename must follow executable.";
		return 1;
	}

	ifstream treeFile(argv[1]);

	if (!treeFile.is_open())
	{
		cerr << "Could not open file\n";
	}
	string newString;
	treeFile >> newString;

	cout << newString;
	*/
	x = 1;
	y = 2;
	diam = 3;
	id = 4;
	zip = 5;
	boro = "Brooklyn";
	health = "Test 2";
	spc = "Test 3"; // counterpart different for test of cases and '-' 
	status = "test 4";

	Tree tree1(id, diam, status, health, spc, zip, boro, x, y);

	x = 1;
	y = 2;
	diam = 3;
	id = 4;
	zip = 5;
	boro = "Manhattan";
	health = "Test 2";
	spc = "pizza";	// counterpart different for test of cases and '-' 
	status = "test 4";

	Tree tree2(id, diam, status, health, spc, zip, boro, x, y);

	Tree tree3(id, diam, status, health, spc, zip, boro, x, y);
	boro = "Queens";
	Tree tree4(id, diam, status, health, spc, zip, boro, x, y);
	boro = " brooklyn";
	Tree tree5(id, diam, status, health, spc, zip, boro, x, y);
	TreeCollection trl;
	boro = "Long Island";
	Tree tree6(id, diam, status, health, spc, zip, boro, x, y);
	
	trl.AddTree(tree1);
	trl.AddTree(tree2);
	trl.AddTree(tree3);
	trl.AddTree(tree4);
	trl.AddTree(tree5);
	trl.AddTree(tree6);

	trl.RemoveTree(tree4);
	/*
	cout << "equality: ";
	if (tree1 == tree2)
	{
		cout << "Yes!\n";
	}
	else
	{
		cout << "Boo!\n";
	}

	cout << "samename: ";
	if (samename(tree1, tree2))
	{
		cout << "Yes!\n";
	}
	else
	{
		cout << "Boo!\n";
	}

	cout << "Less than <: ";
	if (tree1 < tree2)
	{
		cout << "Winner!\n";
	}
	else
	{
		cout << "Boo!\n";
	}
	
	cout << "islessname: ";
	if (islessname(tree1, tree2))
	{
		cout << "Other winner!\n";
	}
	else
	{
		cout << "Bigger Boo!\n";
	}
	
	cout << "Common name: " << tree1.common_name(tree1) << " borough name: " << tree2.borough_name(tree2) <<
		" diameter: " << tree1.diameter(tree1) << endl;
	*/
	string stop;
	cout << "Stop!\n";
	cin >> stop;

	return 0;
}
void switchGo()
{
	
}