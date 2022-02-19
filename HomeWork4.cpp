// C++ OOP. Lesson 4 homework
// Author: Stepan Istomin

#include <iostream>
#include <cassert>		// for assert
#include <vector>
#include <algorithm>	// for "sort" and "unique"
#include <ctime>		// to measure program time 
#include <unordered_set>

// Task 1
class ArrayInt
{
private:
	int m_lenght;
	int* m_data;
public:
	ArrayInt() : m_lenght(0), m_data(nullptr) {}
	ArrayInt(int lenght) : m_lenght(lenght) {
		assert(lenght >= 0);
		if (lenght > 0)
			m_data = new int[lenght];
		else
			m_data = nullptr;
	}
	~ArrayInt() { delete[] m_data; }
	void erase() {
		delete[] m_data;
		m_lenght = 0;
		m_data = nullptr;
	}
	void resize(int newLenght) {
		if (newLenght <= 0)
			erase();
		int* newData = new int[newLenght];
		int CopyElements = 0;
		if (newLenght > m_lenght) CopyElements = m_lenght;
		else CopyElements = newLenght;
		for (size_t i = 0; i < CopyElements; i++)
			newData[i] = m_data[i];
		delete[]m_data; 
		m_data = newData;
		m_lenght = newLenght;
	}
	void pop_back() { //для удаления последнего элемента массива (аналог функции pop_back() в векторах)
		resize(m_lenght - 1);
	}
	void pop_front() { //для удаления первого элемента массива (аналог pop_front() в векторах)
		int* newData = new int[m_lenght-1];
		int CopyElements = 0;
		for (size_t i = 1; i < m_lenght; i++)
			newData[i-1] = m_data[i];
		delete[]m_data;
		m_data = newData;
		m_lenght--;
	}
	void sort() { //для сортировки массива
		std::sort(m_data, m_data+m_lenght);
	}
	void print() { // для вывода на экран элементов
		for (size_t i = 0; i < m_lenght; i++)
		{
			std::cout << "[" << m_data[i] << "] ";
		};
		std::cout << std::endl;
	}
	int& operator[](int index) {
		assert(index >= 0);
		return m_data[index];
	}
};
// Task 2
size_t usingVector(const std::vector<int>& input)
{
	std::vector<int> uniq; // create new vector for unique values
	uniq.reserve(input.size());
	for (int item : input) {
		uniq.push_back(item);
	}
	std::sort(uniq.begin(), uniq.end());
	return unique(uniq.begin(), uniq.end()) - uniq.begin(); // " - uniq.begin()" becose we work with pointers
}
size_t usingUnSet(const std::vector<int>& input)
{
	std::unordered_set<int> uniq;
	uniq.reserve(input.size());
	for (int item : input) {
		uniq.insert(item);
	}
	return uniq.size();
}
// Task 3
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
private:
	std::vector<Card*> hand;
};

int main()
{
	using namespace std;

	//task1
	{
		ArrayInt array(10);
		for (size_t i = 0; i < 10; i++)
			array[i] = rand()/100;
		array.print();
		array.pop_back();
		array.print();
		array.pop_front();
		array.print();
		array.sort();
		array.print();
	}
	//task2
	{
		int size = 100000;
		vector<int> checkArray;
		for (size_t i = 0; i < size; i++)
			checkArray.push_back(rand());

		unsigned int start_time = clock(); // начальное время
		cout << "Different values: " << usingVector(checkArray) << endl;
		unsigned int end_time = clock(); // конечное время
		unsigned int search_time = end_time - start_time; // искомое время
		cout << "Running time Vector (ms): " << search_time << endl;

		start_time = clock(); // начальное время
		cout << "Different values: " << usingUnSet(checkArray) << endl;
		end_time = clock(); // конечное время
		search_time = end_time - start_time; // искомое время
		cout << "Running time unordered set (ms): " << search_time << endl;
	}
	//task3
	{
		Hand playerHand;
		cout << playerHand.GetValue() << endl;

		Card* pcard1;
		pcard1 = new Card(HEARTS, EIGHT);
		playerHand.Add(pcard1);
	
		Card* pcard2;
		pcard2 = new Card(CLUBS, ACE);
		playerHand.Add(pcard2);
	
		Card* pcard3;
		pcard3 = new Card(HEARTS, ACE);
		playerHand.Add(pcard3);
	
		cout << playerHand.GetValue() << endl;
		playerHand.Clear();
		cout << playerHand.GetValue() << endl;

	}
	return 0;
}