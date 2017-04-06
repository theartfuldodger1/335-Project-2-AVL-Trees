
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
#include <string>
#include <list>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "Tree_Collection.h"

using namespace std;

void UserPrompt(TreeCollection &);
string FileIterator(istream &, int);
int ScrollChars(istream &);
void ProcessFile(ifstream &, TreeCollection &);
void printBoroCounts(list<string> &, TreeCollection &);
int ScrollWhiteSpace(istream &cin);
string toLowerCase(const string &wordIn);
void voidLowerCase(string &wordIn);
string commaMachine(int numIn);

int main(int argc, char* argv[])
{
	/*//for command line execution
	 if (argc != 2)//for attempted launch w/o param
    {
        cerr << "\n\tUsage: " << argv[0] << " <Filename>\n\t\tA filename must follow executable.\n\n";
        return 1;
    }
    ifstream TreeFile(argv[1]);

    if (!TreeFile.is_open())
    {
        cerr << "\n\tCould not open file\n\ns";
        return 1;
    }
	*///for IDE execution
	///////////////////////////////////
	ifstream TreeFile("test");
	///////////////////////////////////
	TreeFile.clear();//discard first line

	TreeCollection Collection;
	ProcessFile(TreeFile, Collection);//Processess data input, creates AVL tree and corresponding Tree collection data
	UserPrompt(Collection);// User prompts and calls data retrival functions that display relevent data

	return 0;
}
//iterates through string input and modifies strings upper case letters to lower case if needed
//Precondition: Valid string of letters
//Postcondition: Returns string with only lower case letters
string toLowerCase(const string &wordIn)
{
	string word_temp = wordIn;

	for (int i = 0; i < word_temp.length(); i++)
	{
		if (word_temp[i] == 45)
			word_temp[i] = ' ';
		else
		{
			if ((word_temp[i] >= 'A') && (word_temp[i] <= 'Z')) //looks for upper case
				word_temp[i] = (char)((int)word_temp[i] + 32); //modifies accordingly by replacement
		}
	}
	return word_temp;
}
//iterates through string input and modifies strings upper case letters to lower case if needed
//Precondition: Valid string of letters
//Postcondition: Returns string with only lower case letters
void voidLowerCase(string &wordIn)
{
	for (unsigned int i = 0; i < wordIn.length(); i++)
	{
		if (wordIn[i] == 45)
			wordIn[i] = ' ';
		else
		{
			if ((wordIn[i] >= 'A') && (wordIn[i] <= 'Z')) //looks for upper case
				wordIn[i] = (char)((int)wordIn[i] + 32); //modifies accordingly by replacement
		}
	}
}
//Prompt user for input. Checks for whitespace following all words input. checks how many 
//words input, allowing a maximum of three. all words are checked to see if hyphens present
//These are removed and replaced with dashes for ease in processing comparissons
void UserPrompt(TreeCollection &Collection)
{
	int temp;
	string search_term1, search_term2, search_term3, term_consolidated;
	string treename;

	do  //Prompts for user input and validates quantity of terms input. looks for whitespace
	{
		cout << "\n\tEnter the tree species to learn more about it (\"quit\" to stop): ";
		cin >> search_term1;

		cout << "\n\tYou entered " << search_term1 << "." << endl << endl;

		temp = ScrollWhiteSpace(cin);
		if (temp == EOF || temp == 10)
			term_consolidated = search_term1;//one word input
		else
		{
			term_consolidated = search_term1;
			cin >> search_term2;

			temp = ScrollWhiteSpace(cin);
			if (temp == EOF || temp == 10)
				term_consolidated += " " + search_term2;//second word input
			else
			{
				term_consolidated += " " + search_term2;
				cin >> search_term3;
				term_consolidated += " " + search_term3;//third word input
				temp = ScrollWhiteSpace(cin); 

				if (temp != EOF && temp != 10)//too many terms input
					term_consolidated = "\tInvalid search term series. No more than three (3) terms allowed.\n";
			}
		}
		voidLowerCase(term_consolidated);
		//Data output starts here but is primarily handled elsewhere.
		if (term_consolidated != "quit")
		{
			cout << "\tAll matching species:\n\n";
			//species names in list post breakdown to lower case
			list<string> TreesFound = Collection.get_matching_species(term_consolidated);

			if (TreesFound.empty())
				cout << "\t\tNone. Species not found.\n";
			else
			{	
				list<string>::iterator listIter;
				for (listIter = TreesFound.begin(); listIter != TreesFound.end(); listIter++)
				{
					treename = *listIter;
					cout << "\t\t" << treename << "\n";
				}
				cout << "\n\tPopularity in the city:\n\n";
				printBoroCounts(TreesFound, Collection);//data output handler
			}
		}
	} while (term_consolidated != "quit");
}
//Data file handler. iterates through csv, collecting data from specific fields. data is
//assigned and a Tree object is created and passed to Tree_Collection for packaging and to pass to AVL for insert
void ProcessFile(ifstream &TreeFile, TreeCollection &Collection)
{
	//Tree variables
	double x, y;
	int diam, id, zip;
	string boro, health, spc, status;

	//Processing variables
	string idstr, xstr, ystr;
	string newString, temp;

	int firstPass = 0;
	int i = 1;//for skipping fields in data file
	while (!TreeFile.eof())
	{	//each FileIterator() scrolls through the datafile, skipping fields as required
		if (firstPass == 0)//this line first pass only. id then assigned @ end of loop
			id = atoi(FileIterator(TreeFile, i).c_str());//i == 1
		i += 2;
		diam = atoi(FileIterator(TreeFile, i).c_str());//i == 3
		status = toLowerCase(FileIterator(TreeFile, i));//i == 3
		i -= 2;
		health = toLowerCase(FileIterator(TreeFile, i));//i == 1
		i++;
		spc = toLowerCase(FileIterator(TreeFile, i));//i == 2
		i += 14;
		zip = atoi(FileIterator(TreeFile, i).c_str());//i == 16
		i -= 12;
		boro = toLowerCase(FileIterator(TreeFile, i));//i == 4
		i += 6;
		xstr = FileIterator(TreeFile, i);//i == 10
		x = atof(xstr.c_str());
		i -= 9;
		ystr = FileIterator(TreeFile, i);//i == 1

		firstPass = 1;
		int j = 0;
		while (j < ystr.size())//process y-coordinate string ystr
		{
			//delimiter is readubg the last entry in the line, the y-coordinate, the \n
			//and then turning the corner and grabbing the first entry on the next line.
			//the loop below cleans that up in the strings and converts to int and assigns
			//to variables
			temp = ystr[j];
			if (temp == "\n")
			{	
				j++;
				while (j < ystr.size())
				{
					idstr += ystr[j];
					ystr[j] = ' ';
					j++;
				}
				id = atoi(idstr.c_str());
				idstr.clear();
			}
			else
				j++;
		}
		y = atof(ystr.c_str());
		i = 1;
		//if statement - checking validity of all tree input
		if (x > 0 && y > 0 && diam > 0 && id > 0 && zip > 0 && zip > 0 &&
			(status == "alive" || status == "dead" || status == "stump") &&
			(health == "good" || health == "fair" || health == "poor") &&
			(boro == "brooklyn" || boro == "bronx" || boro == "manhattan" ||
				boro == "staten island" || boro == "queens"))
		{
			Tree tree1(id, diam, status, health, spc, zip, boro, x, y);
			Collection.AddTree(tree1);//AVL Insertion via Tree_Collection
		}
	}
}
//Scrolls through file data for processing specific fields as required
//Returns next data field as a string
string FileIterator(istream & TreeFile, int skip)
{
	string newString;
	int endFlag = 0;

	for (int i = 0; i < skip; i++)
	{
		getline(TreeFile, newString, ',');
		endFlag = ScrollChars(TreeFile);
	}
	return newString;
}
//allows skipping of parenthesis and iterates through whitespace after a word that may be 
//or is expected to be the last entry in order to find next entry or eof
//used only in FileIterator(). Returns next char as int
int ScrollChars(istream &TreeFile)
{
	int temp = TreeFile.peek();
	//catch parenthesis here
	if (temp == '"')
	{
		do
		{
			TreeFile.ignore();
			temp = TreeFile.peek();
		} while (temp != '"');
	}
	//9 == horizontal tab
	while (temp == ' ' || temp == 9)//skip trailing white space
	{
		TreeFile.ignore();
		temp = TreeFile.peek();
	}
	return temp;
}
//iterates through whitespace after a word that may be or is expected to be the last entry
//in order to find eof. Used by UserPrompt() for user input processing (cin). Returns next char as int
//Precondition: 2nd or 3rd word of search term input
//Postcondition: cin loaded with next non-whitespace data
int ScrollWhiteSpace(istream &cin)
{
	int temp = cin.peek();
	//9 == horizontal tab
	while (temp == ' ' || temp == 9)
	{
		cin.ignore();
		temp = cin.peek();
	}
	return temp;
}
//Handles processing AVL data. extracts numeric values for output. packages tree name in a Tree struct
//and passes as param for search. Recieves data as a list and interprets counts for output to screen
void printBoroCounts(list<string> &TreeNames, TreeCollection &Collection)
{
	int total_this_tree = 0, total_all_trees;
	double percent;
	string tree_name;

	int bronx_tree = 0, brooklyn_tree = 0, manhattan_tree = 0, nyc = 0, statenisland_tree = 0, queens_tree = 0, boro_total_tree;
	int bronx_all, brooklyn_all, manhattan_all, nyc_all, statenisland_all, queens_all;
	string bronx_str = "bronx", brooklyn_str = "brooklyn",  manhattan_str = "manhattan",  statenisland_str = "staten island", queens_str = "queens";
	
	list <string>::iterator iterFront = TreeNames.begin();
	while (iterFront != TreeNames.end())
	{
		list <Tree> AvlCount;
		tree_name = *iterFront;
		//pass tree_name to search funcs
		//Tree tree1(id, diam, status, health, spc, zip, boro, x, y);
		Tree Lost_Tree (0, 0, "", "", tree_name, 0, "", 0, 0 );//for search. empty tree with only spc_common populated
		AvlCount = Collection.AvlMatchTrees(Lost_Tree);//Calling search, AVL, for all instances of a tree. Returns a list of trees
		total_this_tree += Collection.count_of_tree_species(tree_name);
		iterFront++;
		list <Tree>::iterator AvlFront = AvlCount.begin();
		//gets counts by reading list for borough occurance only 
		while (AvlFront != AvlCount.end())
		{
			if (AvlFront->borough_name() == bronx_str)
				bronx_tree++;
			if (AvlFront->borough_name() == brooklyn_str)
				brooklyn_tree++;
			if (AvlFront->borough_name() == manhattan_str)
				manhattan_tree++;
			if (AvlFront->borough_name() == statenisland_str)
				statenisland_tree++;
			if (AvlFront->borough_name() == queens_str)
				queens_tree++;
			AvlCount.pop_front();
			AvlFront = AvlCount.begin();
		}
	}
	boro_total_tree = bronx_tree + brooklyn_tree + manhattan_tree + statenisland_tree + queens_tree;

	//these return as int, all trees in each borough, all species
	manhattan_all = Collection.count_of_trees_in_boro(manhattan_str);
	bronx_all = Collection.count_of_trees_in_boro(bronx_str);
	brooklyn_all = Collection.count_of_trees_in_boro(brooklyn_str);
	queens_all = Collection.count_of_trees_in_boro(queens_str);
	statenisland_all = Collection.count_of_trees_in_boro(statenisland_str);
	
	total_all_trees = Collection.total_tree_count();//grand total, all species
	////nyc_all value also counted on data intake and saved in a variable in Tree_Collection as tree_count to cross reference
	nyc_all = bronx_all + brooklyn_all + manhattan_all + statenisland_all + queens_all; //grand total, all species

	cout.setf(ios::fixed, ios::floatfield);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout << right;
	percent = (total_this_tree /(double)total_all_trees)*100;
	cout << "\t\tNYC:" << setw(21) << boro_total_tree << setw(9) << " (" << total_all_trees << ") " << setw(6) << percent << "%"<< endl;

	percent = (bronx_tree / (double)bronx_all) * 100;
	cout << "\t\tBronx:" << setw(19) << bronx_tree << setw(10) << " (" << bronx_all << ") " << setw(6) << percent << "%" << endl;

	percent = (brooklyn_tree / (double)total_all_trees) * 100;
	cout << "\t\tBrooklyn:" << setw(16) << brooklyn_tree << setw(9) << " (" << brooklyn_all << ") " << setw(6) << percent << "%" << endl;

	percent = (manhattan_tree / (double)manhattan_all) * 100;
	cout << "\t\tManhattan:" << setw(15) << manhattan_tree << setw(10) << " (" << manhattan_all << ") " << setw(6) << percent << "%" << endl;

	percent = (statenisland_tree / (double)statenisland_all) * 100;
	cout << "\t\tStaten Island:" << setw(11) << statenisland_tree << setw(10) << " (" << statenisland_all << ") " << setw(6) << percent << "%" << endl;

	percent = (queens_tree / (double)queens_all) * 100;
	cout << "\t\tQueens:" << setw(18) << queens_tree << setw(9) << " (" << queens_all << ") " << setw(6) << percent << "%" << endl;
}