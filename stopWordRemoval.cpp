#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

int main(){
	vector<string> stopWordList;
	ifstream iFile;
	iFile.open("stopWord.txt");
	char ch;
	string word;

	/*while(iFile>>ch){
		if(ch==','){
			//ch = ' ';
			iFile<<' ';
			continue;
		}
		//cout<<ch<<"	";
	} */
	while(iFile>>word){
		/*stringstream inputStr(word);
        while(inputStr>>ch){
            if(ch==','){
                inputStr<<' ';
            }
        }*/
        while()
		stopWordList.push_back(word);
		cout<<word<<endl;;
	}
	iFile.close();

}
