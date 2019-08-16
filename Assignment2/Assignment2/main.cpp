#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip> 
#include <iterator>
#include <algorithm> 
#include <regex>
#include <stdio.h>  

using namespace std;
#include "FileReader.h"
#include "avlTree.h"

void menu(FileReader &fileR);
void secMenu(FileReader &fileR);
void searchDic(FileReader &fileR);
void deleteWord(FileReader &fileR);
void delLowFreq(FileReader &fileR);





int main() 
{
	FileReader FR;
	menu(FR);
	secMenu(FR);
	system("pause"); 
	return 0;
}

void menu(FileReader &fileR)
{
	cout << "MENU\n"
		<< "1: Load single file\n"
		<< "2: Load entire database\n";
	int option;
	cin >> option;
	
	if (option == 1)
	{
		fileR.readSingle();
	}
	else if (option == 2)
	{
		fileR.readMultiple(4);
	}
	else
		menu(fileR);
}
void secMenu(FileReader &fileR)
{
	system("CLS");
	cout << "MENU\n"
		<< "1: Print tree\n"
		<< "2: Print word list\n"
		<< "3: Find word\n"
		<< "4: Delete word\n"
		<< "5: Delete low frequency words\n"
		<< "6: Save dictionary to file\n"
		<< "00: Exit\n";
	int option = 0;
	cin >> option;

	if (option == 1)
	{
		fileR.printEntireTree();
	}
	else if (option == 2)
	{
		fileR.printTree(1);
		cin >> option;
		secMenu(fileR);
	}
	else if (option == 3)
	{
		searchDic(fileR);
	}
	else if (option == 4)
	{
		deleteWord(fileR);
	}
	else if (option == 5)
	{
		delLowFreq(fileR);
	}
	else if (option == 6)
	{
		fileR.treeToClass();
	}
	else if (option == 00)
	{
		return;
	}
	else
		secMenu(fileR);
}

void searchDic(FileReader &fileR)
{
	string word;
	while (word != "exit")
	{
		word.clear();
		system("CLS");
		fileR.searchResults();
		cout << "Enter word to search for.\n";
		cin >> word;
		fileR.findWord(word);
	}
}

void deleteWord(FileReader &fileR)
{
	string input;
	while (input != "exit")
	{
		system("CLS");
		fileR.printTree(1);
		cout << "\n\n Type 'exit' to leave.\n"
			<< "Enter word to delete.\n";
		fileR.removeWord(input);
	}
}

void delLowFreq(FileReader &fileR)
{
	system("CLS");
	cout << "Deleting low frequency words\n"
		<< "Enter desired threshold: ";
	int input;
	cin >> input;

	fileR.removeLowFreq(input);
	fileR.printTree(1);
}