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
#include <locale>

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
			tokenmap.insert(pair<string, string>(temp.at(1), temp.at(0)));
			temp.clear();
		}
	}

	void scanFile(istream& infile, ostream& outfile){
		if(!infile){
			cout << "could not open the file " << infile <<  endl;
			exit(-1);
		}

		string s;
		string keyword = "";
		while(getline(infile, s)){
			keyword = "";
			s.erase(remove(s.begin(), s.end(), ' '), s.end());

			for(int i = 0; i < s.length(); i++){
				if(isalpha(s[i])){
					keyword.push_back(s[i]);
					if(keycheck(keyword)){
						outfile << tokenmap.at(keyword) << " : " << keyword << endl;
						keyword = "";

					}
				}else{
					keyword.push_back(s[i]);
					if(keycheck(keyword)){
						outfile << tokenmap.at(keyword) << " : " << keyword << endl;
						keyword = "";
					}else if(keyword.at(0) == '\"' and keyword.at(keyword.length()-1) == '\"' and keyword.length() != 1){
						outfile << "t_str : " << "hello World" << endl;
						keyword = "";
					}
				}
			}
		}
		cout << "file read successfully" << endl;
	}

	bool keycheck(string key){
		if(tokenmap.find(key) == tokenmap.end()){
			return false;
		}else{
			return true;
		}
	}
};

int main() {
	ifstream infile("tokenlexemedata.txt");
	LexAnalyzer e(infile);
	infile.close();
	infile.open("inputfile.txt");
	ofstream outfile("outputfile.txt");
	e.scanFile(infile, outfile);
	return 0;
}
