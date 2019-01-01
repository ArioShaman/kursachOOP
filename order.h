#include <string>
#include <iostream>

using namespace std;

class Order{
    public:
        int id;
        int id_transport;
        int durationRent;
        int durationFine = 0;
        bool isCose = false;

    Order(int id, int id_transport, int durationRent){
        this->id = id;
        this->id_transport = id_transport;
        this->durationRent = durationRent; 
        // print();
    }

    void print(){
        cout << this->id << "\n";
        cout << this->id_transport << "\n";
        cout << this->durationRent << "\n";
        cout << this->durationFine << "\n";
        cout << this->isCose<< "\n";
        cout << "\n";
    }
};