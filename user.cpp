#include "manager.h"
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <cctype>
#include <vector>
#include <sstream>
#include <iostream>
#include<windows.h>
using namespace std;
#include <string>

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
    class InsulinDosageTracker {
        private:
            struct InsulinEntry {
                string insulinType;
                double dosage;
                string timeOfDay;
            };
        
            static const int MAX_INSULIN_ENTRIES = 100;
            InsulinEntry insulinEntries[MAX_INSULIN_ENTRIES];
            int insulinEntryCount;
        
        public:
            InsulinDosageTracker() : insulinEntryCount(0) {}
        
            void addInsulinEntry(const string& insulinType, double dosage, const string& timeOfDay) {
                if (insulinEntryCount < MAX_INSULIN_ENTRIES) {
                    insulinEntries[insulinEntryCount++] = {insulinType, dosage, timeOfDay};
                } else {
                    cout << "Error: Maximum entries reached." << endl;
                }
            }
        
            double recommendDosage(double bloodSugarLevel) const {
                if (bloodSugarLevel < 70) {
                    cout<<endl<<"Hypoglycemia, no insulin needed";
                    return 0; // Hypoglycemia, no insulin needed
                } else if (bloodSugarLevel >= 70 && bloodSugarLevel <= 130) {
                    cout<<endl<<"Normal range, small dose";
                    return 2;  
                } else if (bloodSugarLevel > 130 && bloodSugarLevel <= 180) {
                    cout<<endl<<"Moderate dose";
                    return 4; // Moderate dose
                } else {
                    cout<<endl<<"High dose";
                    return 6; // High dose
                }
            }
        
            void displayInsulinResults() const {
                if (insulinEntryCount == 0) {
                    cout << "No insulin dosage records available." << endl;
                    return;
                }
        
                double totalDosage = 0;
        
                cout << "\nInsulin Dosage Monitoring Report:" << endl;
                cout << "-------------------------------------------------" << endl;
                cout << left << setw(15) << "Insulin Type" << setw(10) << "Dosage" << setw(15) << "Time of Day" << endl;
                cout << "-------------------------------------------------" << endl;
        
                for (int i = 0; i < insulinEntryCount; i++) {
                    cout << left << setw(15) << insulinEntries[i].insulinType 
                         << setw(10) << insulinEntries[i].dosage << setw(15) << insulinEntries[i].timeOfDay << endl;
                    totalDosage += insulinEntries[i].dosage;
                }
        
                cout << "-------------------------------------------------" << endl;
                cout << "Total Dosage: " << totalDosage << " units" << endl;
            }
        };
         
bool manager::menu(){
  
  cout << endl << "----------------------------------------========================================== Welcome To DiaWell ==========================================----------------------------------------" << endl << endl;
  cout << "Enter 1 to create a new account:" << endl << endl;
  cout << "Enter 2 to login:" << endl << endl;
  
  string o;
  cin >> o;

  if(o == "1"){
    if(create()){
        return true;
    }
    else{
        return false;
    }
  }
  else if(o == "2"){
    if(login()){
        return true;
    }
    else{
        return false;
    }
  }
  else{
    cout << endl << "...................................................................................... Invalid Option ...................................................................................." << endl << endl;
  }
  
  return false; 
}

bool manager::create(){
  cout << endl << ".........................................................................................................................................................................................." << endl << endl;
  cout << "To Create An Account, Please Enter Your User Name:";
  cout << "                                                                                                WARNING: DO NOT USE SPACES IN YOUR NAME!" << endl;
  cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;
  
  string name;
  cin >> name;

  if((name == "q") || (name == "Q")){
    return false;
  }

  cout << endl << ".........................................................................................................................................................................................." << endl << endl;
  cout << "Please Enter Your Password:";
  cout << "                                                                                                WARNING: DO NOT USE SPACES IN YOUR PASSWORD!" << endl;
  cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;
  
  string password;
  cin >> password;

  if((password == "q") || (password == "Q")){
    return false;
  }
  
  string goal = "unknown";
  persons* person;
  person = new persons(name, password, goal);
  

  if(!checkname(person)){
    if(!checkpassword(person)){
        cout << endl << "Congratulations, Your Account Has Been Created " << person->getName() << "!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        add(person);
        string key;
        cin >> key;
    }
    else{
        cout << endl << "Sorry But The Password Is Already In Use!" << endl << endl;
        cout << "Enter Any Key To Return To Menu" << endl << endl;
        string key;
        cin >> key;
    }
    return false;
  }
  else{
    cout << endl << "Sorry But there Is Already A User Under This Name, Please Enter Any Key To Return To Menu:" << endl << endl;
    string key;
    cin >> key;
    return false;
  }
  
  return false;
}

