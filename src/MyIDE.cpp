//============================================================================
// Name        : MyIDE.cpp
// Author      : Cole Paulline
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class LexAnalyzer{
private:
	vector <string> lexemes;
	vector <string> tokens;
	map <string, string> tokenmap;

public:
	LexAnalyzer(istream& infile);

	void scanFile(istream& infile, ostream& outfile){
		if(!infile){
			cout << "could not open the file" << endl;
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
	return 0;
}
