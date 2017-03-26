
/*
Author: Cordell Hurst
Course : CSCI 335 Software Design and Analysis III
Instructor: Stewart Weiss
Assignment 02

This program...
*/

#ifndef __Tree_H__
#define __Tree_H__

#include <iostream>
#include <string> 	//for string handling

using namespace std;

	
 

class Tree
{
public:
	Tree(int id, int diam, string status, string health,//DONE & Tested
		 string spc, int zip, string boro, double x, double y);//Still done & tested

	

	friend bool islessname(const Tree & t1, const Tree & t2);//DONE & Tested
	friend bool samename(const Tree & t1, const Tree & t2);//DONE & Tested
	friend bool operator==(const Tree & t1, const Tree & t2);//DONE & Tested
	friend bool operator<(const Tree & t1, const Tree & t2);//DONE & Tested
	friend ostream& operator<< (ostream & os, const Tree & t);//DONE & Tested
	friend string toLowerCase(const string & wordIn); //void toLowerCase(string &wordIn);
	friend void toLowerCase(string &wordIn); //void toLowerCase(string &wordIn);

	//Getters
	double diameter();//DONE & Tested
	string common_name();//DONE & Tested
	string borough_name();//DONE & Tested

private:
	double x_sp;		//x spatial coordinate specifying position in New York State state plane coordinates
	double y_sp;		//y spatial coordinate specifying position in New York State state plane coordinates

	int tree_id;		//a non - negative integer that uniquely identies the tree
	int tree_dbh;		//a non - negative integer specifying tree diameter
	int zipcode;		//a positive five digit integer. (This means that any number from 0 to 99999 is acceptable.
						//The values that are shorter should be treated as if they had leading zeroes, i.e., 
						//8608 represents zipcode 08608, 98 represents zip code 00098, etc.)
						//Strings case sensitive
	string boroname;	//valid values : Manhattan, Bronx, Brooklyn, Queens, Staten Island
	string health;		//a string, valid values : Good, Fair, Poor, or the empty string
	string spc_common;	//the common name of the tree, such as  white oak or a possibly empty string
	string status;		//a string, valid values : Alive, Dead, Stump, or the empty string
	

	
};

// A Tree object indicating no tree exists
const Tree  NO_TREE(0, 0, "", "", "", 0, "", 0, 0);


#endif /* __Tree_H__ */