bool manager::checkpassword(persons* person){
ifstream fin;
  fin.open("DATA.txt");
  string temp;
  string password = person->getPassword();

  if(!fin.is_open()){
    cout << "File Not Found!" << endl;
    return 0;
  }

  while(getline(fin, temp)){
    
    istringstream ins(temp);

    string tempname;
    ins >> tempname;
    string temppassword;
    ins >> temppassword;

   

    
    if(temppassword == password){
      return true;
    }

  }
  
  fin.close();

  return false;
}

bool manager::login(){

  persons* person = nullptr;
  
  cout << endl << ".........................................................................................................................................................................................." << endl << endl;
  cout << "Please Enter Your User Name To Login: ";
  cout << "                                                                                                              WARNING: DO NOT USE SPACES IN YOUR NAME!" << endl;
  cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;

  string name;
  cin >> name;

  if((name == "q") || (name == "Q")){
    return false;
  }

  cout << endl << ".........................................................................................................................................................................................." << endl << endl;
  cout << "Please Enter Your Password: ";
  cout << "                                                                                                              WARNING: DO NOT USE SPACES IN YOUR NAME!" << endl;
  cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;

  string password;
  cin >> password;

  if((password == "q") || (password == "Q")){
    return false;
  }
  
    
  person = storage(name, password);
  if(person != nullptr){
    play(person);
    return false;
  }
    
  

  return false;
  
}
void manager::save(persons* person) {
    const int MAX_RECORDS = 1000; // Maximum number of records
    string dataArray[MAX_RECORDS];
    int recordCount = 0;

    ifstream fin("DATA.txt");
    string line;

    // Reading data from the file
    while (getline(fin, line) && recordCount < MAX_RECORDS) {
        istringstream ins(line);
        string name, password, goal;
        int height, weight, age, insuline_dosage, sugar, bp;

        if (ins >> name >> password >> goal >> height >> weight >> age >> insuline_dosage >> sugar >> bp) {
            // Store each line in the array
            dataArray[recordCount++] = line;
        }
    }
    fin.close();

    // Construct the new entry for the person
    ostringstream newPersonData;
    newPersonData << person->getName() << " " << person->getPassword() << " " //<< person->getGoal() << " "
                  << person->getHeight() << " " << person->getWeight() << " " << person->getAge() << " "
                  << person->getinsuline_dosage() << " " << person->getsugar() << " " << person->getbp();

    string newPersonString = newPersonData.str();

    // Replace old entry if exists
    bool updated = false;
    for (int i = 0; i < recordCount; i++) {
        istringstream ins(dataArray[i]);
        string name, password;
        ins >> name >> password;

        if (name == person->getName() && password == person->getPassword()) {
            dataArray[i] = newPersonString;
            updated = true;
            break;
        }
    }

    // If no existing entry is found, add the new entry
    if (!updated && recordCount < MAX_RECORDS) {
        dataArray[recordCount++] = newPersonString;
    }

    // Write the updated data back to the file
    ofstream fout("DATA.txt");
    for (int i = 0; i < recordCount; i++) {
        fout << dataArray[i] << endl;
    }
    fout.close();
}

