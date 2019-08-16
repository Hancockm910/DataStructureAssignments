#include "FileReader.h"

void FileReader::print(DATA ss)
{
	cout << ss.key << "::" << ss.freq << ", ";
}

void FileReader::deleteLowFreq(int value)
{
}

void FileReader::removeLowFreq(int value)
{
	tree.AVL_LowFreq(value);
}

void FileReader::removeWord(string input)
{
	tree.AVL_Delete(input);
}



FileReader::FileReader()
{

}

FileReader::~FileReader()
{

}

void FileReader::readSingle()
{
	string word;
	ifstream wordFile;
	wordFile.open("textexample1.txt");
	if (wordFile.is_open())
	{

		while (wordFile >> word)
		{
			DATA data;
			data.key = processString(word);
			tree.AVL_Insert(data);
			word.clear();
		}
	}
	else
		cout << "Opening failed\n\n";
}

void FileReader::readMultiple(int NumberOfFiles)
{
	string word;
	NumberOfFiles++;
	string file = "textexample";
	string extension = ".txt";
	string filename;
	ifstream wordFile;
	for (int fileNumber = 1; fileNumber < NumberOfFiles; fileNumber++)
	{
		stringstream ss;
		ss << fileNumber;
		filename = file + ss.str() + extension;
		wordFile.open(filename);
		if (wordFile.is_open())
			cout << endl << filename << " opened.\n";
		else
			cout << endl << filename << " not opened.\n";
		while (wordFile >> word)
		{
			DATA data;
			data.key = processString(word);
			tree.AVL_Insert(data);
			word.clear();
		}
	}
	//printTree();
}

string FileReader::processString(string Input)
{
	Input.erase(remove_if(Input.begin(), Input.end(), &ispunct), Input.end());
	Input.erase(remove_if(Input.begin(), Input.end(), &isdigit), Input.end());
	transform(Input.begin(), Input.end(), Input.begin(), ::tolower);
	return Input;
}

void FileReader::treeToDictionary(DATA transfer)
{
	ofstream dictionary;
	dictionary.open("dictionary.txt", fstream::app);
	if (dictionary.is_open())
	{
		dictionary << transfer.key << " " << transfer.freq << "\n";
		dictionary.close();
	}
	else
		cout << "Dictionary failed to open.\n";
}

void FileReader::printTree(int input)
{
	if (input == 1)
	{
		tree.AVL_Traverse(print);
		cout << "Total words: " << tree.AVL_Count() << endl;
	}
	if (input == 2)
	{
		treeTwo.AVL_Traverse(print);
		cout << "Total words: " << treeTwo.AVL_Count() << endl;
	}
}

void FileReader::findWord(string input)
{
	char next = input[input.size() - 1];
	next++;
	string passed(1, next);

	tree.AVL_findWord(input, passed);
}

void FileReader::searchResults()
{
	priority_queue<DATA>printer;
	printer = tree.getSearchResult();
	cout << "\n\nSearch Results: " << endl;
	while (!printer.empty())
	{
		cout << printer.top().key << " " << printer.top().freq << endl;
		printer.pop();
	}
}

void FileReader::treeToClass()
{
	tree.AVL_Traverse(treeToDictionary);
}

void FileReader::chopTreeDown()
{
	tree.AVL_Destroy();
}

void FileReader::readFromDictionary()
{
	string word;
	int frequency;
	ifstream wordFile;
	wordFile.open("dictionary.txt");
	if (wordFile.is_open())
	{
		while (wordFile >> word >> frequency)
		{
			DATA data;
			data.key = processString(word);
			data.freq = frequency;
			treeTwo.AVL_Insert(data);
			word.clear();
		}
	}
	else
		cout << "Opening failed\n\n";
}

void FileReader::printEntireTree()
{
	tree.AVL_Print();
}
