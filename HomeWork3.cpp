// C++ OOP. Lesson 3 homework
// Author: Stepan Istomin
#include <iostream>
#include <cmath>
#include <string>
#include <numeric> // for lcm and gcd
const float PI = static_cast<float>(acos(-1.0));

// Task 1

class Figure
{
public:
	Figure() {};
	virtual float area() = 0;
};
class Circle : public Figure
{
public:
	Circle(float _r) { r = _r; };
	float area() {
		return PI * powf(r,2);
	}
private:
	float r;
};
class Parallelogram : public Figure
{
public:
	Parallelogram(float _side1, float _side2, float _h) { side1 = _side1; side2 = _side2; h = _h; };
	float area() {
		return side1 * h;
	}
protected:
	float side1;
	float side2;
	float h;
};
class Rectangle : public Parallelogram
{
public:
	Rectangle (float _side1, float _side2) : Parallelogram (_side1, _side2, _side2){};
};
class Square : public Parallelogram
{
public:
	Square(float _side1) : Parallelogram(_side1, _side1, _side1) {};
};
class Rhombus : public Parallelogram
{
public:
	Rhombus(float _side1, float _h) : Parallelogram(_side1, _side1, _h) {};
};

// Task 2
class Car
{
public:
	Car(std::string _company, std::string _model) : company(_company), model(_model) {
		std::cout << std::endl << __func__ << std::endl;
	};
protected:
	std::string company;
	std::string model;
};
class PassengerCar : virtual public Car // Car now virtual class
{
public:
	PassengerCar(std::string _company, std::string _model) : Car(_company, _model) { std::cout << __func__ << std::endl;	};
};
class Bus : virtual public Car // Car now virtual class
{
public:
	Bus(std::string _company, std::string _model) : Car(_company, _model) { std::cout << __func__ << std::endl; };
};
class Minivan : public PassengerCar, Bus
{
public:
	Minivan(std::string _company, std::string _model) 
		: PassengerCar(_company, _model), Bus(_company, _model), Car(_company, _model) { std::cout << __func__ << std::endl; };
};

// Task 3
class Fraction
{
public:
	Fraction(int _numerator, int _denominator){
		numerator = _numerator;
		if (_denominator)
			denominator = _denominator;
		else {
			denominator = 1;
			std::cout << "The denominator cannot be zero. Denominator value changed to 1" << std::endl;
		};
	};
	Fraction operator+(Fraction value) const {
		int lcm = std::lcm(denominator, value.denominator); //least common multiple
		int num = numerator * (lcm / denominator) + value.numerator * (lcm / value.denominator);
		int gcd = std::gcd(num, lcm); // greatest common divisor
		num /= gcd;
		lcm /= gcd;
		return Fraction(num, lcm);
	}
	Fraction operator-(Fraction value) const {
		int lcm = std::lcm(denominator, value.denominator); //least common multiple
		int num = numerator * (lcm / denominator) - value.numerator * (lcm / value.denominator);
		int gcd = std::gcd(num, lcm); // greatest common divisor
		num /= gcd;
		lcm /= gcd;
		return Fraction(num, lcm);
	}
	Fraction operator*(Fraction value) const {
		int num = numerator * value.numerator;
		int den = denominator * value.denominator;
		int gcd = std::gcd(num, den); // greatest common divisor
		num /= gcd;
		den /= gcd;
		return Fraction(num, den);
	}
	Fraction operator/(Fraction value) const {
		int num = numerator * value.denominator;
		int den = denominator * value.numerator;
		int gcd = std::gcd(num, den); // greatest common divisor
		num /= gcd;
		den /= gcd;
		return Fraction(num, den);
	}
	Fraction operator-() const {
		return Fraction(-numerator, denominator);
	}
	friend bool operator== (Fraction l_value, Fraction r_value) {
		// check for reducible fraction - left operator
		int gcd = std::gcd(l_value.numerator, l_value.denominator);
		l_value.numerator /= gcd;
		l_value.denominator /= gcd;
		// check for reducible fraction - right operator
		gcd = std::gcd(r_value.numerator, r_value.denominator);
		r_value.numerator /= gcd;
		r_value.denominator /= gcd;
		return (l_value.numerator == r_value.numerator && l_value.denominator == r_value.denominator);
	}
	friend bool operator!=(Fraction l_value, Fraction r_value) {
		return !(l_value == r_value);
	}
	friend bool operator< ( Fraction l_value,  Fraction r_value) {
		int lcm = std::lcm(l_value.denominator, r_value.denominator); //least common multiple
		l_value.numerator = l_value.numerator * (lcm / l_value.denominator);
		r_value.numerator = r_value.numerator * (lcm / r_value.denominator);
		return (l_value.numerator < r_value.numerator);
	}
	friend bool operator>= (const Fraction& l_value, const Fraction& r_value) {
		return !(l_value < r_value);
	}
	friend bool operator> (Fraction l_value, Fraction r_value) {
		int lcm = std::lcm(l_value.denominator, r_value.denominator); //least common multiple
		l_value.numerator = l_value.numerator * (lcm / l_value.denominator);
		r_value.numerator = r_value.numerator * (lcm / r_value.denominator);
		return (l_value.numerator > r_value.numerator);
	}
	friend bool operator<= (const Fraction& l_value, const Fraction& r_value) {
		return !(l_value > r_value);
	}