persons* manager::storage(string name, string password) {
    const int MAX_RECORDS = 1000;
    string dataArray[MAX_RECORDS][9];
    int recordCount = 0;

    ifstream fin("DATA.txt");
    string line;

    if (!fin.is_open()) {
        cout << "File Not Found!" << endl;
        return nullptr;
    }

    // Reading data from the file
    while (getline(fin, line) && recordCount < MAX_RECORDS) {
        istringstream ins(line);
        for (int i = 0; i < 9; i++) {
            ins >> dataArray[recordCount][i];
        }
        recordCount++;
    }
    fin.close();

    int userIndex = -1;
    for (int i = 0; i < recordCount; i++) {
        if (dataArray[i][0] == name && dataArray[i][1] == password) {
            userIndex = i;
            break;
        }
    }

    if (userIndex == -1) {
        cout << "Incorrect User Name or Password!" << endl;
        cout << "Enter Any Key To Return To Menu" << endl;
        string key;
        cin >> key;
        return nullptr;
    }

    persons* user = new persons();
    user->setName(dataArray[userIndex][0]);
    user->setPassword(dataArray[userIndex][1]);
    //user->setGoal(dataArray[userIndex][2]);
    user->setHeight(stoi(dataArray[userIndex][3]));
    user->setWeight(stoi(dataArray[userIndex][4]));
    user->setAge(stoi(dataArray[userIndex][5]));
    user->setinsuline_dosage(stoi(dataArray[userIndex][6]));
    user->setsugar(stoi(dataArray[userIndex][7]));
    user->setbp(stoi(dataArray[userIndex][8]));

    return user;
}
bool manager::checkname(persons* person){
    
    ifstream fin;
    fin.open("DATA.txt");
    string temp;
    string name = person->getName();
  
    if(!fin.is_open()){
      cout << "File Not Found!" << endl;
      return 0;
    }
  
    while(getline(fin, temp)){
      
      istringstream ins(temp);
  
      string tempname;
      ins >> tempname;
  
      
      if(tempname == name){
        return true;
      }
  
    }
    
    fin.close();
  
    return false;
  
  }
  
  void manager::add(persons* person){
    
  
    string info = person->getName() + " " + person->getPassword() + " " + /*person->getGoal() + " " +*/ to_string(person->getHeight()) + " " + to_string(person->getWeight()) + " " + to_string(person->getAge()) + " " + to_string(person->getinsuline_dosage()) + " " + to_string(person->getsugar()) + " " + to_string(person->getbp()); 
    ofstream fout;
    fout.open("DATA.txt", ios_base::app);
  
    if(!fout.is_open()){
      cout << "File Not Found!" << endl;
    }
  
    fout << info << endl;
  
    
    
  
    fout.close();
  
  }
  
  bool manager::play(persons* person){
    
    cout << endl << "................................................................................. Successfully Logged In! ................................................................................" << endl << endl;
    
    if((person->getHeight() == 0) || (person->getWeight() == 0) ||(person->getAge() == 0)/* || (person->getGoal() == "unknown")*/){
      cout << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;
  
          
      int inches;
      cout << endl <<  "Please Enter Your Height In Inches (NOTE: 60 Inches is 5 Feet):" << endl << endl;
      cin >> inches;
      while(!inches){
          cout << endl <<  "Invalid Input, Please Enter Your Height In Inches(NOTE: 60 Inches is 5 Feet):" << endl << endl;
          cin.clear();
          cin.ignore();
          cin >> inches;
      }
          
      person->setHeight(inches);
  
          
      int weight;
      cout << endl <<  "Please Enter Your Weight In Pounds:" << endl << endl;
      cin >> weight;
      while(!weight){
          cout << endl <<  "Invalid Input, Please Enter Your Weight In Pounds:" << endl << endl;
          cin.clear();
          cin.ignore();
          cin >> weight;
      }
      person->setWeight(weight);
      int age;
      cout << endl <<  "Please Enter Your Age:" << endl << endl;
      cin >> age;
      while(!age){
          cout << endl <<  "Invalid Input, Please Enter Your Age:" << endl << endl;
          cin.clear();
          cin.ignore();
          cin >> age;
      }
      person->setAge(age);
      save(person);
      bool run = true;

  while(run){
    cout << endl << "...................................................................................... Welcome " << person->getName() << "! ....................................................................................." << endl << endl;

    cout << endl << "Enter 1 For Your Personalized Blood Sugar Report:" << endl << endl;
    cout << "Enter 2 For Your Personalized Insuline Dosage Report:" << endl << endl;
    cout << "Enter 3 For Your Personalized Meal Plan:" << endl << endl;
    cout << "Enter 4 For Your Diabetic Test:" << endl << endl;
    cout << "Enter 5 For Water and Sleep Tracker" << endl << endl;
    cout << "Enter 6 To Update Stats:" << endl << endl;
    cout << "Enter 7 To Exit:" << endl << endl;
    
    string o;
    cin >> o;
    
    if(o == "1"){
      //workoutplan(person);
    BloodSugarTracker tracker;
    string timeOfDay;
    double sugarLevel;
    int choice;

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
    }
    else if(o == "2"){
        int choice;
        InsulinDosageTracker tracker;
        string insulinType;
        double dosage;
        string timeOfDay;
        double bloodSugarLevel;
        do {
            cout << "\nHealth Monitoring System Menu" << endl;
            cout << "\nInsulin Dosage Tracker Menu" << endl;
            cout << "1. Add Insulin Dosage Entry" << endl;
            cout << "2. View Dosage Report" << endl;
            cout << "3. Get Recommended Dosage" << endl;
            cout << "4. Exit" << endl;
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter Insulin Type (e.g., Rapid, Long-acting): ";
                    cin >> insulinType;
                    cout << "Enter Dosage (in units): ";
                    cin >> dosage;
                    cout << "Enter Time of Day (e.g., Morning, Afternoon, Night): ";
                    cin >> timeOfDay;
                    tracker.addInsulinEntry(insulinType, dosage, timeOfDay);
                    break;
                case 2:
                    tracker.displayInsulinResults();
                    break;
                case 3:
                    cout << "Enter Current Blood Sugar Level (mg/dL): ";
                    cin >> bloodSugarLevel;
                    cout << "Recommended Insulin Dosage: " << tracker.recommendDosage(bloodSugarLevel) << " units" << endl;
                    break;
                case 4:
                    cout << "Exiting the tracker. Goodbye!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            } 
                } while (choice != 4);
                return false;
            }  
        }
    }
  } 