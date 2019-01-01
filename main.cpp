#include <string>
#include <iostream>

#include "transport.h"
#include "bike.h"
#include "auto.h"


#include <fstream>

using namespace std;

void readDataFromFile(){
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
            a.print();
        }
        if(kind == "bike"){
            Bike b(id, year, mark, color, number, mileage, rentPrice);
            b.print();
        }
        cout << "\n";

    } 
}

int main(){
    readDataFromFile();
    return 0;
}