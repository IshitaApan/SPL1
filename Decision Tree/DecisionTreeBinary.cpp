#include<bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace std;

#define DATA "bank.txt"
#define ROW row
#define COLUMN 5 //for bank.txt
//double **dataset;
struct data{
    vector<double>rowData;
};
vector<data> dataset;
string *header;


double calculateFeatureEntropy(){
    double Entropy;
    return Entropy;
}


double calculateTableEntropy(int number, int totalSize){
    double probability =(double)number/(double)totalSize ;
    double entropy = probability * log2(probability);
    return (-1)*entropy ;
}

void makeTree(int nodeNo,int nodeLevel,vector<data>dataset,string *header){
    double element;
    string elementHeader;
    for(int i=0;i<column;i++){
        elementHeader = header[i];
        for(int j=0;j<row;j++){
            element = dataset[j][i];


        }
    }
}

void cleanUpString(string &str){
    for(int i=0;i<str.size();i++)
        if(str[i]==',') str[i] = ' ';
}

void selectTrainData(){

}

void readFile(){
    freopen(DATA,"r",stdin);
    /*int ROW,COLUMN;
    cin >> row >> COLUMN; */
    header = new string[COLUMN];
    string str,strTemp;
    getline(cin,str);
    cleanUpString(str);
    istringstream iss(str);
    int i=0;
    while(iss>>strTemp){
        header[i++] = strTemp;
    }


    /*dataset=new double*[ROW];
    for(int i=0;i<ROW;i++)          //2D array nile
        dataset[i] = new double[COLUMN]; */
    double dTemp;
    int row=1;
    while(getline(cin,str)){
        row++;
        cleanUpString(str);
        istringstream iss(str);
        data rd;
        while(iss>>dTemp){
            rd.rowData.push_back(dTemp);
        }
        dataset.push_back(rd);
    }
    cout<<"Size of Dataset: "<<dataset.size()<<" Row: "<<ROW<<" Column: "<<COLUMN<<endl;

}
int main() {
    readFile();
    selectTrainData();
    /*for(int i=0;i<COLUMN;i++)
        cout<<header[i]<<" * ";
    cout<<endl;
    for(int i=0;i<5;i++){
        for(int j=0;j<COLUMN;j++){          //INPUT testing
            cout<<dataset[i][j]<<"  ";
        }
        cout<<endl;
    } */

    makeTree(0,0,dataset,header);

}
