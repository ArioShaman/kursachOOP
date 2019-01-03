#include <string>
#include <iostream>

using namespace std;

class OrderAuto:public virtual Order{
    public:
        int startRent;

    OrderAuto(int id, int id_transport, int startRent, int durationRent):Order(id,id_transport,durationRent){
        this->startRent = startRent;
    }

    friend ostream &operator<<(ostream &output, const OrderAuto &o){
        output << "ID: "<< o.id << "\n";
        output << "Auto ID: "<< o.id_transport << "\n";
        output << "Начало аренды(день): "<< o.startRent << "\n";
        output << "Длительность аренды: "<< o.durationRent << "\n";
        output << "Длительность штрафа: "<< o.durationFine << "\n";
        output << "Заказ закрыт?: "<< o.isClose << "\n";
        cout << "\n";
    }

    bool isExpireRent(int curDay){
        int runnedTime = curDay - this->startRent;
        // cout << "runnedTime:   " << runnedTime << "\n\n";
        if(runnedTime >= this->durationRent){
            return true;
        }
        else{
            return false;
        }
    }

    void print(){
        cout << this->id << "\n";
        cout << this->id_transport << "\n";
        cout << this->startRent << "\n";
        cout << this->durationRent << "\n";
        cout << this->durationFine << "\n";
        cout << this->isClose<< "\n";
        cout << "\n";
    }
};