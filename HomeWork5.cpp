// C++ OOP. Lesson 5 homework
// Author: Stepan Istomin

#include <iostream>
#include <string>
#include <vector>

// Task 1
template<typename T>
class Pair1
{
public:
	Pair1(T _num1, T _num2) : num1(_num1),num2(_num2) {};
	T first() const { return num1; }
	T second() const { return num2; }
private:
	T num1;
	T num2;
};
// Task 2
template<typename T1, typename T2>
class Pair
{
public:
	Pair(T1 _num1, T2 _num2) : num1(_num1), num2(_num2) {};
	T1 first() const { return num1; }
	T2 second() const { return num2; }
protected:
	T1 num1;
	T2 num2;
};
// Task 3
template<typename T>
class StringValuePair : public Pair<std::string, T>
{
public:
	StringValuePair(std::string _val1, T _val2) : Pair<std::string, T>(_val1,_val2) {};
};
// Task 4
enum Suit {
	DIAMONDS,	// Бубны
	CLUBS,		// Трефы
	HEARTS,		// Червы
	SPADES		// Пики
};
enum CardName {
	ACE = 11,
	TWO = 2,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK = 10,
	QUEEN = 10,
	KING = 10
};
class Card
{
public:
	Card(Suit _suit, CardName _name) : suit(_suit), name(_name) {};
	void Flip() {
		state = !state;
	}
	int GetValue() {
		return name;
	}
private:
	Suit suit;
	CardName name;
	bool state = 0; // 0 - card face down, 1 - card face up
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
	int GetValue() {
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
	GenericPlayer(std::string _name = "Player") : name(_name) {};
	//~GenericPlayer();
	virtual bool IsHitting() { return 0; }
	bool IsBoosted() {
		if (GetValue() > 21) { return true; }
		else { return false; }
	}
	void Bust() {
		if (IsBoosted())
			std::cout << name << " is busts!" << std::endl;
	}
protected:
	std::string name;
};
int main()
{
	using namespace std;
//task1
	{
		Pair1<int> p1(6, 9);
		cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

		const Pair1<double> p2(3.4, 7.8);
		cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
	}
//task2
	{
		Pair<int, double> p1(6, 7.8);
		cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

		const Pair<double, int> p2(3.4, 5);
		cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

	}
//task3
	{
		StringValuePair<int> svp("Amazing", 7);
		std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
	}
//task4
	{
		GenericPlayer playerHand;

		Card* pcard1;
		pcard1 = new Card(HEARTS, ACE);
		playerHand.Add(pcard1);

		Card* pcard2;
		pcard2 = new Card(CLUBS, KING);
		playerHand.Add(pcard2);

		Card* pcard3;
		pcard3 = new Card(HEARTS, JACK);
		playerHand.Add(pcard3);
		
		Card* pcard4;
		pcard4 = new Card(HEARTS, THREE);
		playerHand.Add(pcard4);

		cout << playerHand.GetValue() << endl;
		playerHand.Bust();

		playerHand.Clear();

	}
	return 0;
}
