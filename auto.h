#include <string>
#include <iostream>

using namespace std;

class Auto:public virtual Transport{
    public:
        int rentPrice;//цена аренды за сутки в у.е.
        string kind;//тип транспортного средства;
        Auto(){
            cout << "Конструктор Auto без парметров";
        }
        Auto(int id, int createYear, string mark, string color, string number, int mileage, int rentPrice):Transport(id, createYear, mark, color, number, mileage){
            this->rentPrice = rentPrice;
            this->kind = "Автомобиль";
        }

    void print(){
        cout << this->id << "\n";
        cout << this->createYear << "\n";
        cout << this->mark << "\n";
        cout << this->color << "\n";
        cout << this->number << "\n";
        cout << this->mileage << "\n";

        cout << this->kind << "\n";
        cout << this->rentPrice << "\n";
        cout << "\n";    
    }        

};
