#include <string>
using namespace std;

class PlayingCard{
private:
	char suit;
	int value;
public:
	PlayingCard();
	~PlayingCard();
	void setS(char s);
	void setV(int v);
	string outV();
	bool operator<(const PlayingCard& c);
	bool operator>(const PlayingCard& c);
	bool operator==(const PlayingCard& c);
	friend ostream &operator<<(ostream &output, const PlayingCard &c);
};