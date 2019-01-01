#include <string>
#include <iostream>

using namespace std;

class Transport{
    public:
        int id;
        int createYear;//год выпуска
        string mark;//марка
        string color;//цвет транспортного средства
        string number;//номер транспортного средства
        int mileage;//пробег в километрах

    Transport(){
        cout << "Конструктор Transport без параметров";
    }
    Transport(int id, int createYear, string mark, string color, string number, int mileage){
        this->id = id;
        this->createYear = createYear;
        this->mark = mark;
        this->color = color;
        this->number = number;
        this->mileage = mileage;
        // print();
    }
    void print(){
        cout << this->id << "\n";
        cout << this->createYear << "\n";
        cout << this->mark << "\n";
        cout << this->color << "\n";
        cout << this->number << "\n";
        cout << this->mileage << "\n";
    }
};