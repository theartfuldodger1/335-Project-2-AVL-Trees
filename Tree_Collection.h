
/*
Author: Cordell Hurst
Course : CSCI 335 Software Design and Analysis III
Instructor: Stewart Weiss
Assignment 02

This program...
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
	int count_of_tree_species(const string & species_name);
	int count_of_trees_in_boro(const string & boro_name);

	//This returns a list<string> object containing a list of all of the actual tree species that match a
	//given parameter string species_name.This method should be case insensitive.The list
	//returned by this function should not contain any duplicate names and may be empty.
	list<string> get_matching_species(const string & species_name);
	void AddTree(const Tree&);//need string list work
	void RemoveTree(const Tree&);

private:
	struct BoroughBox
	{
		string borough;
		int boroughCount;

		bool operator<(const BoroughBox &second) const
		{
			if (toLowerCase(borough) < toLowerCase(second.borough))
			{
				return true;
			}
			else if (toLowerCase(borough) > toLowerCase(second.borough))
			{
				return false;
			}
			return (borough.size() < second.borough.size());
		}
	};

	struct SpeciesBox
	{
		string species;
		int speciesCount = 0;

		bool operator<(const SpeciesBox &second) const
		{
			if (toLowerCase(species) < toLowerCase(second.species))
			{
				return true;
			}
			else if (toLowerCase(species) > toLowerCase(second.species))
			{
				return false;
			}
			return (species.size() < second.species.size());
		}
	};
	typedef set<BoroughBox>::iterator boroIterMk;
	typedef set<SpeciesBox>::iterator speciesIterMk;

	int tree_count; //Total number of trees stored in the collection 

	AVL_Tree ArborHarbor;
	list<string> TreeTypes;
	set<BoroughBox, less<BoroughBox>> BoroughNames; //change type to BoroughBox and adjust functions insertion and deletion
	set<SpeciesBox, less<SpeciesBox>> TreeSpecies; //change type to SpeciesBox and adjust functions insertion and deletion
	
};
#endif /* Tree_Collection_H__ */
