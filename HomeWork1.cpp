// C++ OOP. Lesson 1 homework
// Author: Stepan Istomin

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdint> // for Task 2

// Task 1
class Power
{
private:
	double number1, number2;
public:
	Power() { number1 = 1; number2 = 1; }
	//Power(double _num1 = 1, double _num2 = 1) { number1 = _num1; number2 = _num2; }
	//Power(double _num1 = 1, double _num2 = 1) : number1(_num1), number2(_num2) {}
	void set(double num1, double num2) {
		number1 = num1;
		number2 = num2;
	}
	double calculate() {
		return pow(number1, number2);
	}
};

// Task 2
class RGBA
{
private:
	std::uint8_t m_red, m_green, m_blue, m_alpha;
public:
	RGBA(uint8_t _red = 0, uint8_t _green = 0, uint8_t _blue = 0, uint8_t _alpha = 255) {
		m_red = _red;
		m_green = _green;
		m_blue = _blue;
		m_alpha = _alpha;
	}
	void print() {
		std::cout << "red\t" << unsigned(m_red) << "\n";
		std::cout << "green\t" << unsigned(m_green) << "\n";
		std::cout << "blue\t" << unsigned(m_blue) << "\n";
		std::cout << "alpha\t" << unsigned(m_alpha) << "\n";
	}
};

// Task 3
class Stack
{
private:
	int array[10];
	int cursor = -1;
public:
	void reset() {
		for (int i = 0; i < 10; i++)
			array[i] = 0;
			cursor = -1;
	}
	int push(int data) {
		if (cursor < 10) {
			array[++cursor] = data;
			return true;
		}
		else {
			std::cout << "Stack overflow\n";
			return false;
		}
	}
	int pop() {
		if (cursor != -1)
			return array[cursor--];
		else {
			std::cout <<  "Stack is empty\n";
			return -1;
		}
	}
	void print() {
		std::cout << "( ";
		for (int i = 0;i<=cursor;i++)
			std::cout << array[i] << " ";
		std::cout << ")" << std::endl;
	}
};

int main()
{
	Power task1;
	std::cout << "-------- Task 1 --------\n" << task1.calculate() << std::endl;
	task1.set(3, 2);
	std::cout << task1.calculate() << std::endl;
	std::cout << "-------- Task 2 --------\n";
	RGBA task2;
	task2.print();
	std::cout << "-------- Task 3 --------\n";

	Stack stack;
	stack.reset();
	stack.print();

	stack.push(3);
	stack.push(7);
	stack.push(5);
	stack.print();

	stack.pop();
	stack.print();

	stack.pop();
	stack.pop();
	stack.print();
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

