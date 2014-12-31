#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <fstream>		//read/write from/to file
#include <stdlib.h>
#include "PlayingCard.h"
using namespace std;

int War(string Aname, string Bname, ofstream& OutFile,int win,vector<int>& Battles,vector<int>& ComeBack){
	PlayingCard cards[52];
	for (int i = 0; i < 13; i++){
		cards[i].setS('S');
		cards[i].setV(i+2);
		cards[13+i].setS('H');
		cards[13+i].setV(i+2);
		cards[26+i].setS('C');
		cards[26+i].setV(i+2);
		cards[39+i].setS('D');
		cards[39+i].setV(i+2);
	}
	
	random_shuffle(&cards[0], &cards[51]);

	vector<PlayingCard> Adeck;
	vector<PlayingCard> Bdeck;
	vector<PlayingCard> Mdeck;
	
	Adeck.assign(cards,cards+26);
	Bdeck.assign(cards+26,cards+52);

	int Wcount=0;
	int Bcount=0;

	vector<int> CardsInA;
	vector<int> CardsInB;
	
	while (1){
		Bcount++;
		if (Adeck.size()==0){
			Bcount--;
			//cout<<Bname<<"("<<win<<") DEFEATED "<<Aname<<" in "<<Bcount<<" Battles and "<<Wcount<<" Wars"<<endl;
			OutFile<<Bname<<"("<<win<<") DEFEATED "<<Aname<<" in "<<Bcount<<" Battles and "<<Wcount<<" Wars"<<endl;
			Battles.push_back(Bcount);
			sort(CardsInB.begin(),CardsInB.end());
			ComeBack.push_back(CardsInB.front());
			CardsInA.erase(CardsInA.begin(),CardsInA.end());
			CardsInB.erase(CardsInB.begin(),CardsInB.end());
			//cout<<"123"<<Battles.size();
			return 1;
		}
		if (Bdeck.size()==0){
			Bcount--;
			//cout<<Aname<<"("<<win<<") DEFEATED "<<Bname<<" in "<<Bcount<<" Battles and "<<Wcount<<" Wars"<<endl;
			OutFile<<Aname<<"("<<win<<") DEFEATED "<<Bname<<" in "<<Bcount<<" Battles and "<<Wcount<<" Wars"<<endl;
			Battles.push_back(Bcount);
			sort(CardsInA.begin(),CardsInA.end());
			ComeBack.push_back(CardsInA.front());
			CardsInA.erase(CardsInA.begin(),CardsInA.end());
			CardsInB.erase(CardsInB.begin(),CardsInB.end());
			//cout<<Battles.size();
			return 0;
		}
		if (Adeck.front()<Bdeck.front()){
			//cout<<"\tBattle "<<Bcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+1<<endl;
			OutFile<<"\tBattle "<<Bcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+1<<endl;
			CardsInA.push_back(Adeck.size()-1);
			CardsInB.push_back(Bdeck.size()+1);
			Bdeck.push_back(Bdeck.front());
			Bdeck.push_back(Adeck.front());
			Adeck.erase(Adeck.begin());
			Bdeck.erase(Bdeck.begin());
		}
		else if (Adeck.front()>Bdeck.front()){
			//cout<<"\tBattle "<<Bcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
			OutFile<<"\tBattle "<<Bcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
			CardsInA.push_back(Adeck.size()+1);
			CardsInB.push_back(Bdeck.size()-1);
			Adeck.push_back(Adeck.front());
			Adeck.push_back(Bdeck.front());
			Adeck.erase(Adeck.begin());
			Bdeck.erase(Bdeck.begin());
		}
		else{
			//cout<<"\tBattle "<<Bcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;
			OutFile<<"\tBattle "<<Bcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;

			while(Adeck.front()==Bdeck.front()){
				Wcount++;
				if (Adeck.size()<5){
					if (Bdeck.size()<5){
						//cout<<"A<4, B<4"<<endl;
						Mdeck.insert(Mdeck.end(),Adeck.begin(),Adeck.end()-1);
						Mdeck.insert(Mdeck.end(),Bdeck.begin(),Bdeck.end()-1);
						Adeck.erase(Adeck.begin(),Adeck.end()-1);
						Bdeck.erase(Adeck.begin(),Adeck.end()-1);
						if (Adeck.front()<Bdeck.front()){
							//cout<<"\tWar "<<Wcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+Mdeck.size()+1<<endl;
							OutFile<<"\tWar "<<Wcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+Mdeck.size()+1<<endl;
							CardsInA.push_back(Adeck.size()-1);
							CardsInB.push_back(Bdeck.size()+Mdeck.size()+1);
							Bdeck.push_back(Bdeck.front());
							Bdeck.push_back(Adeck.front());
							Adeck.erase(Adeck.begin());
							Bdeck.erase(Bdeck.begin());
							Bdeck.insert(Bdeck.end(),Mdeck.begin(),Mdeck.end());
							Mdeck.erase(Mdeck.begin(),Mdeck.end());
							break;
						}
						else if (Adeck.front()>Bdeck.front()){
							//cout<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+Mdeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
							OutFile<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+Mdeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
							CardsInA.push_back(Adeck.size()+Mdeck.size()+1);
							CardsInB.push_back(Bdeck.size()-1);
							Adeck.push_back(Adeck.front());
							Adeck.push_back(Bdeck.front());
							Adeck.erase(Adeck.begin());
							Bdeck.erase(Bdeck.begin());
							Adeck.insert(Adeck.end(),Mdeck.begin(),Mdeck.end());
							Mdeck.erase(Mdeck.begin(),Mdeck.end());
							break;
						}
						else{
							//cout<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;
							OutFile<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;
						}
					}
					else{
						//cout<<"A<4, B>4"<<endl;
						Mdeck.insert(Mdeck.end(),Adeck.begin(),Adeck.end()-1);
						Mdeck.insert(Mdeck.end(),Bdeck.begin(),Bdeck.begin()+4);
						Adeck.erase(Adeck.begin(),Adeck.end()-1);
						Bdeck.erase(Bdeck.begin(),Bdeck.begin()+4);
						if (Adeck.front()<Bdeck.front()){
							//cout<<"\tWar "<<Wcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+Mdeck.size()+1<<endl;
							OutFile<<"\tWar "<<Wcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+Mdeck.size()+1<<endl;
							CardsInA.push_back(Adeck.size()-1);
							CardsInB.push_back(Bdeck.size()+Mdeck.size()+1);
							Bdeck.push_back(Bdeck.front());
							Bdeck.push_back(Adeck.front());
							Adeck.erase(Adeck.begin());
							Bdeck.erase(Bdeck.begin());
							Bdeck.insert(Bdeck.end(),Mdeck.begin(),Mdeck.end());
							Mdeck.erase(Mdeck.begin(),Mdeck.end());
							break;
						}
						else if (Adeck.front()>Bdeck.front()){
							//cout<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+Mdeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
							OutFile<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+Mdeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
							CardsInA.push_back(Adeck.size()+Mdeck.size()+1);
							CardsInB.push_back(Bdeck.size()-1);
							Adeck.push_back(Adeck.front());
							Adeck.push_back(Bdeck.front());
							Adeck.erase(Adeck.begin());
							Bdeck.erase(Bdeck.begin());
							Adeck.insert(Adeck.end(),Mdeck.begin(),Mdeck.end());
							Mdeck.erase(Mdeck.begin(),Mdeck.end());
							break;
						}
						else{
							//cout<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;
							OutFile<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;
						}
						break;
					}
				}
				else if(Bdeck.size()<5){
					//cout<<"A>4, B<4"<<endl;
					Mdeck.insert(Mdeck.end(),Adeck.begin(),Adeck.begin()+4);
					Mdeck.insert(Mdeck.end(),Bdeck.begin(),Bdeck.end()-1);
					Adeck.erase(Adeck.begin(),Adeck.begin()+4);
					Bdeck.erase(Bdeck.begin(),Bdeck.end()-1);
					if (Adeck.front()<Bdeck.front()){
						//cout<<"\tWar "<<Wcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+Mdeck.size()+1<<endl;
						OutFile<<"\tWar "<<Wcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+Mdeck.size()+1<<endl;
						CardsInA.push_back(Adeck.size()-1);
						CardsInB.push_back(Bdeck.size()+Mdeck.size()+1);
						Bdeck.push_back(Bdeck.front());
						Bdeck.push_back(Adeck.front());
						Adeck.erase(Adeck.begin());
						Bdeck.erase(Bdeck.begin());
						Bdeck.insert(Bdeck.end(),Mdeck.begin(),Mdeck.end());
						Mdeck.erase(Mdeck.begin(),Mdeck.end());
						break;
					}
					else if (Adeck.front()>Bdeck.front()){
						//cout<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+Mdeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
						OutFile<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+Mdeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
						CardsInA.push_back(Adeck.size()+Mdeck.size()+1);
						CardsInB.push_back(Bdeck.size()-1);
						Adeck.push_back(Adeck.front());
						Adeck.push_back(Bdeck.front());
						Adeck.erase(Adeck.begin());
						Bdeck.erase(Bdeck.begin());
						Adeck.insert(Adeck.end(),Mdeck.begin(),Mdeck.end());
						Mdeck.erase(Mdeck.begin(),Mdeck.end());
						break;
					}
					else{
						//cout<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;
						OutFile<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;
					}
					break;
				}
				else{
					Mdeck.insert(Mdeck.end(),Adeck.begin(),Adeck.begin()+4);
					Mdeck.insert(Mdeck.end(),Bdeck.begin(),Bdeck.begin()+4);
					Adeck.erase(Adeck.begin(),Adeck.begin()+4);
					Bdeck.erase(Bdeck.begin(),Bdeck.begin()+4);
					if (Adeck.front()<Bdeck.front()){
						//cout<<"\tWar "<<Wcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+Mdeck.size()+1<<endl;
						OutFile<<"\tWar "<<Wcount<<": "<<Bname<<" ("<<Bdeck.front()<<") defeated "<<Aname<<" ("<<Adeck.front()<<"): "<<Aname<<" "<<Adeck.size()-1<<", "<<Bname<<" "<<Bdeck.size()+Mdeck.size()+1<<endl;
						CardsInA.push_back(Adeck.size()-1);
						CardsInB.push_back(Bdeck.size()+Mdeck.size()+1);
						Bdeck.push_back(Bdeck.front());
						Bdeck.push_back(Adeck.front());
						Adeck.erase(Adeck.begin());
						Bdeck.erase(Bdeck.begin());
						Bdeck.insert(Bdeck.end(),Mdeck.begin(),Mdeck.end());
						Mdeck.erase(Mdeck.begin(),Mdeck.end());
						break;
					}
					else if (Adeck.front()>Bdeck.front()){
						//cout<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+Mdeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
						OutFile<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") defeated "<<Bname<<" ("<<Bdeck.front()<<"): "<<Aname<<" "<<Adeck.size()+Mdeck.size()+1<<", "<<Bname<<" "<<Bdeck.size()-1<<endl;
						CardsInA.push_back(Adeck.size()+Mdeck.size()+1);
						CardsInB.push_back(Bdeck.size()-1);
						Adeck.push_back(Adeck.front());
						Adeck.push_back(Bdeck.front());
						Adeck.erase(Adeck.begin());
						Bdeck.erase(Bdeck.begin());
						Adeck.insert(Adeck.end(),Mdeck.begin(),Mdeck.end());
						Mdeck.erase(Mdeck.begin(),Mdeck.end());
						break;
					}
					else{
						//cout<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;
						OutFile<<"\tWar "<<Wcount<<": "<<Aname<<" ("<<Adeck.front()<<") tied "<<Bname<<" ("<<Bdeck.front()<<")"<<endl;
					}
				}	
			}
		}
	}
}
