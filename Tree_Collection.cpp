
/*
Author: Cordell Hurst
Course : CSCI 335 Software Design and Analysis III
Instructor: Stewart Weiss
Assignment 02
30 March 2017
This program is tasked to read the inputfile, parse its lines, construct a Tree object for each line
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
#include <fstream>
#include <string> //for string handling
#include <list> //for lists
#include <set>
#include <sstream>

#include "Tree_Collection.h"

using namespace std;

//A default constructor for the class that creates an empty AVL tree, and empty TreeTypesList
//container, and an empty BoroughNames container.
TreeCollection::TreeCollection()
{
	//created empty by default:
	//AVL_Tree ArborHarbor;
	//list<string> TreeTypesList;
	//set<BoroughBox, less<BoroughBox>> BoroughNames; //change type to BoroughBox and adjust functions insertion and deletion
	//set<SpeciesBox, less<SpeciesBox>> TreeSpecies; //change type to SpeciesBox and adjust functions insertion and deletion
}
//A destructor for the class.
TreeCollection::~TreeCollection()
{
	
}
//This returns the total number of Tree objects stored in the collection.
int TreeCollection::total_tree_count()
{
	return tree_count;
}
//Calls recursive function. This returns the number of Tree objects in the collection whose spc_common species name
//matches the species_name specifed by the parameter. This method is case insensitive.
//If the method is called with a non-existent species the return value is 0.
int TreeCollection::count_of_tree_species(const string &species_name)
{
	//search a set. setname == b, search BoroughNames. setname == t, search TreeSpecies.
	return SearchSet('t', species_name); //returns int
}
//Calls recursive function. This returns the number of Tree objects in the collection that are located in the borough
//specifed by the parameter. This method is case insensitive. If the method is called with a
//non - existent borough name, the return value is 0.
int TreeCollection::count_of_trees_in_boro(const string &boro_name)
{
	//search a set. setname == b, search BoroughNames. setname == t, search TreeSpecies.
	return SearchSet('b', boro_name); //returns int
}
//Binary predicate for list::unique
//param to remove all duplicates with list::unique(), type string. Must be sorted first
bool UniqueList(string first, string second)
{
	return (first == second);
}
//Bool compare param for list::sort(), type string
bool ListCompare(string first, string second)
{
	if (first < second)
		return true;
	else
		return false;
}
//This returns a list<string> object containing a list of all of the actual tree species that match a
//given parameter string species_name.This method is case insensitive. The list
//returned by this function dos not contain any duplicate names and may be empty.
list<string> TreeCollection::get_matching_species(const string &species_name)
{
	string term1, term2, term3;
	string result;
	int multiterm =  0;
	int total_trees = 0;//can be used for verification of totals
	//attemps to divide input if multiple words. eliminates hyphen and makes all lower case
	TermSplitter(species_name, term1, term2, term3, multiterm);
	//overloaded functions for actual search
	if(multiterm == 1)
		return SearchTerms(total_trees, term1);
	else if (multiterm == 2)
		return SearchTerms(total_trees, term1, term2);
	else if (multiterm == 3)
		return SearchTerms(total_trees, term1, term2, term3);
}
//Switch for searching each term and comparing vs each term stored in <set> TreeSpecies. Overloaded and modified
//depending on the number of search terms required
list<string> TreeCollection::SearchTerms(int running_total, string term1)
{
	string pull1, pull2, pull3;
	int multipull = 0;
	running_total = 0;
	list<string> ListOut;
	spcMk TreeIter = TreeSpecies.begin();
	string hold;

	while (TreeIter != TreeSpecies.end())
	{
		TermSplitter(TreeIter->species, pull1, pull2, pull3, multipull);
		switch (multipull)
		{
			case 1:
				if (term1 == pull1)
				{
					hold = TreeIter->species;
					ListOut.push_back(hold);
					running_total += TreeIter->speciesCount;
				}
				break;
			case 2:
				if (term1 == pull1 || term1 == pull2)
				{
					hold = TreeIter->species;
					ListOut.push_back(hold);
					running_total += TreeIter->speciesCount;
				}
				break;
			case 3:
				if (term1 == pull1 || term1 == pull2 || term1 == pull3)
				{
					hold = TreeIter->species;
					ListOut.push_back(hold);
					running_total += TreeIter->speciesCount;
				}
				break;
		}
		TreeIter++;
	}
	return ListOut;
}
//Switch for searching each term and comparing vs each term stored in <set> TreeSpecies. Overloaded and modified
//depending on the number of search terms required
list<string> TreeCollection::SearchTerms(int running_total, string term1, string term2)
{
	string pull1, pull2, pull3, holder;
	int multipull = 0;
	running_total = 0;
	list<string> ListOut;
	spcMk TreeIter = TreeSpecies.begin();
	string hold;

	term1 += " " + term2;
	while (TreeIter != TreeSpecies.end())
	{
		TermSplitter(TreeIter->species, pull1, pull2, pull3, multipull);

		switch (multipull)
		{
		case 1:
			
			break;
		case 2:
			pull1 += " " + pull2;
			if (term1 == pull1)
			{
				hold = TreeIter->species;
				ListOut.push_back(hold);
				running_total += TreeIter->speciesCount;
			}
			break;
		case 3:
			pull1 += " " + pull2;
			pull2 += " " + pull3;

			if (term1 == pull1 || term1 == pull2)
			{
				hold = TreeIter->species;
				ListOut.push_back(hold);
				running_total += TreeIter->speciesCount;
			}
			break;
		}
		TreeIter++;
	}
	return ListOut;
}
//Switch for searching each term and comparing vs each term stored in <set> TreeSpecies. Overloaded and modified
//depending on the number of search terms required
list<string> TreeCollection::SearchTerms(int running_total, string term1, string term2, string term3)
{
	string pull1, pull2, pull3;
	int multipull = 0;
	running_total = 0;
	list<string> ListOut;
	spcMk TreeIter = TreeSpecies.begin();
	string hold;

	term1 += " " + term2 + " " + term3;
	while (TreeIter != TreeSpecies.end())
	{
		TermSplitter(TreeIter->species, pull1, pull2, pull3, multipull);
		switch (multipull)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			pull1 += " " + pull2 + " " + pull3;
			if (term1 == pull1)
			{
				hold = TreeIter->species;
				ListOut.push_back(hold);
				running_total += TreeIter->speciesCount;
			}
			break;
		}
		TreeIter++;
	}
	return ListOut;
}
//Adds tree to the collection. check <set> for like terms. if present, pull quantity and destroy 
//element to allow insertion with updated quantity. Handles both borough name and common_name (species).
//send Tree to AVL for insertion into tree. 
void TreeCollection::AddTree(Tree &tree1)
{
	char setname;//for SearchSetAdd(). using b for BoroughNames or t for TreeSpecies
	int quantityboro = 1;
	int quantitytree = 1;
	//check <set> for like terms. if present, pull quantity and destroy element to allow insertion
	//with updated quantity
	quantityboro = SearchSetAdd(setname = 'b', tree1.borough_name());
	if (quantityboro == 0 || quantityboro == -1)
		quantityboro = 1; 
	else
		quantityboro++;

	quantitytree = SearchSetAdd(setname = 't', tree1.common_name());
	if (quantitytree == 0 || quantitytree == -1)
		quantitytree = 1; 
	else
		quantitytree++;
	//Insertion happens here. <set> sorts and will not insert duplicates
	BoroughBox BBox{ tree1.borough_name(), quantityboro };
	BoroughNames.emplace(BBox);
	SpeciesBox SBox{ tree1.common_name(), quantitytree };
	TreeSpecies.emplace(SBox);
	//insertion into AVL
	ArborHarbor.insert(tree1);
	tree_count++;
}
//check <set> for like terms. if present, pull quantity and return value. Called by count functions
//search a set. setname == 'b' to search BoroughNames. setname == 't' to search TreeSpecies.
//Handles either borough name and common_name(species) depending on call
int TreeCollection::SearchSet(char setname, string searchterm)
{
	int valuefound;

	if (setname == 'b')
	{
		if (!BoroughNames.empty())
		{
			boroMk boroIter;
			BoroughBox BBox{ searchterm, 1 };
			boroIter = BoroughNames.find(BBox);//requires same type for search. Search defined in struct
			if (boroIter != BoroughNames.end())
				return (valuefound = boroIter->boroughCount);
			else
				valuefound = 0;
		}
	}
	else if (setname == 't')
	{
		if (!TreeSpecies.empty())
		{
			spcMk spcIter;
			SpeciesBox SBox{ searchterm, 1 };
			spcIter = TreeSpecies.find(SBox);//requires same type for search. Search defined in struct
			if (spcIter != TreeSpecies.end())
				return (valuefound = spcIter->speciesCount);
			else
				valuefound = 0;
		}
	}
	else
		cerr << "Invalid value passed to SearchSet(). Valid value for setname are: "
		<< "setname == 'b', search BoroughNames. setname == 't', search TreeSpecies.\n";
	return 0;//Item not found or empty tree
}
//check <set> for like terms. if present, pull quantity and destroy
//element to allow insertion with updated quantity. Handles both borough name and common_name (species).
//send Tree to AVL for insertion into tree. 
//set::emplace will sort and NOT place duplicates. also, cannot change a value once placed. 
//must destroy element and place new one.
int TreeCollection::SearchSetAdd(char setname, string searchterm)
{
	int valuefound;

	if (setname == 'b')
	{
		if (!BoroughNames.empty())
		{
			boroMk boroIter;
			BoroughBox BBox{ searchterm, 1 };
			boroIter = BoroughNames.find(BBox);
			if (boroIter != BoroughNames.end())
			{	
				valuefound = boroIter->boroughCount;
				BoroughNames.erase(boroIter);
				return valuefound;
			}
			else
				valuefound = 0;
		}
	}
	else if (setname == 't')
	{
		if (!TreeSpecies.empty())
		{
			spcMk spcIter;
			SpeciesBox SBox{ searchterm, 1 };
			spcIter = TreeSpecies.find(SBox);
			if (spcIter != TreeSpecies.end())
			{
				valuefound = spcIter->speciesCount; 
				TreeSpecies.erase(spcIter);
				return valuefound;
			}
			else
				valuefound = 0;
		}
	}
	else
		cerr << "Invalid value passed to SearchSet(). Valid value for setname are: "
		<< "setname == 'b' to search BoroughNames. setname == 't' to search TreeSpecies.\n";

	return 0;//Item not found or empty tree
}
//Splits strings with multiple words into seperate strings, makes all lower case and removes hyphen. Returns clean strings and a value
//reflecting the number of terms returned
void TreeCollection::TermSplitter(string species_name, string &term1, string &term2, string &term3, int &multiterm)
{
	term1.clear();
	term2.clear();
	term3.clear();
	string temp;
	
	unsigned int i = 0;
	while (i < species_name.size())
	{
		term1 += species_name[i];
		multiterm = 1;
		i++;
		temp = species_name[i];
		
		if (temp == " " || temp == "-")//remove hyphens
		{
			multiterm = 2;
			i++;
			while (i < species_name.size())
			{
				term2 += species_name[i];
				i++;
				temp = species_name[i];
				if (temp == " " || temp == "-")
				{
					multiterm = 3;
					i++;
					while (i < species_name.size())
					{
						term3 += species_name[i];
						species_name[i] = ' ';
						i++;
					}
				}
			}
		}
	}
}
//For printing entire collection in various formats
void TreeCollection::longDistance()
{
	ArborHarbor.printAll();
}
//passes search param(Tree) to AVL_Tree class and returns a list of Tree types back to main for
//processing values in main.
list<Tree> TreeCollection::AvlMatchTrees(const Tree &Tree1) const
{
	list<Tree> ListOut;
	ListOut = ArborHarbor.findallmatches(Tree1);
	return ListOut;
}