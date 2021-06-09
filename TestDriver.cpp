// modified version of SingleLinkListExamples.cpp into the required test driver

#include "ChonkList.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	ofstream outFile;
	ifstream inFile;
	ChonkList<int> myList;

	outFile.open("output.txt");
	inFile.open("lil_test.txt");

	if (!inFile) {
		cout << "File not found!" << endl;
		exit(0);
	}

	string command;
	inFile >> command;
	while (command != "quit") {
		if (command == "append") {
			int num;
			inFile >> num;
			myList.Append(num);
			outFile << "Appending " << num << endl;
		}

		else if (command == "remove") {
			int num;
			inFile >> num;
			myList.Remove(num);
			outFile << "Removing " << num << endl;
		}
		/*

		else if (command == "insert") {
			int before, after;
			inFile >> before >> after;
			//myList.InsertAfter(before, after);
			outFile << "Inserting " << after << " after " << before << endl;
		}
		*/
		
		else if (command == "print") {
			myList.Print();
			for (int i = 0; i < myList.GetLength(); i++)
				outFile << *myList.GetIndex(i) << " ";
			outFile << "\n";
		}	

		else if (command == "search") {
			int num;
			inFile >> num;
			int* val = myList.Search(num);
			if (val == nullptr) {
				outFile << *val << " does not exist in list" << endl;
			}
			else {
				outFile << *val << " exists in list" << endl;
			}
		}
		else if (command == "getindex") {
			int num;
			inFile >> num;
			int* val = myList.GetIndex(num);
			if (val == nullptr) {
				outFile << *val << " does not exist in list" << endl;
			}
			else {
				outFile << *val << " exists in index " << num << endl;
			}
		}

		else if (command == "getlength") {
			outFile << "Length: " << myList.GetLength() << endl;
		}
		
		else if (command == "quit") {
			return 0;
		}
		inFile >> command;
	}
	return 0;
}