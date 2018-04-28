#include<bits/stdc++.h>
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

}

