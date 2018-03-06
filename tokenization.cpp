#include<iostream>
#include<fstream>
#include<istream>
#include<sstream>
#include<vector>
using namespace std;

int main() {
	vector <string> tokens;
	ifstream inputFile;
	inputFile.open("file.txt");
	string lines,words;

	while(getline(inputFile,lines)){
		istringstream inputLine(lines);
		
		while(getline(inputLine,words,' ')){
		//while(getline(cin,words)){
			tokens.push_back(words);


		}		

	}
	vector<string> :: iterator it;	
	
	for(it = tokens.begin(); it!=tokens.end(); it++){
		cout<<*it<<endl<<endl;
	}
	inputFile.close();
	
	

}
