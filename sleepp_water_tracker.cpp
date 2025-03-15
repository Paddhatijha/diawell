#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class HealthTracker {
private:
    string filename = "health_data.txt"; 

public:
   // Function to display record
    void displayRecord(string date, float sleep, float water) {
        cout << "\n--- Record for " << date << " ---\n";
        cout << "Sleep: " << sleep << " hours ";
        if (sleep < 6) cout << "(Too little!)";
        else if (sleep > 9) cout << "(Too much!)";
        cout << "\n";

        cout << "Water: " << water << "L ";
        if (water < 2) cout << "(Drink more!)";
        else if (water > 5) cout << "(Too much!)";
        cout << "\n";
    }

    // Function to add daily record
    void addRecord() {
        string date;
        float sleep, water;

        cout << "\nEnter date (YYYY-MM-DD): ";
        cin >> date;
        cout << "Enter sleep hours: ";
        cin >> sleep;
        cout << "Enter water intake (liters): ";
        cin >> water;

        ofstream file(filename, ios::app); 
        if (file) {
            file << date << " " << sleep << " " << water << "\n";
            cout << "Data saved!\n";
        } else {
            cout << "Error saving data.\n";
        }
        file.close();
    }

    // Function to view all records
    void viewRecords() {
        ifstream file(filename);
        if (!file) {
            cout << "No previous records found.\n";
            return;
        }

        string date;
        float sleep, water;

        cout << "\n--- Health Records ---\n";
        while (file >> date >> sleep >> water) {
            displayRecord(date, sleep, water); // Now accessible anywhere
        }

        file.close();
    }

    // Function to view records of a specific date
    void viewRecordByDate() {
        ifstream file(filename);
        if (!file) {
            cout << "No previous records found.\n";
            return;
        }

        string searchDate, date;
        float sleep, water;
        bool found = false;

        cout << "Enter date to search (YYYY-MM-DD): ";
        cin >> searchDate;

        while (file >> date >> sleep >> water) {
            if (date == searchDate) {
                displayRecord(date, sleep, water);
                found = true;
                break; // Stop searching after finding the record
            }
        }

        if (!found) {
            cout << "No record found for " << searchDate << ".\n";
        }

        file.close();
    }
};

int main() {
    HealthTracker tracker;
    int choice;

    do {
        cout << "\n1. Add Record\n2. View All Records\n3. View Record by Date\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) tracker.addRecord();
        else if (choice == 2) tracker.viewRecords();
        else if (choice == 3) tracker.viewRecordByDate();
        else if (choice != 4) cout << "Invalid choice. Try again.\n";

    } while (choice != 4);

    cout << "Exit\n";
    return 0;
}


