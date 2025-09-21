#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
class Vehicle{
    private:
        string vehicleNo;
        string ownerName;
        string status;
        time_t entryTime;
        time_t exitTime;
    public:
        Vehicle(string vehicleNo,string ownerName){
            this->vehicleNo=vehicleNo;
            this->ownerName=ownerName;
            entryTime=time(0);
        }
        string getVehicleNo(){
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
        ParkingSystem(string vno){
            if
        }
        void addVehicle(){

        }
        void removeVehicle(string vno){
            for(int i=0;i<vehicles.size();i++){
                if(vehicles[i]->getVehicleNo()==vno){
                    vehicles[i]->exitVehicle();
                    vehicles.erase(vehicles.begin()+i);
                    cout << "Vehicle removed successfully"<<endl;
                    return;
                }
            }
            cout << "Vehicle not found"<<endl;
        }
        void viewVehicle(){

        }
        void ViewSlot(){

        }
        void generateReport(){

        }
};
int main(){
    {
        
        int type, choice;
        string vno, ownerName;
        cout << "1. Park Vehicle" << endl;
        cout << "2. Exit Vehicle" << endl;
        cout << "3. View Parked Vehicles" << endl;
        cout << "4. View Available Slots" << endl;
        cout << "5. Generate Report" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter your name: " << endl;
                cin >> ownerName;
                cout << "Enter your vehicle number: " << endl;
                cin >> vno;
                Vehicle* v = new Vehicle(vno, ownerName);
                break;
            case 2:
                cout << "Enter your vehicle number: " << endl;
                cin >> vno;
                ParkingSystem ps(vno);
                break;
            case 3:
            case 4:
            case 5:
            case 0:
                break;
        }
    }
}