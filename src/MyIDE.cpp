//============================================================================
// Name        : MyIDE.cpp
// Author      : Cole Paulline
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

class LexAnalyzer{
private:
	vector <string> lexemes;
	vector <string> tokens;
	map <string, string> tokenmap;

public:
	LexAnalyzer(istream& infile){
		if(!infile){
			cout << "could not open the file " << infile << endl;
			exit(-1);
		}
		string s;
		vector<string> temp;
		while(getline(infile, s)){
			istringstream ip(s);
			do{
				string word;
				ip >> word;
				temp.push_back(word);
			}while(ip);
			cout << temp.at(0) << " " << temp.at(1) << endl;
			tokenmap.insert(pair<string, string>(temp.at(1), temp.at(0)));
			temp.clear();
		}
	}

	void scanFile(istream& infile, ostream& outfile){
		if(!infile){
			cout << "could not open the file " << infile <<  endl;
			exit(-1);
		}
		int i = 0;
		string s;
		while(getline(infile, s)){

			//scan through the line stored in 's' to split keywords from symbols and integers

			i++;
		}

		cout << "file read successfully" << endl;
	}
};

int main() {
	cout << "Hello World" << endl; // prints Hello World
	ifstream infile("tokenlexemedata.txt");
	LexAnalyzer e(infile);


	return 0;
}
