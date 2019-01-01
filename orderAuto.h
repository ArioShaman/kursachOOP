#include <string>
#include <iostream>

using namespace std;

class OrderAuto:public virtual Order{
    public:
        int startRent;

    OrderAuto(int id, int id_transport, int startRent, int durationRent):Order(id,id_transport,durationRent){
        this->startRent = startRent;
    }

    void print(){
        cout << this->id << "\n";
        cout << this->id_transport << "\n";
        cout << this->startRent << "\n";
        cout << this->durationRent << "\n";
        cout << this->durationFine << "\n";
        cout << this->isCose<< "\n";
        cout << "\n";
    }
};