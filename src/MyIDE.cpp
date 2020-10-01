//============================================================================
// Name        : MyIDE.cpp
// Author      : Cole Paulline
// Version     :
// Copyright   : Your copyright notice
// Description : my compiler program in C++
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

	//containers for the program
	vector <string> lexemes;
	vector <string> tokens;
	map <string, string> tokenmap;

public:

	/*
	 * pre: parameter refers to an open data file consisting of token and
	 * lexeme pairs i.e. s_and and, t_begin begin, t_int 27. Each pair
	 * appears on its own input line.
	 * post: token map has been populated
	 */
	LexAnalyzer(istream& infile){
		if(!infile){
			cout << "could not open the file " << infile << endl;
			exit(-1);
		}
		string s;
		vector<string> temp;
		while(getline(infile, s)){
			istringstream ip(s);

			//passes in the token lexeme pairs into a temporary vector
			do{
				string word;
				ip >> word;
				temp.push_back(word);
			}while(ip);

			//moves the pairs from the vector into the map container
			tokenmap.insert(pair<string, string>(temp.at(1), temp.at(0)));
			temp.clear();
		}
	}

	/*
	 * pre: 1st parameter refers to an open text file that contains source
	 * code in the language, 2nd parameter refers to an open empty output
	 * file
	 * post: If no error, the token and lexeme pairs for the given input
	 * file have been written to the output file.  If there is an error,
	 * the incomplete token/lexeme pairs, as well as an error message have
	 * written to the output file.  A success or fail message has printed
	 * to the console.
	 */
	void scanFile(istream& infile, ostream& outfile){

		//checks to see if the file name is valid for input
		if(!infile){
			cout << "could not open the file " << infile <<  endl;
			exit(-1);
		}

		//checks to see if the file name is valid for output
		if(!outfile){
			cout << "could not open the file " << outfile << endl;
			exit(-1);
		}

		string s; //the current line variable
		string keyword = ""; //the keyword variable for later checking

		while(getline(infile, s)){
			keyword = "";

			//loop to scan every letter of the string
			for(int i = 0; i < s.length(); i++){

				//ignores the spaces in the line being passed in
				if(s[i] == ' '){
					continue;

				}else{

					//this branch checks for alphabetical characters for keywords
					if(isalpha(s[i])){
						keyword.push_back(s[i]);
						if(keycheck(keyword)){
							vectorAdd(keyword, tokenmap.at(keyword));
							keyword = "";

						//if it is not a key word then it is passed in as an id
						}else if(!lexemes.empty() and !isalpha(s[i+1])){
							vectorAdd(keyword, "t_id");
							keyword = "";
						}

					//this branch checks if it is an integer and if the next
					//is not another integer it adds it to the vectors
					}else if(isdigit(s[i])){
						keyword.push_back(s[i]);
						if(isdigit(s[i+1])){
							continue;
						}else{
							vectorAdd(keyword, "t_int");
							keyword = "";
						}

					//this branch is for adding strings and checks for the
					//quotation marks around a string
					}else if(s[i] == '\"'){
						int x = i+1;

						while(s[x] != '\"'){
							keyword.push_back(s[x]);
							x += 1;
							if(x == s.length()-1){
								cout << "there was an error, the string doesn't have and ending \"" << endl;
								exit(-1);
							}
						}
						i = x;
						vectorAdd(keyword, "t_str");
						keyword = "";

					//this last branch is for the symbols of the lexemes
					//and checks if there is another symbol next to it
					//in which they combine to make a different symbol
					//ex) = or ==
					}else{

						//Immediately pushes the symbol because that is the only
						//one left not checked
						keyword.push_back(s[i]);
						string temp = keyword + s[i+1];

						//if there is a symbol next to it that makes
						//a different lexeme then it is out in the vectors
						if(keycheck(temp)){
							vectorAdd(temp, tokenmap.at(temp));
							keyword = "";
							i += 1;

						//else it stores the original symbol found
						}else if(keycheck(keyword)){
							vectorAdd(keyword, tokenmap.at(keyword));
							keyword = "";
						}
					}
				}
			}
		}

		//the for loop goes through the token lexeme containers and prints them
		//to the out file
		for(int i = 0; i < lexemes.size(); i++){
			outfile << tokens.at(i) << " : " << lexemes.at(i) << endl;
		}
		cout << "file read successfully" << endl;
	}

	/*
	 * pre: the parameter is referring to the key that is being checked
	 * post: the function returns true if the key passed in exists in the
	 * 		 token map
	 */
	bool keycheck(string key){
		if(tokenmap.find(key) == tokenmap.end()){
			return false;
		}else{
			return true;
		}
	}

	/*
	 * pre: the 1st parameter refers to the lexeme that is being added
	 * 		to the lexeme vector
	 * 		the 2nd parameter refers to the token that is being added
	 * 		to the token vector
	 * post: the lexeme and token passed in are put into their corresponding
	 * 		 vector caches
	 */
	void vectorAdd(string lex, string tok){
		lexemes.push_back(lex);
		tokens.push_back(tok);
	}
};

int main() {

	//reads the file for the lexeme data
	ifstream infile("tokenlexemedata.txt");
	LexAnalyzer e(infile);
	infile.close();

	//asks the user for the input file name
	string input;
	cout << "please enter an input file name" << endl;
	cin >> input;
	infile.open(input);

	//asks the user for the output file name
	string output;
	cout << "please enter an output file name" << endl;
	cin >> output;
	ofstream outfile(output);

	//scans the files through the program then closes them out
	e.scanFile(infile, outfile);
	infile.close();
	outfile.close();
}
