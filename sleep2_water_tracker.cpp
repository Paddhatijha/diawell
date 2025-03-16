#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class HealthTracker {
private:
    string username;
    string filename;

public:
    // Constructor to set the username and file
    HealthTracker(string user) {
        username = user;
        filename = username + "_health_data.txt"; // Unique file for each user
    }

    // Function to display a single record
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

    // Function to add a new record
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
            cout << "Data saved successfully!\n";
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

        cout << "\n--- Health Records for " << username << " ---\n";
        while (file >> date >> sleep >> water) {
            displayRecord(date, sleep, water);
        }

        file.close();
    }

    // Function to view a specific date's record
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
                break;
            }
        }

        if (!found) {
            cout << "No record found for " << searchDate << ".\n";
        }

        file.close();
    }
};

// Function to register a new user
void registerUser() {
    string username, password;
    cout << "Enter a new username: ";
    cin >> username;
    cout << "Enter a password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << "\n";
    file.close();

    cout << "User registered successfully!\n";
}

// Function to log in an existing user
bool loginUser(string &username) {
    string inputUser, inputPass, storedUser, storedPass;
    cout << "Enter username: ";
    cin >> inputUser;
    cout << "Enter password: ";
    cin >> inputPass;

    ifstream file("users.txt");
    bool loginSuccess = false;
    while (file >> storedUser >> storedPass) {
        if (inputUser == storedUser && inputPass == storedPass) {
            loginSuccess = true;
            username = inputUser;
            break;
        }
    }
    file.close();

    if (loginSuccess) {
        cout << "Login successful! Welcome, " << username << "!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
    return loginSuccess;
}

int main() {
    int option;
    string username;

    do {
        cout << "\n1. Register\n2. Login\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> option;

        if (option == 1) {
            registerUser();
        } else if (option == 2) {
            if (loginUser(username)) {
                HealthTracker tracker(username);
                int choice;

                do {
                    cout << "\n1. Add Record\n2. View All Records\n3. View Record by Date\n4. Logout\n";
                    cout << "Enter choice: ";
                    cin >> choice;

                    if (choice == 1) tracker.addRecord();
                    else if (choice == 2) tracker.viewRecords();
                    else if (choice == 3) tracker.viewRecordByDate();
                    else if (choice != 4) cout << "Invalid choice. Try again.\n";

                } while (choice != 4);

                cout << "Logged out.\n";
            }
        } else if (option != 3) {
            cout << "Invalid option. Try again.\n";
        }

    } while (option != 3);

    cout << "Goodbye!\n";
    return 0;
}
