#include "PlayingCard.h"
#include <string>
#include <iostream>
using namespace std;


PlayingCard::PlayingCard(){}
PlayingCard::~PlayingCard(){}
void PlayingCard::setS(char s){
	suit=s;
}
void PlayingCard::setV(int v){
	value=v;
}

string PlayingCard::outV(){
	string out;
	if (value==14){
		out="A";
	}
	else if (value==13){
		out="K";
	}
	else if (value==12){
		out="Q";
	}
	else if (value==11){
		out="J";
	}
	else if (value==10){
		out="10";
	}
	else{out=value+48;}
	return out;

}

bool PlayingCard::operator<(const PlayingCard& c){
	if(value<c.value){return 1;}
	else{return 0;}
}
bool PlayingCard::operator>(const PlayingCard& c){
	if(value>c.value){return 1;}
	else{return 0;}
}
bool PlayingCard::operator==(const PlayingCard& c){
	if(value==c.value){return 1;}
	else{return 0;}
}
ostream &operator<<(ostream &output, const PlayingCard &c){
	PlayingCard x=c;
	output<<x.outV()<<x.suit;
    return output;
}