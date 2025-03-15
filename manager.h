#ifndef MANAGER_H
#define MANAGER_H
#include<windows.h>
//#include "person.h"
#include <iostream>
using namespace std;
#include <string>

class persons{
    protected:
    string name;
    string password;
    string goal;
    int height;
    int weight;
    int age;
    int insuline_dosage;
    int sugar;
    int bp;
    public:
    persons(){                                                        //defalut constructor
        name = "unknown";
        password = "unknown";
        goal = "unknown";
        height = 0;
        weight = 0;
        age = 0;
        insuline_dosage= 0;
        sugar = 0;
        bp = 0;
    }
    persons(string n, string p, string g){                           //parameterized constructor
        name = n;
        password = p;
        goal = g;
    }
    void setName(string n){
        name = n;
    }
    string getName(){
        return name;
    }
    void setPassword(string p){
        password = p;
    }
    string getPassword(){
        return password;
    }
    /*void setGoal(string g){
        goal = g;
    }
    string getGoal(){
        return goal;*/
    void setinsuline_dosage(int s){
        insuline_dosage = s;
    }
    int getinsuline_dosage(){
        return insuline_dosage;
    }
    void setsugar(int b){
        sugar = b;
    }
    int getsugar(){
        return sugar;
    }
    void setbp(int d){
        bp = d;
    }
    int getbp(){
        return bp;
    }
    void setHeight(int h){
        height = h;
    }
    int getHeight(){
        return height;
    }
    void setWeight(int w){
        weight = w;
    }
    int getWeight(){
        return weight;
    }
    void setAge(int a){
      age = a;
    }
    int getAge(){
      return age;
    }

};
class manager{
public:
persons* person;
/*bool updategoal(persons* person);
bool workoutplanbulk(persons* person);
bool workoutplan(persons* person);
bool updateheight(persons* person);
bool updateweight(persons* person);
bool updateage(persons* person);
bool updatebench(persons* person);
bool updatesquat(persons* person);
bool updatedeadlift(persons* person);
bool bench(persons* person);*/
bool one(persons* person);
/*bool squat(persons* person);
bool deadlift(persons* person);
bool updatepr(persons* person);
bool update(persons* person);*/
void save(persons* person);
/*bool workoutplanlean(persons* person);
bool meal(persons* person);
bool mealbulk(persons* person);
bool meallean(persons* person);
bool strength(persons * person);*/
persons* storage(string name, string password);
bool play(persons* person);
bool create();
bool login();
bool menu();
bool checkname(persons* person);
bool checkpassword(persons* person);
void add(persons* person);
};
#endif
/*
class BloodSugarTracker {
private:
    struct Entry {
        string timeOfDay;
        double bloodSugarLevel;
    };

    static const int MAX_ENTRIES = 100;
    Entry entries[MAX_ENTRIES];
    int entryCount;

public:
    BloodSugarTracker() : entryCount(0) {}

    void addEntry(const string& timeOfDay, double level) {
        if (entryCount < MAX_ENTRIES) {
            entries[entryCount++] = {timeOfDay, level};
        } else {
            cout << "Error: Maximum entries reached." << endl;
        }
    }

    void displayResults() const {
        if (entryCount == 0) {
            cout << "No blood sugar records available." << endl;
            return;
        }

        double total = 0;
        double highest = entries[0].bloodSugarLevel;
        double lowest = entries[0].bloodSugarLevel;

        cout << "\nBlood Sugar Tracking Report:" << endl;
        cout << "-------------------------------------" << endl;
        cout << left << setw(15) << "Time of Day" << right << setw(15) << "Sugar Level" << endl;
        cout << "-------------------------------------" << endl;

        for (int i = 0; i < entryCount; i++) {
            cout << left << setw(15) << entries[i].timeOfDay << right << setw(15) << entries[i].bloodSugarLevel << " mg/dL" << endl;
            total += entries[i].bloodSugarLevel;
            if (entries[i].bloodSugarLevel > highest) highest = entries[i].bloodSugarLevel;
            if (entries[i].bloodSugarLevel < lowest) lowest = entries[i].bloodSugarLevel;
        }

        double average = total / entryCount;

        cout << "-------------------------------------" << endl;
        cout << "Average Level: " << average << " mg/dL" << endl;
        cout << "Highest Level: " << highest << " mg/dL" << endl;
        cout << "Lowest Level: " << lowest << " mg/dL" << endl;
    }
};

int main() {
    BloodSugarTracker tracker;
    int choice;
    string timeOfDay;
    double sugarLevel;

    do {
        cout << "\nBlood Sugar Tracker Menu" << endl;
        cout << "1. Add Blood Sugar Entry" << endl;
        cout << "2. View Report" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Time of Day (e.g., Morning, Afternoon, Night): ";
                cin >> timeOfDay;
                cout << "Enter Blood Sugar Level (in mg/dL): ";
                cin >> sugarLevel;
                tracker.addEntry(timeOfDay, sugarLevel);
                break;
            case 2:
                tracker.displayResults();
                break;
            case 3:
                cout << "Exiting the tracker. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 3);

    return 0;
}*/

