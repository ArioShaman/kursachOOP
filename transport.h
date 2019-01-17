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
        bool isRent = false;

    Transport(){
        this->id = 0;
        this->createYear = 0;
        this->mark = "empty";
        this->color = "empty";
        this->number = "empty";
        this->mileage = 0;        
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

    void rent(){
        if(this->isRent){
            cout << "Транспортное средство уже арендовано \n";
        }else{    
            this->isRent = true;
        }
    }

    void unrent(){
        if(!this->isRent){
            cout << "Транспортное средство не арендовано \n";
        }else{    
            this->isRent = false;
        }
    }    

    void addMileage(int mileage){
        this->mileage = this->mileage + mileage;
    }
    bool isExist(){
        if(this->id == 0){
            return false;
        }else{
            return true;
        }
    }  

    bool isRented(){
        return this->isRent;
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