// C++ OOP. Lesson 6 homework
// Author: Stepan Istomin

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <Windows.h> //for SetConsole

// Task 1
bool is_digit(const char* S) {
    const char* temp = "0123456789-+";
    unsigned point_count = 0;

    for (int i = 0; i < strlen(S); i++) {
        if ((i > 0) && (S[i] == '+' || S[i] == '-')) return false;
        if (S[i] == '.') {
            point_count++;
            if (point_count > 1) return false;
        }
        if (!strchr(temp, S[i])) return false;
    }
    return true;
}
// Task 2
std::ostream &endll(std::ostream &stream)
{
    stream << "\n" << "\n" << std::flush;
    return stream;
}
// Task 3,4,5
enum Suit {
	DIAMONDS,	// Бубны
	CLUBS,		// Трефы
	HEARTS,		// Червы
	SPADES		// Пики
};
enum CardName {
	ACE = 1,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING
};


class Card
{
public:
	Card(Suit _suit, CardName _name) : suit(_suit), name(_name) {};
	void Flip() {
		state = !state;
	}
	int GetValue() {
		if (!state) return 0;
		else if (name < 11) return name;
		else return 10;
	}
	friend std::ostream& operator<<(std::ostream& os, const Card& _Card); // task 5
private:
	Suit suit;
	CardName name;
	bool state = 1; // 0 - card face down, 1 - card face up
};
class Hand
{
public:
	Hand() {};
	void Add(Card* _card) { hand.push_back(_card); }
	void Clear() {
		std::vector<Card*>::iterator iter = hand.begin();
		for (iter = hand.begin(); iter != hand.end(); ++iter)
		{
			delete* iter;
			*iter = 0;
		}
		hand.clear();
	}
	int GetValue() const{
		if (hand.empty())
			return 0;
		if (hand.size()) {
			size_t sum = 0;
			size_t aceCount = 0;
			for (size_t i = 0; i < hand.size(); i++) //Calculating points without aces 
			{
				if (hand[i]->GetValue() == ACE) // If card is ace
					aceCount++;
				else
					sum += hand[i]->GetValue(); // Any card other than an ace 
			}
			for (aceCount; aceCount > 0; ) // Algorithm for calculating points from aces 
			{
				sum += (sum + 11 <= 21 - --aceCount) ? 11 : 1;
			}
			return sum;
		}
		else
			return 0;
	}
protected:
	std::vector<Card*> hand;
};

class GenericPlayer : public Hand
{
public:
	GenericPlayer(std::string _name) : name(_name) {};
	virtual bool IsHitting() const = 0;
	bool IsBoosted() {
		if (GetValue() > 21) { return true; }
		else { return false; }
	}
	void Bust() {
		if (IsBoosted())
			std::cout << name << " is busts!" << std::endl;
	}
	friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& _GenPlayer); // task 5
protected:
	std::string name;
};
// Task 3
class Player : public GenericPlayer { 
public:
	Player(std::string _name) : GenericPlayer(_name) {};
	virtual bool IsHitting() const{
		char ans;
		do {
			std::cout << "want to take another card? (y/n)";
			std::cin >> std::setw(1) >> ans;
			std::cin.ignore(32767, '\n');
		} while (ans != 'y' && ans != 'n');
		if (ans == 'y') return 1;
		else return 0;
	};
	void Win() const { std::cout << name << " won!" << std::endl; }
	void Lose() const { std::cout << name << " lost!" << std::endl; }
	void Push() const { std::cout << name << " has tied." << std::endl; }
};
// Task 4
class House : public GenericPlayer
{
public:
	House() : GenericPlayer("Dealer") {};
	virtual bool IsHitting() const {
		return (GetValue() < 17) ? 1 : 0;
	}
	void FlipFirstCard() {
		hand[0]->Flip();
	}
};
//Task 5
std::ostream& operator<<(std::ostream& os, const Card& _Card)
{
	const std::string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	const std::string SUITS[] = { u8"\u2666", u8"\u2663", u8"\u2665", u8"\u2660" };
	SetConsoleOutputCP(CP_UTF8);
	if (_Card.state)
	{
		os << RANKS[_Card.name] << SUITS[_Card.suit];
	}
	else
	{
		os << "XX";
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, const GenericPlayer& _GenPlayer)
{
	os << _GenPlayer.name << " "; 
	for (size_t i = 0; i < _GenPlayer.hand.size(); i++)
	{
		os << *_GenPlayer.hand[i] << " ";
	}
	os << _GenPlayer.GetValue();
	return os;
}
int main()
{
    using namespace std;
    //task1 var1
    {
        //int num;
        //cout << "Enter integer number: ";
        //cin >> num;
        //while (cin.fail()) {
        //    cin.clear();
        //    cin.ignore(32767, '\n');
        //    cout << "Input error, please try again: ";
        //    cin >> num;
        //}
    }
    //task1 var2
    {
        const int N = 256;
        char S[N];
        int num;
        cout << "Enter integer number: ";
        cin.getline(S, N);
        while (!is_digit(S)) {
            cerr << "Input error, please try again: ";
            cin.getline(S, N);
        }
        num = stoi(S);
        cout << num << endl;
    }
    //task2
    {
        cout << "endll test" << endll << "next line" << endl;
    }
    //task3-4-5
	{
		Player player("Stepan");
		if (player.IsHitting())	cout << "yes" << endl;
		else cout << "no" << endl;

		Card* pcard1;
		pcard1 = new Card(HEARTS, ACE);
		player.Add(pcard1);
		pcard1->Flip();

		Card* pcard2;
		pcard2 = new Card(CLUBS, KING);
		player.Add(pcard2);

		Card* pcard3;
		pcard3 = new Card(HEARTS, JACK);
		player.Add(pcard3);

		Card* pcard4;
		pcard4 = new Card(HEARTS, THREE);
		player.Add(pcard4);

		cout << player << endl;
		player.Bust();

		player.Clear();
	}
	return 1;
}
