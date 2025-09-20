#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
class Vehicle{
    private:
        int vehicleNo;
        string ownerName;
        string status;
        time_t entryTime;
        time_t exitTime;
    public:
        Vehicle(int vehicleNo,string ownername){
            this->vehicleNo=vehicleNo;
            this->ownerName=ownerName;
            entryTime=time(0);
        }
        int getVehicleNo(){
            return vehicleNo; 
        }
        string getOwnerName(){
            return ownerName;
        }
        time_t getEntryTime(){
            return entryTime;
        }
        void parkingVehicle(){

        }
        void exitVehicle(){
         
        }
        virtual double calculateCharges(){
            return 20;
        }
};

class car:public Vehicle{
    public:
        double calculateCharges(){
            return 50;
        }
};

class Bike:public Vehicle{
    public: 
        double calculateCharges() override{
            return 20;
        }
};

class ParkingSlot{
    private:
        int slotId;
        string status;
    public:
        ParkingSlot(int slotId){
            this->slotId=slotId;
        }
        void freeSlot(){

        }
        void checkAvailability(){

        }
};
class ParkingSystem{
    private:
        vector<Vehicle*> vehicles;
        vector<ParkingSlot> slots;
    public:
        ParkingSystem(int totalslots){
            
        }
        void addVehicle(){

        }
        void removeVehicle(){

        }
        void viewVehicle(){

        }
        void ViewSlot(){

        }
        void generateReport(){

        }
};
int main(){
   int choice;
   string type,vehicleNo,ownerName;
   cout << "1. Park Vehicle"<<endl;
   cout << "2. Exit Vehicle"<<endl;
   cout << "3. View Parked Vehicles"<<endl;
   cout << "4. View Available Slots"<<endl;
   cout << "5. Generate Report"<<endl;
   cout << "0. Exit"<<endl;
   cout << "Enter choice: "<<endl;
   cin  >> choice;
   switch(choice){
       case 1:
            cout <<"Enter your name: "<<endl;
            cin >> ownerName;
            cout << "Enter your vehicle number: "<< endl;
            cin >> vehicleNo;
            cout << "Enter your vehicle type: "<<endl;
            cin >> type;
            break;
       case 2:
       case 3:
       case 4:
       case 5:
       case 0:
    }
}