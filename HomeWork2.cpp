// C++ OOP. Lesson 2 homework
// Author: Stepan Istomin

#include <iostream>
#include <string>

// Task 1
enum Gender
{
	MALE,
	FEMALE
};
class Person
{
public:
	Person(std::string _name, int _age, Gender _gender, int _weight) { name = _name; age = _age; gender = _gender; weight = _weight; };
	void setName(std::string _name) { name = _name; }
	void setAge(int _age) { age = _age; }
	void setWeight(int _weight) { weight = _weight; }
protected:
	std::string name;
	int age;
	Gender gender;
	int weight;
};
class Student : public Person
{
public:
	Student(std::string _name, int _age, Gender _gender, int _weight, int _year = 1) : Person(_name, _age, _gender, _weight) {
		year = _year; studCount++;
	};
	void setYear(int _year) { year = _year; }	//reassignment 
	void incrYear() { year++; }					//increase 
	void printInfo() {
		std::cout << "Student: \t" << name << std::endl;
		std::cout << "Age: \t\t" << age << std::endl;
		std::cout << "Gender: \t";
		if (gender)
			std::cout << "female";
		else
			std::cout << "male";
		std::cout << std::endl;
		std::cout << "Weight: \t" << weight << std::endl;
		std::cout << "Year of study: \t" << year << std::endl << std::endl;
	}
	void countInfo() { std::cout << "Number of students: " << studCount << std::endl << std::endl; }
private:
	int year;
	static int studCount;
};
int Student::studCount = 0;

// Task 2
class Fruit
{
public:
	Fruit(std::string _name, std::string _color) { name = _name; color = _color; };
	std::string getName() {
		return name;
	}
	std::string getColor() {
		return color;
	}
protected:
	std::string name;
	std::string color;
};
class Apple:public Fruit
{
public:
	Apple(std::string _color) : Fruit("apple", _color) {};
	Apple(std::string _name, std::string _color) : Fruit(_name, _color) { name = _name + " apple"; color = _color; };
};
class Banana :public Fruit
{
public:
	Banana() : Fruit("banana", "yellow") {};
};
class GrannySmith :public Apple
{
public:
	GrannySmith() : Apple("Granny Smith", "green") {};
};

int main()
{
	//task1
	{
		Student first("Mel Gibson", 56, MALE, 78, 2);
		first.setAge(66);
		first.printInfo();
		Student second("Usain Bolt", 34, MALE, 85, 1);
		second.setName("Usain St. Leo Bolt");
		second.printInfo();
		Student third("Adele", 33, FEMALE, 68, 3);
		third.incrYear();
		third.printInfo();
		third.countInfo();
	}
	//task2
	{
		Apple a("red");
		Banana b;
		GrannySmith c;

		std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
		std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
		std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";
	}
	return 0;
}

/* Task 3
* If the comments are not displayed in Russian, the task is duplicated on the portal GB
* Для игры в Блек Джек предполагаю создать следующие классы:

Класс Game который будет включать в себя переменные статуса игры, колоды, и все методы для управления ходом игры и взаимодействия между классами Dealer и Player и отображением происходящего на экране.
В зависимости от того какие именно правила будут в задании к игре, будет задана колода карт (или несколько колод), состояние колоды должно отслеживаться, какие карты еще в колоде а какие уже розданы.
Колоду предполагаю отслеживаться через массив размера 13 х 4, где строки - значение карт, а номера столбцов будут обозначать масти (К примеру deck[1][3] будет отвечать за двойку бубей.)
наличие карты в колоде отслеживаться через значение ячейки, где 1-карта еще в колоде, 0 - карта уже роздана.
Если игра идет в три колоды, то тогда значения массива будут приниматься в диапазоне 0 - 3
Выбор карты из колоды будет определяется методом генерирующим через ПСЧ номер строки и номер столбца, генерация идет до момента пока не будет найдена ненулевая ячейка.

Player - базовый класс, с полем "points", "status"
и методами на проверку и изменения статусов (Блэк-Джек, недобор, перебор),
для хранения и отображении на экране информации о взятых картах можно создать поле "cards" в виде массива класса "Card" куда методами будут добавляться карты,
отдельный метод будет считать кол-во очков, учитывая 1 или 11 очков для туза в зависимости от общего количества очков.
перед каждой раздачей поля points и cards будут обнулятся

Dealer - производный от Player класс, с котором будут немного другие методы управляющие статусами и прописаны алгоритмы ИИ для управления дилером.

Active Player - производный от Player класс активного игрока, добавлено поле "деньги" и "ставка" (возможно еще добавить поле "name" для отображения игрока).

Card - класс карты, с полями "название", "масть". (Количество очков в зависимости от названия карты будет считаться методами класса Player, т.к. для туза кол-во очков определяется неоднозначно.).
Методы класса будут определять название и масть в зависимости от той ячейки массива deck из которой была "вынута" карта.
*/ 
