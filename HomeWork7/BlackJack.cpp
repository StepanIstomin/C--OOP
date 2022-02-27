//  C++ OOP. BlackJack game
// Author: Stepan Istomin

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <Windows.h> //for SetConsole
#include <algorithm> // for shuffle
#define DELAY 1000

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
	int GetValue() const {
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
class Player : public GenericPlayer {
public:
	Player(std::string _name) : GenericPlayer(_name) {};
	virtual bool IsHitting() const {
		if (GetValue() == 21) return 0;
		char ans;
		do {
			std::cout << "Do you want to take another card? (y/n)";
			std::cin >> std::setw(1) >> ans;
			std::cin.ignore(32767, '\n');
		} while (ans != 'y' && ans != 'n' );
		if (ans == 'y') return 1;
		else return 0;
	};
	void Win() const { std::cout << name << " won!" << std::endl; }
	void Lose() const { std::cout << name << " lost!" << std::endl; }
	void Push() const { std::cout << name << " has tied." << std::endl; }
};
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
std::ostream& operator<<(std::ostream& os, const GenericPlayer& _GenPlayer)
{
	os << _GenPlayer.name << ": ";
	for (size_t i = 0; i < _GenPlayer.hand.size(); i++)
	{
		os << *_GenPlayer.hand[i] << " ";
	}
	os << "(" << _GenPlayer.GetValue() << ")";
	return os;
}
class Deck : public Hand
{
public:
	Deck() { Populate(); };
	void Populate(){
		for (size_t i = 0; i < 4; i++)	{		//card suit
			for (size_t j = 1; j <= 13; j++) {	//card name
				Add(new Card(static_cast<Suit>(i), static_cast<CardName>(j)));
			}
		}
	}
	void Shuffle(){
		std::random_shuffle(hand.begin(),hand.end());
	}
	void Deal(Hand& aHand){
		if (!hand.empty()) {
			aHand.Add(hand.back());
			hand.pop_back();
		}
		else std::cout << "Out of cards. Unable to deal.";
	}
	void AddltionalCards(GenericPlayer& aGenerlcPlayer) {
		while (!(aGenerlcPlayer.IsBoosted()) && aGenerlcPlayer.IsHitting())
		{
			Deal(aGenerlcPlayer);
			std::cout << aGenerlcPlayer << std::endl;
			Sleep(DELAY);
			if (aGenerlcPlayer.IsBoosted())
				aGenerlcPlayer.Bust();
		}
	}
};
class Game
{
public:
	Game(std::vector<std::string> _names) {
		std::vector<std::string>::const_iterator pName;
		for (pName = _names.begin(); pName != _names.end(); ++pName)
			players.push_back(Player(*pName));
		deck.Populate();
		srand(static_cast<unsigned int>(time(0)));
		deck.Shuffle();
	};
	void play() {
		// Start hand
		std::vector<Player>::iterator pPlayer;
		for (size_t i = 0; i < 2; i++) {
			deck.Deal(house);
			for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
				deck.Deal(*pPlayer);
		}
		house.FlipFirstCard();
		std::cout << std:: endl << house << std::endl;
		// Additional cards
		for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
			std::cout << *pPlayer << std::endl;
		for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
			deck.AddltionalCards(*pPlayer);
		house.FlipFirstCard();
		std::cout << house << std::endl;
		Sleep(DELAY);
		for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer) { // If only one player
			if (!pPlayer->IsBoosted())
				deck.AddltionalCards(house);
			else pPlayer->Lose();
		}
		// Win conditions
		if (house.IsBoosted()) {
			for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer) {
				if (!pPlayer->IsBoosted())
					pPlayer->Win();
			}
		}
		else {
			for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer) {
				if (!pPlayer->IsBoosted()) {
					if (pPlayer->GetValue() > house.GetValue())
						pPlayer->Win();
					else if (pPlayer->GetValue() < house.GetValue())
						pPlayer->Lose();
					else
						pPlayer->Push();
				}
			}
		}
		//hand clearing
		for (pPlayer = players.begin(); pPlayer != players.end(); ++pPlayer)
			pPlayer->Clear();
		house.Clear();
	};
	bool wantToPlay() {
		char ans;
		do {
			std::cout << "Do you want to play again? (y/n)";
			std::cin >> std::setw(1) >> ans;
			std::cin.ignore(32767, '\n');
		} while (ans != 'y' && ans != 'n');
		if (ans == 'y') return 1;
		else return 0;
	}
private:
	Deck deck;
	House house;
	std::vector<Player> players;
};
int main()
{
	using namespace std;
	cout << "Welcome to Blackjack game!" << endl;
	bool playOn;
	string playerName;
	vector<string> names;
	cout << "Enter your name: ";
	cin >> playerName;
	names.push_back(playerName);
	do {
		Game game(names);
		game.play();
		playOn = game.wantToPlay();
	} while (playOn);
}
