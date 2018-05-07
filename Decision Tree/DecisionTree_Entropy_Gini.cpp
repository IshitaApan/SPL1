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

struct data{
    vector<double>rowData;
};
vector<data> dataset;

vector<data> testDataset;

int choice;

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
    for(map<int,int>:: iterator it = leftDataset.begin(); it != leftDataset.end(); it++){
        leftEntropy += (double) calculateTableEntropy(it -> second, leftDataCt);
    }
    leftEntropy *= leftDataCt;
    leftEntropy /= (double)dataset.size();

    for(map<int,int>:: iterator it = rightDataset.begin(); it != rightDataset.end(); it++){
        rightEntropy += (double) calculateTableEntropy(it -> second, rightDataCt);
    }
    rightEntropy *= rightDataCt;
    rightEntropy /= (double)dataset.size();

    Entropy = leftEntropy+rightEntropy;

    return Entropy;
}



//??????????????????????????????????????????????




double calculateGiniIndex(int number, int totalSize){
    double probability =(double)number/(double)totalSize ;
    double gini = probability * probability;
    //gini = 1 - gini;
    return gini;
}

double calculateFeatureGini(double element,int col,vector<data>dataset){

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

    //double leftEntropy = 0.0, rightEntropy = 0.0;
    double leftGini = 0.0, rightGini = 0.0;
    for(map<int,int>:: iterator it = leftDataset.begin(); it != leftDataset.end(); it++){
        //leftEntropy += (double) calculateTableEntropy(it -> second, leftDataCt);
        leftGini += (double) calculateGiniIndex(it -> second, leftDataCt);
    }
   // leftEntropy *= leftDataCt;
    //leftEntropy /= (double)dataset.size();
    leftGini = 1 - leftGini;

    for(map<int,int>:: iterator it = rightDataset.begin(); it != rightDataset.end(); it++){
        rightGini += (double) calculateGiniIndex(it -> second, rightDataCt);
    }
    //rightEntropy *= rightDataCt;
    //rightEntropy /= (double)dataset.size();
    rightGini = 1-rightGini;

    leftGini = (leftGini * (double)leftDataCt)/(double)dataset.size();
    rightGini = (rightGini * (double)rightDataCt)/(double)dataset.size();
    double averageChildrenGini = leftGini+rightGini;

    return averageChildrenGini;
}





//????????????????????????????????????????????????????????????????



int nodeCt = 0;
int treeHeight = 0;
void makeTreeRecursively(int nodeNo,int nodeLevel,vector<data>dataset){
    double totalEntropy=0.0;
	// entropy
	double giniIndex = 0.0;
	// gini    
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

    for(map<int,int>:: iterator it = decisions.begin();it!=decisions.end();it++){
        //cout<<"Class: "<<it->first<<" "<<it->second<<endl;
        if(choice==0) totalEntropy += calculateTableEntropy(it->second, dataset.size());
//entropy
        else if(choice) giniIndex += calculateGiniIndex(it->second, dataset.size());
//gini    
	}
    double ParentGini = 1 - giniIndex;
    // if total entropy tends to 0 or less than 0, it means probability of being one class tends to 1,
    //so the leaf will be that class of highest probability
    if(( choice==1 && ParentGini <0.00000001)||( choice==0 && totalEntropy <0.00000001)){
        nodes[nodeNo].isLeaf = true;
        nodes[nodeNo].ans = decisionClass;
        nodes[nodeNo].value = 0.0;
        return;
    }
//////////////////////////////////////////////////////////////////////////
    double InfoGain = 0.0;
//entropy
    double mn = 1e17;
    double element,value = 0.0;
    int ans=-1;
    string elementHeader;

    for(int i=0;i<COLUMN-1;i++){
        //elementHeader = header[i];
        for(int j=0;j<dataset.size();j++){
            element = dataset[j].rowData[i];

			if(choice == 0) InfoGain = calculateFeatureEntropy(element,i,dataset);
            else if(choice) InfoGain = calculateFeatureGini(element,i,dataset);////////////////
//Gini

            if(InfoGain < mn){
                mn = InfoGain ;
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
       // cout<<value<<endl;
    }

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
    while(getline(cin,str)){
        ROW++;
        cleanUpString(str);
        istringstream iss(str);
        data rd;
        while(iss>>dTemp){
            rd.rowData.push_back(dTemp);
        }
        dataset.push_back(rd);
    }
    cout<<"Size of Dataset: "<<dataset.size()<<" Row: "<<ROW<<" Column: "<<COLUMN<<endl;
	
	fclose(stdin);

}

int main() {
    readFile();

    selectTrainDataRandomly(dataset,testDataset);
	cout<<"****************************"<<endl<<endl;
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

	cout<<"Enter Choice:\n0.Entropy\n1.Gini Index\n";

		
	cin>>choice;

	if(!choice) cout<<"Entropy based classification"<<endl;
	else if(choice==1) cout<<"Gini index based classification"<<endl;
	else{
		cout<<"Enter a valid choice"<<endl;
		return 1;
	}

    makeTreeRecursively(0,0,dataset);
    cout<<"****************************"<<endl<<endl;
    cout<<"Total nodes of the tree: "<<nodeCt<<endl;
    cout<<"Height of the tree: "<<treeHeight<<endl;
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


