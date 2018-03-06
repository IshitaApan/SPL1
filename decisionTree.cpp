#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<map>
using namespace std;

#define INPUT_FILE "data.txt"
//#define COLUMN
//#define ROW
map <string,int> indexMaping;
int main() {
    freopen(INPUT_FILE,"r",stdin);
// if row & column number is provided in data set
   /* int ROW,COLUMN;
    cin>>ROW>>COLUMN;*/
//else, will be defined ROW & COLUMN above
//or
    //calculate column
    int COLUMN=0;
    string line,words;
    getline(cin,line);
    istringstream iss(line);
    //cout<<"CHeck "<<line;
    while(getline(iss,words,',')){  
        COLUMN++;
    }

    //calculate row
    int ROW=1;
    while(getline(cin,line) ){
		//cout<<"CHeck"<<endl;        
		ROW++;
	}
		
//    fclose(INPUT_FILE);

    cout<<ROW<<" "<<COLUMN<<endl;
//if features name are provided in data set
    freopen(INPUT_FILE,"r",stdin);
    string *name_of_features;
    name_of_features = new string[COLUMN];
    for(int i = 0; i < COLUMN; i++){
		cin >> name_of_features[i];
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
}
