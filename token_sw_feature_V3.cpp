#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
struct mapSorter{
	string word;
	int frequency;

};

bool sortingRule(const mapSorter& a ,const mapSorter& b)
{
	return a.frequency > b.frequency;
}

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
	iFile.open("sample_dev0.txt");
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
	map< string, int> frequencyMap;
	for(it = tokens.begin(); it!=tokens.end(); it++){
		frequencyMap[*it]++;		
			//cout<<*it<<"		";
	}
//*********************************************************************
	mapSorter mS;	
	vector<mapSorter> feature;
	for(map<string,int>::iterator i=frequencyMap.begin(); i != frequencyMap.end(); i++) {
		//cout<<i->first<<"	"<<i->second<<endl;
		mS.word = i->first;
		mS.frequency = i->second;
		feature.push_back(mS);

	}

	sort(feature.begin(),feature.end(), sortingRule );


// Feature selection


cout<<"******************************************"<<endl<<endl;
	int ct = 1;
	for(vector<mapSorter>::iterator i=feature.begin() ; i!=feature.end() ; i++){

		cout<<ct++<<". "<<(*i).word<<" : "<<(*i).frequency<<endl;
	}
	


}
