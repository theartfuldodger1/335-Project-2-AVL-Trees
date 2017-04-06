
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

#ifndef __Tree_Collection_H__
#define __Tree_Collection_H__

#include <iostream>
#include <string> //for string handling
#include <list> //for lists
#include <set> //For set operations

#include "Tree.h"
#include "AVL.h"

using namespace std;

class TreeCollection
{
public:
	TreeCollection();
	~TreeCollection();
	int total_tree_count();
	int count_of_tree_species(const string &species_name);
	int count_of_trees_in_boro(const string &boro_name);

	//This returns a list<string> object containing a list of all of the actual tree species that match a
	//given parameter string species_name.This method is case insensitive. The list
	//returned by this function dos not contain any duplicate names and may be empty.
	list<string> get_matching_species(const string &species_name);
	list<Tree> AvlMatchTrees(const Tree &Tree1) const;

	void AddTree(Tree&);
	void longDistance();//allows printing from main of all AVL elements. However AVL function disabled in AVL_Tree.cpp


private:
	struct BoroughBox//holds which borough and how many total trees in borough
	{
		string borough;
		int boroughCount;

		BoroughBox(string boro, int borocount) 
			: borough{ boro }, boroughCount{ borocount } {}

		//compare for set::find()
		bool operator<(const BoroughBox &second) const
		{
			if (borough < second.borough)
			{
				return true;
			}
			else if (borough > second.borough)
			{
				return false;
			}
			return (borough.size() < second.borough.size());
		}
	};
	struct SpeciesBox//holds species name and how many counted total
	{
		string species;
		int speciesCount = 0;

		SpeciesBox(string spc, int spccount) : species{ spc }, speciesCount{ spccount } {}

		//compare for set::find()
		bool operator<(const SpeciesBox &second) const
		{
			if (species < second.species)
			{
				return true;
			}
			else if (species > second.species)
			{
				return false;
			}
			return (species.size() < second.species.size());
		}
	};

	typedef list<string>::iterator listMk;
	typedef set<BoroughBox>::iterator boroMk;
	typedef set<SpeciesBox>::iterator spcMk;

	AVL_Tree ArborHarbor; //This is where the trees park...
	set<BoroughBox, less<BoroughBox>> BoroughNames;//Maintains borough total tree count. No duplicates
	set<SpeciesBox, less<SpeciesBox>> TreeSpecies;//Maintains species total tree count. No duplicates

	int SearchSet(char, string);
	int SearchSetAdd(char, string);
	int tree_count; //Total number of trees stored in the collection 
	void TermSplitter(string, string&, string&, string&, int &multiterm);
	list<string> SearchTerms(int, string term1);
	list<string> SearchTerms(int, string term1, string term2);
	list<string> SearchTerms(int, string term1, string term2, string term3);
};
#endif /* Tree_Collection_H__ */
