#include <string>
#include <iostream>

using namespace std;

class Auto:public virtual Transport{
    public:
        int rentPrice;//цена аренды за сутки в у.е.
        string kind;//тип транспортного средства;
        Auto():Transport(){
            this->rentPrice = 0;
            this->kind = "Автомобиль";
        }
        Auto(int id, int createYear, string mark, string color, string number, int mileage, int rentPrice):Transport(id, createYear, mark, color, number, mileage){
            this->rentPrice = rentPrice;
            this->kind = "Автомобиль";
        }

        void setAuto(Auto &a){
            this->id = a.id;
            this->createYear = a.createYear; 
            this->mark = a.mark;
            this->color = a.color;
            this->number = a.number;
            this->mileage = a.mileage;
            this->rentPrice = a.rentPrice;
            this->isRent = a.isRent;   
            this->kind = "Автомобиль";
        }

        friend ostream &operator<<(ostream &output, const Auto &a){

            output << "ID: "<< a.id << "\n";
            output << "Дата создания: "<< a.createYear << "\n";
            output << "Модель: "<< a.mark << "\n";
            output << "Цвет: "<< a.color << "\n";
            output << "номер: "<< a.number << "\n";
            output << "Пробег: "<< a.mileage << "\n";
            output << "Тип транспорта: "<< a.kind << "\n";
            output << "Цена аренды: "<< a.rentPrice << "\n";
            output << "Арендован ли транспорт?: "<< a.isRent << "\n\n";
            return output;
        }           

};
