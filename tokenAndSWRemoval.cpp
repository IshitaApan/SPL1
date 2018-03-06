#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
using namespace std;

void cleanUp(string &s){
	int i=0;
	while(i!=s.length()){
		if(s[i]>='A' && s[i]<='Z'){
            s[i] = s[i]+32;
		}
		else if(s[i]<'A' || (s[i]>'Z' && s[i]<'a') || s[i]>'z'){
			s[i]=' ';

		}
		i++;
	}
}

int main(){
	vector<string> stopWordList;
	ifstream iFile;
	iFile.open("stopWord.txt");
	string line,word;

	while(getline(iFile,line)){
		cleanUp(line);
		istringstream iLine(line);
		while(iLine>>word){
			stopWordList.push_back(word);
			//cout<<word<<endl;

		}
	}
	iFile.close();
	vector <string> tokens;
	//ifstream inputFile;
	iFile.open("file.txt");
	//string lines,words;
    //string lines;
	while(getline(iFile,line)){
		//cout<<line<<endl;
		cleanUp(line);
		//cout<<line<<endl;
		istringstream iLine(line);
		while(iLine>>word){
		//while(getline(cin,words)){
			//cout<<word<<endl;
			tokens.push_back(word);


		}

	}
	iFile.close();

	vector<string> :: iterator it;
	vector<string> :: iterator it2;
    cout<<"check"<<endl;
    //int ct=0;
	for(it = tokens.begin(); it!=tokens.end(); it++){
		for(it2=stopWordList.begin(); it2!=stopWordList.end(); it2++){
			if(*it == *it2){
				//cout<<ct++<<*it<<endl;
				tokens.erase(it);
				it--;
				//break;
			}
		}
	}
	cout<<"\nfile word list after removing stopWord"<<endl;
	for(it = tokens.begin(); it!=tokens.end(); it++){
		cout<<*it<<"		";
	}

}
