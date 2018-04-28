#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<cmath>
#include<sstream>
#include<map>
using namespace std;

//#define DATA "data1.txt"
//#define DATA "w.csv"
//#define DATA "wine.csv"
//#define DATA "data2.txt"
#define DATA "bank.txt"
//#define ROW row
#define COLUMN 5 //for bank.txt
//#define COLUMN 12 //for w.csv
//#define COLUMN 14 //for wine.csv
#define MAXNODE 1000000
//double **dataset;
struct data{
    vector<double>rowData;
};
vector<data> dataset;
//vector<data> trainingDataset;
vector<data> testDataset;


string *header;

struct Node{
    bool isLeaf = false;
    int n = 0;
    double value = 0.0;
    int ans = 0;
    int leftNode;
    int rightNode;
}nodes[MAXNODE];


int ROW=1;

double calculateTableEntropy(int number, int totalSize){
    double probability =(double)number/(double)totalSize ;
    double entropy = probability * log2(probability);
    return (-1)*entropy ;
}


double calculateFeatureEntropy(double element,int col,vector<data>dataset){
    double Entropy;
    map<int,int> leftDataset,rightDataset;
    int leftDataCt=0,rightDataCt=0;
    for(int i=0;i<dataset.size();i++){
        if(dataset[i].rowData[col]<=element){
            leftDataset[(int)dataset[i].rowData[COLUMN-1]]++;
           // cout<<"%%%%%"<<endl;
            leftDataCt++;
        }
        else{
            rightDataset[(int)dataset[i].rowData[COLUMN-1]]++;
            rightDataCt++;
        }
    }

    double leftEntropy = 0.0, rightEntropy = 0.0;
    for(auto it = leftDataset.begin(); it != leftDataset.end(); it++){
        leftEntropy += (double) calculateTableEntropy(it -> second, leftDataCt);
    }
    leftEntropy *= leftDataCt;
    leftEntropy /= (double)dataset.size();

    for(auto it = rightDataset.begin(); it != rightDataset.end(); it++){
        rightEntropy += (double) calculateTableEntropy(it -> second, rightDataCt);
    }
    rightEntropy *= rightDataCt;
    rightEntropy /= (double)dataset.size();

    Entropy = leftEntropy+rightEntropy;

    return Entropy;
}


int nodeCt = 0;
int treeHeight = 0;
void makeTreeRecursively(int nodeNo,int nodeLevel,vector<data>dataset){
    double totalEntropy=0.0;
    treeHeight = max(treeHeight,nodeLevel);
    map<int,int> decisions;
    int decisionClass=-1;
    int mx=-1;
    for(int i=0;i<dataset.size();i++){
        int decision = (int)dataset[i].rowData[COLUMN-1];
        decisions[decision]++;
        if(decisions[decision]>mx){
            mx = decisions[decision];
            decisionClass = decision;
        }
    }

    for(auto it = decisions.begin();it!=decisions.end();it++){
        //cout<<"Class: "<<it->first<<" "<<it->second<<endl;
        totalEntropy += calculateTableEntropy(it->second, dataset.size());
    }
    if(totalEntropy<0.00000001){
        nodes[nodeNo].isLeaf = true;
        nodes[nodeNo].ans = decisionClass;
        nodes[nodeNo].value = 0.0;
        return;
    }
    double entropy = 0.0;
    double mn = 1e17;
    double element,value = 0.0;
    int ans=-1;
    string elementHeader;

    for(int i=0;i<COLUMN-1;i++){
        //elementHeader = header[i];
        for(int j=0;j<dataset.size();j++){
            element = dataset[j].rowData[i];
            entropy = calculateFeatureEntropy(element,i,dataset);
            if(entropy<mn){
                mn = entropy;
                ans = i; //header[i]; jodi header sting hoy tobe header[i]
                value = element;
            }
        }
    }
    nodes[nodeNo].isLeaf = false;
    nodes[nodeNo].n = ans;
    nodes[nodeNo].value = value;
    nodeCt++;
    nodes[nodeNo].leftNode = nodeCt;
    nodeCt++;
    nodes[nodeNo].rightNode = nodeCt;

    vector<data> leftDataset,rightDataset;
    int leftDataCt=0,rightDataCt=0;
    for(int i=0;i<dataset.size();i++){
        if(dataset[i].rowData[ans]<=value){
            leftDataset.push_back(dataset[i]);
            leftDataCt++;
        }
        else{
            rightDataset.push_back(dataset[i]);
            rightDataCt++;
        }
    }
    makeTreeRecursively(nodes[nodeNo].leftNode,nodeLevel+1,leftDataset);

    makeTreeRecursively(nodes[nodeNo].rightNode,nodeLevel+1,rightDataset);

}

int checkDecision(int node, data dd){
    if(nodes[node].isLeaf){
        return nodes[node].ans;
    }
    else if(dd.rowData[nodes[node].n] <=(nodes[node].value)){
        return checkDecision(nodes[node].leftNode,dd);
    }
    else{
        return checkDecision(nodes[node].rightNode,dd);
    }
}


void cleanUpString(string &str){
    for(int i=0;i<str.size();i++)
        if(str[i]==',') str[i] = ' ';
}

void selectTrainDataRandomly(vector<data> &dataset,vector<data> &testDataset){
    int totSize = dataset.size();
    totSize = totSize*2;
    totSize = totSize/10;

    while(totSize--){
        int value = rand() % dataset.size();
        testDataset.push_back(dataset[value]);
        dataset.erase(dataset.begin()+value);
        cout<<value<<endl;
    }

}


int main() {
    readFile();

    selectTrainDataRandomly(dataset,testDataset);
   cout<<"Now new size of dataset : "<<dataset.size()<<endl;
   cout<<"Now size of test dataset : "<<testDataset.size()<<endl;
    /*for(int i=0;i<COLUMN;i++)
        cout<<header[i]<<" * ";
    cout<<endl;
    for(int i=0;i<5;i++){
        for(int j=0;j<COLUMN;j++){          //INPUT testing
            cout<<dataset[i][j]<<"  ";
        }
        cout<<endl;
    } */

    makeTreeRecursively(0,0,dataset);
    cout<<"Total nodes of the tree: "<<nodeCt<<endl;
    cout<<"Height of the tree: "<<treeHeight<<endl;
      //cout<<"************"<<endl;
    int result=-1;
    int correctCt=0;
    for(int i=0;i<testDataset.size();i++){
        result=checkDecision(0,testDataset[i]);
       // cout<<"### Test No "<<i+1<<":\n";
        //cout<<"Test decision: "<<result<<endl;
        //cout<<"Actual decision: "<<(int)testDataset[i].rowData[COLUMN-1] <<endl;
        //cout<<endl;
        if(result==testDataset[i].rowData[COLUMN-1]) correctCt++;
    }
    cout<<"Total test: "<< testDataset.size() <<endl;
    cout<<"Total correct result: "<< correctCt <<endl;
    cout<<"accuracy : "<<(double)correctCt/(double)testDataset.size()<<endl;
    //int t = getchar();

}

