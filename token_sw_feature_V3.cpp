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


	vector< vector<string> > documentCollection;  //whole document
	vector <string> tokens;
	//ifstream inputFile;
	iFile.open("Eclipse_summary.csv");
	//string lines,words;
    //string lines;
	int row = 0;
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
		documentCollection.push_back(tokens);
//tokens destroyed
		tokens.clear();

	}
	iFile.close();

	vector<string> :: iterator it;
	vector<string> :: iterator it2;
    cout<<"check "<<documentCollection.size()<<endl;
    int ct=0;
	for(int rw=0; rw<documentCollection.size(); rw++ ){
		for(it = documentCollection[rw].begin(); it!=documentCollection[rw].end(); it++){
			for(it2=stopWordList.begin(); it2!=stopWordList.end(); it2++){
				if(*it == *it2){
					documentCollection[rw].erase(it);
					it--;
				}
			}
		}

	}


	cout<<"\nfile word list after removing stopWord"<<endl;
	map< string, int> frequencyMap;
	map< string, int > tempFreq;
	vector< map<string,int> > rowMap;

	for(int rw=0;rw<documentCollection.size();rw++) {
		for(it = documentCollection[rw].begin(); it!=documentCollection[rw].end(); it++){
			frequencyMap[*it]++;
			tempFreq[*it]++;
		}
        rowMap.push_back(tempFreq);
        tempFreq.clear();
	}

//*********************************************************************
	mapSorter mS;
	vector<mapSorter> featureSort;
	for(map<string,int>::iterator i=frequencyMap.begin(); i != frequencyMap.end(); i++) {
		//cout<<i->first<<"	"<<i->second<<endl;
		mS.word = i->first;
		mS.frequency = i->second;
		featureSort.push_back(mS);

	}

	sort(featureSort.begin(),featureSort.end(), sortingRule );


// Feature selection


    cout<<"******************************************"<<endl<<endl;

	vector<string> feature1000;//features


	ct = 1;
	for(vector<mapSorter>::iterator i=featureSort.begin() ; i!=(featureSort.begin()+100) ; i++){

		//cout<<ct++<<". "<<(*i).word<<" : "<<(*i).frequency<<endl;
		feature1000.push_back( (*i).word );
	}

    for(int rw=0;rw<documentCollection.size();rw++){
        cout<<rw+1<<": "<<endl;
        for(vector<string>::iterator it = feature1000.begin(); it!=feature1000.end(); it++){
            //cout<< *it <<":"<<rowMap[rw][*it]<<" ";
            cout<<rowMap[rw][*it]<<" ";
        }
        cout<<endl;
    }





}
