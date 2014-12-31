#include <iostream>     // std::cout
#include <fstream>		//read/write from/to file
#include <vector>       // std::vector
#include <algorithm>	//sort
#include <string>		//string
#include <stdlib.h>     /* srand, rand */
#include "War.h"
using namespace std;

void tournament(vector<string>& NameList,int win, ofstream& OutFile,vector<int>& Battles,vector<int>& ComeBack);

int main(int argc, char const *argv[]){
	if (argc!=3){
		cout<<"BAD # of arguements in command line!"<<endl;
		return 0;
	}
	srand((unsigned)time(0));
	vector<string> NameList;
	int n=0;
	int win=0;
	string temp;
	ifstream InFile(&argv[1][0]);
	while(getline(InFile,temp)){
		NameList.push_back(temp);
		n++;
	}
	//check # of names
	if (n<2){
		cout<<"Too few players."<<endl;
		return 0;
	}
	else{
		while(1){
			if(n==2){
				break;
			}
			else if (n%2==1){
				cout<<"BAD # of names. "<<endl;
				return 0;
			}
			else{n=n/2;}
		}
	}
	InFile.close();
	ofstream OutFile(&argv[2][0]);
	vector<int> Battles;
	vector<int> ComeBack;
	tournament(NameList,win,OutFile,Battles,ComeBack);
	OutFile.close();
	return 0;
}

void tournament(vector<string>& NameList,int win,ofstream& OutFile,vector<int>& Battles,vector<int>& ComeBack){
	int x=NameList.size();
	if (NameList.size()<2){
		cout<<NameList.front()<<" finally win!"<<endl;
		OutFile<<"==="<<endl;

		int a=0;
		for (vector<int>::iterator i = Battles.begin(); i != Battles.end(); ++i){
			a=a+(*i);
			//cout<<*i<<endl;
		}
		a=a/Battles.size();

		sort(Battles.begin(),Battles.end());
		sort(ComeBack.begin(),ComeBack.end());
		cout<<"Average # of battles: "<<a<<endl;
		cout<<"Largest # of battles: "<<Battles.back()<<endl;
		cout<<"Biggest comeback: "<<ComeBack.front()<<endl;

	}
	else{
		win++;
		for (int i = 0; i < x/2; i++){
			//cout<<"===\n"<<NameList.front()<<" vs. "<<NameList.at(1)<<endl;
			OutFile<<"===\n"<<NameList.front()<<" vs. "<<NameList.at(1)<<endl;
			if (War(NameList.front(),NameList.at(1),OutFile,win,Battles,ComeBack)==0){
				NameList.push_back(NameList.front());
				NameList.erase(NameList.begin());
				NameList.erase(NameList.begin());
			}
			else{
				NameList.erase(NameList.begin());
				NameList.push_back(NameList.front());
				NameList.erase(NameList.begin());
			}
		}
		tournament(NameList,win,OutFile,Battles,ComeBack);
	}
}