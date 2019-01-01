#include <string>
#include <iostream>

#include "transport.h"
#include "order.h"


#include "bike.h"
#include "auto.h"

#include "orderAuto.h"
#include "orderBike.h"

#include <fstream>
#include <stack> 


#include <ctime>
#include <cstdlib>

using namespace std;


//Чтение данных с файла
void readDataFromFile(stack <Auto> &autoStack, stack <Bike> &bikeStack){
    ifstream file("./database.txt");

    if(!file) {
        cout << "Cannot open input file.\n";
    }    


    string s;
    while (getline(file, s)) {
        int id; 
        int year;
        string mark;
        string color;
        string number;
        int mileage;        
        int rentPrice;
        string kind;        

        string delimiter = ",";
        size_t pos = 0;
        string token;
        int index = 0;

        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);

            switch(index){
                case 0:
                    id = stoi(token);
                    break;
                case 1:
                    year = stoi(token);
                    break;
                case 2:
                    mark = token;
                    break;
                case 3:
                    color = token;
                    break;
                case 4:
                    number = token;
                    break;
                case 5:
                    mileage = stoi(token);
                    break;
                case 6:
                    rentPrice = stoi(token);
                    break;
                case 7:
                    kind = token;
                    break;                                                                                                                                            
                default:
                    break;
            }

            s.erase(0, pos + delimiter.length());
            index++;
        }
    
        if (kind == "auto"){
            Auto a(id, year, mark, color, number, mileage, rentPrice);   
            autoStack.push(a);
        }
        if(kind == "bike"){
            Bike b(id, year, mark, color, number, mileage, rentPrice);
            bikeStack.push(b);
        }
    } 
}


int main(){
    // OrderAuto oa(1,1, 3, 10);
    // cout << oa;

    // OrderBike ob(1,2,6);
    // cout << ob;

    stack <Auto> autoStack;
    stack <Bike> bikeStack;
    readDataFromFile(autoStack, bikeStack);
    

    int orderId = 0;

    srand(time(NULL));
    for(int curDay = 1; curDay <= 30; curDay++){
        cout << "Текущий день:   "<< curDay << "\n";

        int countCustomers;
        countCustomers=1+rand()%(15-1);
        // cout<< countCustomers << "\n";
        for(int curCustomer = 1; curCustomer <= countCustomers; curCustomer++){
            cout << curCustomer << "\n";
        }
    }
    // cout << autoStack.top();
    // cout << bikeStack.top();


    return 0;
}