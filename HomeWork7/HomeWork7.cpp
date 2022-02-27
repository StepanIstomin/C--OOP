// C++ OOP. Lesson 7 homework
// Author: Stepan Istomin

#include <iostream>
#include <ctime>
#include <memory>

// Task1
class Date
{
public:
	Date(signed short _day, signed short _month, signed short _year) : day(_day), month(_month), year (_year) {};
	void changeDay(signed short _day) { day = _day; }
	void changeMonth(signed short _month) { month = _month; }
	void changeYear(signed short _year) { year = _year; }
	friend std::ostream& operator<<(std::ostream& os, const Date& _Date);
	friend Date laterDate(const std::shared_ptr<Date> _date1, const std::shared_ptr<Date> _date2);
private:
	signed short day;
	signed short month;
	signed short year;
};
std::ostream& operator<<(std::ostream& os, const Date& _Date)
{
	os << _Date.day << "." << _Date.month << "." << _Date.year;
	return os;
}
// Task 2
Date laterDate(const std::shared_ptr<Date> _date1, const std::shared_ptr<Date> _date2) {
	if (_date1->year > _date2->year) return *_date1;
	else if (_date1->year < _date2->year) return *_date2;
	else {
		if (_date1->month > _date2->month) return *_date1;
		else if (_date1->month < _date2->month) return *_date2;
		else {
			if (_date1->day > _date2->day) return *_date1;
			else return *_date2;
		}
	}
}
void swapDate(std::shared_ptr<Date> &_date1, std::shared_ptr<Date> &_date2) { //Обязательно передавать умный указатель по адресу, иначе передается копия
	_date1.swap(_date2);
}
int main()
{
	using namespace std;
    //task 1
	{
		//auto_ptr and scoped_ptr - old style 
		// new C++11 smart pointers:
		//unique_ptr - replace for auto_ptr
		//weak_ptr - used when you need a smart pointer that has access to a resource but is not considered its owner 
		//shared_ptr - used to own a single dynamically allocated resource by multiple smart pointers at once

		//unique_ptr<Date> today(new Date(25,2,2022));
		//unique_ptr<Date> date;
		shared_ptr<Date> today(new Date(25, 2, 2022));
		shared_ptr<Date> date;

		today->changeDay(26);
		today->changeYear(22);
		cout << *today << endl;
		date = today;
		if (date.get()) cout << "date pointer is not null" << endl;
		else cout << "date pointer is null" << endl;
		if (today.get()) cout << "today pointer is not null" << endl;
		else cout << "today pointer is null" << endl;
	}
	//task 2
	{
		shared_ptr<Date> date1(new Date(9, 11, 2005));
		shared_ptr<Date> date2(new Date(8, 12, 2004));
		cout << laterDate(date1, date2) << endl; // unique_ptr не передаются в функцию?
		cout << *date2 << endl;
		swapDate(date1, date2);
		cout << *date1 << endl << *date2;
	}
}