	void print() { std::cout << numerator << "/" << denominator << std::endl; }
private:
	int numerator;
	int denominator;
};

// Task 4
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
	ELEVEN,
	TEN,
	JACK = 10,
	QUEEN = 10,
	KING = 10
};
class Card
{
public:
	Card(Suit _suit, CardName _name) : suit(_suit),name(_name) {};
	void Flip() {
		state = !state;
	}
	int GetValue(){
		return name;
	}
private:
	Suit suit;
	CardName name;
	bool state = 0; // 0 - card face down, 1 - card face up
};
int main()
{
	using namespace std;
    //task1
	{
		Circle circle(2);
		cout << circle.area() << endl;
		Parallelogram parallelogram(4, 3, 2.2);
		cout << parallelogram.area() << endl;
		Rectangle rectangle(4, 3);
		cout << rectangle.area() << endl;
		Square square(4);
		cout << square.area() << endl;
		Rhombus rhombus(4, 1.2);
		cout << rhombus.area() << endl;
	}
	//task2
	{
		Car car("Ford", "F150");
		PassengerCar sedan("Mazda", "Mazda 6");
		Bus bus("Ikarus", "Ikarus-260");
		Minivan minivan("Volkswagen", "T1");
		cout <<  endl;
	}
	//task3
	{
		Fraction fr1(3, 7);
		fr1.print();
		Fraction fr2(9, 2);
		fr2.print();
		if (fr1 != fr2) { cout << "Fractions are not equal" << endl; }
		Fraction fr3(57, 14);
		fr2 = fr2 - fr3;
		fr1.print();
		fr2.print();
		if (fr1 == fr2) { cout << "Fractions are equal" << endl; }
		fr1 = fr1 + fr2;
		fr1.print();
		fr2.print();
		if (fr1 > fr2) { cout << "Left Fraction is greater" << endl; }
		fr2 = fr2 * fr3;
		fr1.print();
		fr2.print();
		if (fr1 <= fr2) { cout << "Left Fraction is less or equal" << endl; }
		fr2 = fr1 / fr3;
		fr1.print();
		fr2.print();
		if (fr1 >= fr2) { cout << "Left Fraction is greater or equal" << endl; }
		fr1 = -fr1;
		fr1.print();
		fr2.print();
		if (fr1 < fr2) { cout << "Left Fraction is less" << endl; }
	}
	//task4
	//{
	//	Card card1(HEARTS, ACE);
	//	cout << card1.GetValue() << endl;
	//	Card card2(HEARTS, JACK);
	//	cout << card2.GetValue() << endl;
	//	Card card3(HEARTS, QUEEN);
	//	cout << card3.GetValue() << endl;
	//}
}
