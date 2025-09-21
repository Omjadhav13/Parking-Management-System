#include <iostream>
#include <vector>
#include <ctime>
#include <windows.h>
#include <string>
#include <mysql>
using namespace std;

class Vehicle{
    private:
        string vehicleNo;
        string ownerName;
        string status;
        time_t entryTime;
        time_t exitTime;
        double duration;
    public:
        Vehicle(){}
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
            entryTime=time(0);
        }
        void exitVehicle(){
            exitTime = time(0);
            calculateDuration();
            double charges = calculateCharges();
            cout << "Parking duration: " << duration << " minutes" << endl;
            cout << "Total bill: " << charges << " Rs." << endl;
        }
        void calculateDuration(){
            duration=difftime(exitTime,entryTime)/60;
        }
        virtual double calculateCharges(){
            return duration*50;
        }
};
class ParkingSlot{
    private:
        int slotId;
        bool isOccupied;
    public:
        ParkingSlot(int slotId){
            this->slotId = slotId;
            isOccupied = false;
        }
        void occupySlot(){
            isOccupied = true;
        }
        void freeSlot(){
            isOccupied = false;
        }
        void checkAvailability(){
            if(!isOccupied){
                cout << "Slot " << slotId << " is free" << endl;
            } else{
                cout << "Slot " << slotId << " is occupied" << endl;
            }
        }
        bool getStatus(){
            return isOccupied;
        }
};

class ParkingSystem{
    private:
        vector<Vehicle*> vehicles;
        vector<ParkingSlot> slots;
        int totalSlots;

    public:
        // Constructor
        ParkingSystem(int n = 10){  
            totalSlots = n;
            for(int i=1;i<=n;i++){
                ParkingSlot ps(i);
                slots.push_back(ps);
            }
        }

        void addVehicle(string vno,string ownerName){
            int assignedSlot = -1;
            for(int i=0;i<slots.size();i++){
                if(!slots[i].getStatus()){
                    assignedSlot = i;
                    slots[i].occupySlot();
                    break;
                }
            }
            if(assignedSlot == -1){
                cout << "No slots available!" << endl;
                return;
            }
            Vehicle* v = new Vehicle(vno, ownerName);
            vehicles.push_back(v);
            cout << "Vehicle parked in slot " << assignedSlot + 1 << endl;
            time_t entry = v->getEntryTime();
            cout << "Entry Time: " << ctime(&entry) << endl;
        }

        void removeVehicle(string vno){
            for(int i=0;i<vehicles.size();i++){
                if(vehicles[i]->getVehicleNo() == vno){
                    vehicles[i]->exitVehicle();
                    slots[i].freeSlot();  // consider storing slot in Vehicle
                    vehicles.erase(vehicles.begin() + i);
                    cout << "Vehicle removed successfully" << endl;
                    return;
                }
            }
            cout << "Vehicle not found" << endl;
        }

        void viewVehicle(){
            if(vehicles.size()==0){
                cout << "No vehicles parked, All slots are free" << endl;
                return;
            }
            for(int i=0;i<vehicles.size();i++){
                cout << "Vehicle Number: " << vehicles[i]->getVehicleNo() << endl;
                cout << "Owner Name: " << vehicles[i]->getOwnerName() << endl;
                time_t entry = vehicles[i]->getEntryTime();
                cout << "Entry Time: " << ctime(&entry) << endl;
                cout << "------------------------" << endl;
            }
        }   

        void ViewSlot(){
            for(int i=0;i<slots.size();i++){
                slots[i].checkAvailability();
            }
        }

        void generateReport(){
            cout << "Total vehicles parked: " << vehicles.size() << endl;
            cout << "Total slots available: " << slots.size()-vehicles.size() << endl;
        }
};

int main(){
        ParkingSystem ps;
        int type, choice;
        string vno, ownerName;
        do{
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
                ps.addVehicle(vno, ownerName);
                break;
            case 2:
                cout << "Enter your vehicle number: " << endl;
                cin >> vno;
                ps.removeVehicle(vno);  
                break;
            case 3:
                ps.viewVehicle();
                break;
            case 4:
                ps.ViewSlot();
                break;
            case 5:
                ps.generateReport();
                break;
            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }    while(choice!=0);
    return 0;   
}
