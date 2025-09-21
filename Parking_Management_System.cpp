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

        }
        void exitVehicle(){
            exitTime=time(0);
            
            double charges=calculateCharges();
            calculateDuration();
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
        
        void addVehicle(string vno,string ownerName){
            for(int i=0;i<vehicles.size();i++){
                if(vehicles[i]->getVehicleNo()==vno){
                        cout << "Welcome back " << vehicles[i]->getOwnerName() << endl;
                        Vehicle* v=new Vehicle(vno,ownerName);
                        vehicles.push_back(v);
                        cout << "Your vehicle number is " << vno << endl;
                        time_t entry = v->getEntryTime();
                        cout << "Your entry time is " << ctime(&entry) << endl;
                        return;
                    }    
                }                    
            Vehicle* v=new Vehicle(vno,ownerName);
            vehicles.push_back(v);
            cout << "Vehicle added successfully"<<endl;
            cout << "Your vehicle number is " << vno << endl;
            time_t entry = v->getEntryTime();
            cout << "Your entry time is " << ctime(&entry) << endl;
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
            for(int i=0;i<vehicles.size();i++){
                cout << "Vehicle Number: " << vehicles[i]->getVehicleNo() << endl;
                cout << "Owner Name: " << vehicles[i]->getOwnerName() << endl;
                time_t entry = vehicles[i]->getEntryTime();
                cout << "Entry Time: " << ctime(&entry) << endl;
                cout << "------------------------" << endl;
            }
        }   
        void ViewSlot(){

        }
        void generateReport(){

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
                break;
            case 5:
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