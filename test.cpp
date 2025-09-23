#include <iostream>
#include <mysql.h>
#include <string>
#include <ctime>

using namespace std;

class ParkingSystem {
private:
    static MYSQL* conn;

public:
    ParkingSystem() {
        conn = mysql_init(0);
        if (conn) {
            conn = mysql_real_connect(conn, "localhost", "root", "Ycpait24", "parkingdb", 3306, NULL, 0);
            if (conn) {
                cout << "Connected to MySQL successfully!\n";
            } else {
                cerr << "Connection failed: " << mysql_error(conn) << endl;
                exit(1);
            }
        } else {
            cerr << "MySQL init failed\n";
            exit(1);
        }
    }

    void addVehicle(string vno, string ownerName) {
        string query = "SELECT slotId FROM slots WHERE isOccupied=0 LIMIT 1";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);

            if (!row) {
                cout << "No slots available!\n";
                mysql_free_result(res);
                return;
            }
            int slotId = stoi(row[0]);
            mysql_free_result(res);

            // occupy slot
            query = "UPDATE slots SET isOccupied=1 WHERE slotId=" + to_string(slotId);
            mysql_query(conn, query.c_str());

            // insert vehicle
            query = "INSERT INTO vehicles(vehicleNo, ownerName) VALUES('" + vno + "','" + ownerName + "')";
            mysql_query(conn, query.c_str());

            cout << "Vehicle parked in slot " << slotId << endl;
        } else {
            cerr << "Query error: " << mysql_error(conn) << endl;
        }
    }

    void removeVehicle(string vno) {
        string query = "SELECT id, TIMESTAMPDIFF(MINUTE, entryTime, NOW()) as duration FROM vehicles WHERE vehicleNo='" + vno + "' AND exitTime IS NULL LIMIT 1";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row = mysql_fetch_row(res);

            if (!row) {
                cout << "Vehicle not found!\n";
                mysql_free_result(res);
                return;
            }
            int id = stoi(row[0]);
            double duration = stod(row[1] ? row[1] : "0");
            double charges = duration * 50;
            mysql_free_result(res);

            // update vehicle
            query = "UPDATE vehicles SET exitTime=NOW(), duration=" + to_string(duration) + ", charges=" + to_string(charges) + " WHERE id=" + to_string(id);
            mysql_query(conn, query.c_str());

            // free slot (simplified: free first occupied slot)
            query = "UPDATE slots SET isOccupied=0 WHERE isOccupied=1 LIMIT 1";
            mysql_query(conn, query.c_str());

            cout << "Vehicle exited. Duration: " << duration << " mins. Bill: Rs. " << charges << endl;
        } else {
            cerr << "Query error: " << mysql_error(conn) << endl;
        }
    }

    void viewVehicles() {
        string query = "SELECT vehicleNo, ownerName, entryTime FROM vehicles WHERE exitTime IS NULL";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row;

            if (mysql_num_rows(res) == 0) {
                cout << "No vehicles parked.\n";
                mysql_free_result(res);
                return;
            }

            while ((row = mysql_fetch_row(res))) {
                cout << "Vehicle No: " << row[0]
                     << ", Owner: " << row[1]
                     << ", Entry: " << row[2] << endl;
            }
            mysql_free_result(res);
        } else {
            cerr << "Query error: " << mysql_error(conn) << endl;
        }
    }

    void viewSlots() {
        string query = "SELECT slotId, isOccupied FROM slots";
        if (mysql_query(conn, query.c_str()) == 0) {
            MYSQL_RES* res = mysql_store_result(conn);
            MYSQL_ROW row;

            while ((row = mysql_fetch_row(res))) {
                cout << "Slot " << row[0] << " - " << (stoi(row[1]) ? "Occupied" : "Free") << endl;
            }
            mysql_free_result(res);
        } else {
            cerr << "Query error: " << mysql_error(conn) << endl;
        }
    }

    void generateReport() {
        string query1 = "SELECT COUNT(*) FROM vehicles WHERE exitTime IS NULL";
        mysql_query(conn, query1.c_str());
        MYSQL_RES* res = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(res);
        int parked = stoi(row[0]);
        mysql_free_result(res);

        string query2 = "SELECT COUNT(*) FROM slots WHERE isOccupied=0";
        mysql_query(conn, query2.c_str());
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        int freeSlots = stoi(row[0]);
        mysql_free_result(res);

        cout << "Total parked vehicles: " << parked << endl;
        cout << "Total free slots: " << freeSlots << endl;
    }
};
MYSQL* ParkingSystem::conn = nullptr;
int main() {
    ParkingSystem ps;
    int choice;
    string vno, ownerName;

    do {
        cout << "\n--- Parking Management System ---\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Exit Vehicle\n";
        cout << "3. View Parked Vehicles\n";
        cout << "4. View Slots\n";
        cout << "5. Generate Report\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Owner Name: ";
                cin >> ownerName;
                cout << "Enter Vehicle Number: ";
                cin >> vno;
                ps.addVehicle(vno, ownerName);
                break;
            case 2:
                cout << "Enter Vehicle Number: ";
                cin >> vno;
                ps.removeVehicle(vno);
                break;
            case 3:
                ps.viewVehicles();
                break;
            case 4:
                ps.viewSlots();
                break;
            case 5:
                ps.generateReport();
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
