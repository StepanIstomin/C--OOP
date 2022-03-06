// C++ OOP. Lesson 8 homework
// Author: Stepan Istomin

#include <iostream>

//task1
class DivisionByZero
{
public:
    DivisionByZero(std::string _error):error(_error) {};
    std::string error;
};
template <typename T>
double division(T dividend, T divisor) {
    if (!divisor)
        throw  DivisionByZero("Divisor is null!"); 
    else
        return dividend / static_cast<double>(divisor);
}
//task2
class Ex
{
public:
    Ex(double _x):x(_x) {};
    double x;
};
class Bar
{
public:
    Bar() { y = 0; };
    void set(double a) {
        if (y + a > 100)
            throw Ex(a * y);
        else
            y = a;
    }
private:
    double y;
};
//task3
class Field {
public:
    Field(int _x, int _y) : coord_x(_x), coord_y(_y), dir(0) {};
    Field(int _x, int _y, int _dir) : coord_x(_x), coord_y(_y), dir(_dir) {};
    void showPos() {
        std::cout << "[" << coord_x << "," << coord_y << "]";
    }
protected:
    int coord_x;
    int coord_y;
    int dir;
};
class IllegalCommand : public Field
{
public:
    IllegalCommand(int _x, int _y, int _dir) : Field(_x,_y,_dir) {};
    void error() {
        std::cerr << "Error: wrong offset direction (" << dir << ") - should be in range (1-9). Current position ";
        showPos();
        std::cerr << std::endl;
    };
};
class OffTheField : public Field
{
public:
    OffTheField(int _x, int _y, int _dir) : Field(_x, _y, _dir) {};
    void error() {
        std::cerr << "Error: going out of the field. Direction: " << dir << ". Current position ";
        showPos();
        std::cerr << std::endl;
    };
};
class Robot : public Field
{
public:
    Robot():Field(1, 1) {};
    void move(int _dir){
        dir = _dir;
        if (dir < 1 || dir > 9 ) throw IllegalCommand(coord_x, coord_y, dir);
        int new_coord_x;
        int new_coord_y;
        switch (dir)
            {
            case 1:
                new_coord_x = coord_x - 1;
                new_coord_y = coord_y - 1;
                break;
            case 2:
                new_coord_x = coord_x;
                new_coord_y = coord_y-1;
                break;
            case 3:
                new_coord_x = coord_x + 1;
                new_coord_y = coord_y - 1;
                break;
            case 4:
                new_coord_x = coord_x - 1;
                new_coord_y = coord_y;
                break;
            case 5:
                new_coord_x = coord_x;
                new_coord_y = coord_y;
                break;
            case 6:
                new_coord_x = coord_x + 1;
                new_coord_y = coord_y;
                break;
            case 7:
                new_coord_x = coord_x - 1;
                new_coord_y = coord_y + 1;
                break;
            case 8:
                new_coord_x = coord_x;
                new_coord_y = coord_y + 1;
                break;
            case 9:
                new_coord_x = coord_x + 1;
                new_coord_y = coord_y + 1;
                break;
            default:
                break;
            }
        if (new_coord_x < 1 || new_coord_x > 10 || new_coord_y < 1 || new_coord_y > 10)
            throw OffTheField(coord_x, coord_y, dir);
        else {
            coord_x = new_coord_x;
            coord_y = new_coord_y;
        }
    }
};
int main()
{
    using namespace std;
// Task 1
    try {
        cout << division(2, 0);
    }
    catch (DivisionByZero ex) {
        cerr << ex.error << endl;
    }
//Task 2
    Bar bar;
    int n;
    do {
        try {
            cin >> n;
            bar.set(n);
        }
        catch (Ex ex){cerr << "Ex = " << ex.x << endl;}
    } while (n);
//Task 3
    Robot robot;
    int dir;
    cout << "The robot's displacement is set by the num buttons of the keyboard (1-9), button 5 - stopping movement." << endl;
    do {
        cout << "Current position";
        robot.showPos();
        cout << " Enter the offset direction: ";
        cin >> dir;
        while (cin.fail()) { // Integer check
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Input error, please try again: ";
            cin >> dir;
        }
        try {    
            robot.move(dir);
        }
        catch (IllegalCommand ex) { ex.error(); }
        catch (OffTheField ex) { ex.error(); }
    } while (dir != 5);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

