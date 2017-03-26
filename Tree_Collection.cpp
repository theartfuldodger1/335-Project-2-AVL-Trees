
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
#include <set>

#include "Tree_Collection.h"

using namespace std;

typedef list<string>::iterator listIterMk;

//A default constructor for the class that creates an empty AVL tree, and empty TreeTypes
//container, and an empty BoroughNames container.
TreeCollection::TreeCollection()
{

}
//A destructor for the class.
TreeCollection::~TreeCollection()
{
	//TreeSpecies.~set();
	//BoroughNames.~set();
	//delete AVL tree
}
//Bool compare param for list::sort()
bool SpeciesCompare(const string& first, const string& second)
{
	if (toLowerCase(first) < toLowerCase(second))
	{
		return true;
	}
	else if (toLowerCase(first) > toLowerCase(second))
	{
		return false;
	}
	return (first.length() < second.length());
}
//send stuff to AVL.cpp
void TreeCollection::AddTree(const Tree& tree_in)
{
	ArborHarbor.insert(tree_in);
	tree_count++;
	
	//Search for borough,
	//if found, add 1 
	//else insert new borough
	//Tree TempTree = NO_TREE;
	Tree TempTree = ArborHarbor.find(tree_in);
	//update sets:
	//Tree TempTree = NO_TREE;

	string temp_borough = TempTree.borough_name();
	BoroughBox BoBox;
	BoBox.borough = temp_borough;
	BoBox.boroughCount = 1;
	BoroughNames.emplace(BoBox);
	
	if (TempTree.common_name() != "")
	{
		cout << "I'm here\n";
		string temp_species = TempTree.common_name();
		SpeciesBox SpBox;
		SpBox.species = temp_species;
		SpBox.speciesCount = 1;
		TreeSpecies.emplace(SpBox);
	}


	//two ways to iterate through and print
	boroIterMk iterBoro = BoroughNames.begin();
	while (iterBoro != BoroughNames.end())
	{
		cout << "Borough: " << iterBoro->borough << " Count: " << iterBoro->boroughCount << endl;
		iterBoro++;
	}
		cout << "B List size: " << BoroughNames.size() << endl;
	speciesIterMk iterSpecies = TreeSpecies.begin();
	while (iterSpecies != TreeSpecies.end())
	{
		cout << " Species: " << iterSpecies->species << " Count: " << iterSpecies->speciesCount << endl;
		iterSpecies++;
	}
	cout << "TS List size: " << TreeSpecies.size() << endl;
/*
	//////////////////////////////////////
	//c++11 foreach loop
	for (string const& borough : BoroughNames)
	{
		std::cout << borough << endl;
	}
	cout << BoroughNames.size() << endl;
	//////////////////////////////////////
*/	
}
void TreeCollection::RemoveTree(const Tree& tree_in)
{
	//if (ArborHarbor.find(tree_in));
	ArborHarbor.remove(tree_in);
	
	tree_count--;

	//Search for borough,
	//if found and count is > 0, subtract 1
	//else do nothing

	//update sets:
	Tree TempTree = NO_TREE;
	string temp_borough = TempTree.borough_name();
	string temp_species = TempTree.common_name();

	BoroughBox BoBox;
	//SpeciesBox SpBox;

	BoBox.borough = temp_borough;
	//SpBox.species = temp_species;

	/*Need to terate through
	BoroughNames.erase(BoBox);
	if (TempTree.common_name(tree_in) != "")
	{
		TreeSpecies.erase(SpBox);
	}
	*/
		//list<string> get_matching_species(const string & species_name);
		//////////////////////////////////////
	/*
		//c++11 foreach loop
	for (string const& borough : BoroughNames)
	{
		std::cout << borough << endl;
	}
	cout << BoroughNames.size() << endl;
	//////////////////////////////////////
	*/
}

//This returns the total number of Tree objects stored in the collection.
int TreeCollection::total_tree_count()
{
	return tree_count;
}

//This returns the number of Tree objects in the collection whose spc_common species name
//matches the species_name specied by the parameter. This method should be case insensitive.
//If the method is called with a non-existent species, the return value should be 0.
int TreeCollection::count_of_tree_species(const string &species_name)
{
	int temp = 0;//kill me

	string spcLC = species_name;

	toLowerCase(spcLC);



	//find species in set<string> TreeSpecies;
	//return count of that species or 0 if no match

	return temp;//change me
}
//This returns the number of Tree objects in the collection that are located in the borough
//specied by the parameter. This method should be case insensitive. If the method is called with a
//non - existent borough name, the return value should be 0.
int TreeCollection::count_of_trees_in_boro(const string &boro_name)
{
	int temp = 0;//Kill me

	string boroLC = boro_name;

	toLowerCase(boroLC);

	//find borough in set<string> BoroughNames;
	//return count or 0 if no match

	return temp;//change me
}
//This returns a list<string> object containing a list of all of the actual tree species that match a
//given parameter string species_name. This method should be case insensitive. The list returned 
//by this function should not contain any duplicate names and may be empty.
list<string> TreeCollection::get_matching_species(const string &species_name)
{
	//int set_size = TreeSpecies.size();
	
	//this is cool but isnt going to work for this situation. needs param match, see above comments
	speciesIterMk iterFront = TreeSpecies.begin();
	speciesIterMk iterBack = TreeSpecies.end();
	list<string> temp(TreeSpecies.size());
	
	//setIterMk iterFront = TreeSpecies.begin();

	/*
	while (iterFront != TreeSpecies.end())
	{

	}
	*/
	//go through set<string> TreeSpecies; and find the matches to species_name
	//populate a list with them
	//return said list

	return temp;
}