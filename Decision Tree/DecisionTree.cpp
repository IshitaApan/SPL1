#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<map>
using namespace std;

#define INPUT_FILE "data.txt"

map <string,int> indexMaping;

double calculateEntropy(int total, vector<string>classDecision){
    double entropy = 0.0;
    vector<string>:: iterator it;
    map<string, int> ct;
    map<string, bool> previouslyTaken;
    vector<string> values;
    for(int i=0;i<total;i++){
        if(!previouslyTaken[classDecision[i]]){
    	 values.push_back(classDecision[i]);
    	 previouslyTaken[classDecision[i]] = true;
    	}
        ct[classDecision[i]]++;
    }
    if(values.size() == 1) return 0;
    for(int i = 0; i < values.size(); i++)
    {
    	double probability = (double) ct[values[i]]/total;
    	entropy += probability * log2(probability);
    }
    entropy = entropy*(-1);
    return entropy;
}
void buildTree(int row,int column,string **table){
    vector<string> classDecision;
    for(int i=0; i<row; i++)
    	classDecision.push_back(table[i][column - 1]); // if the decision of a class is in the last column
    double entropy = calculateEntropy(row, classDecision);
}
int main() {
    freopen(INPUT_FILE,"r",stdin);
// if row & column number is provided in data set
   /* int ROW,COLUMN;
    cin>>ROW>>COLUMN;*/
//else calculate row & column
    int COLUMN=0;
    string line,words;
    getline(cin,line);
    istringstream iss(line);
    while(getline(iss,words,',')){
        COLUMN++;
    }
    int ROW=1;
    while(getline(cin,line) )
        ROW++;
//    fclose(INPUT_FILE);

    cout<<ROW<<" "<<COLUMN<<endl;
//if features name are provided in data set
    freopen(INPUT_FILE,"r",stdin);
    string *name_of_features;
    name_of_features = new string[COLUMN];
    for(int i = 0; i < COLUMN; i++){
		cin >> name_of_features[i];
		cout<<name_of_features[i]<<endl;
		indexMaping[name_of_features[i]] = i;
	}
//else
 /*   for(int i = 0; i < COLUMN; i++){
		name_of_features[i]='A'+i;
		indexMaping[name_of_features[i]] = i;
	}
 */
	string **table;
	table = new string*[ROW];
	for(int i=0;i<ROW;i++)
        table[i] = new string[COLUMN];

	for(int i=0; i<ROW; i++)
    	for(int j=0; j <COLUMN; j++)
    		cin >> table[i][j];

    buildTree(ROW,COLUMN,table);
}
