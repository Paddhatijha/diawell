#include <fstream>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <limits>
#include<conio.h>
#include <iostream>
using namespace std;
#include <string>
class persons {
    protected:
        string name;
        string password;
        int height;
        int weight;
        int age;
    
    public:
        persons() { // Default constructor
            name = "unknown";
            password = "unknown";
            height = 0;
            weight = 0;
            age = 0;
        }
    
        persons(string n, string p) { // Parameterized constructor
            name = n;
            password = p;
            height = 0;
            weight = 0;
            age = 0;
        }

    
        void setName(string n) {
            name = n;
        }
        string getName() const {
            return name;
        }
    
        void setPassword(string p) {
            password = p;
        }
    
        string getPassword() {
            return password;
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
class manager: public persons{
    public:
    persons* person;
    bool one(persons* person);
    void save(persons* person);
    persons* storage(string name, string password);
    bool play(persons* person);
    bool options(persons* person);
    bool create();
    bool login();
    bool menu();
    bool checkname(persons* person);
    bool checkpassword(persons* person);
    void add(persons* person);
    };
    class BloodSugarTracker : public persons {
        protected:
            struct Entry {
                string date;    
                string timeOfDay;
                double bloodSugarLevel;
            };
        
            static const int MAX_ENTRIES = 100;
            Entry entries[MAX_ENTRIES];
            int entryCount;
        
        public:
            BloodSugarTracker() : entryCount(0) {}
        
            void addEntry(const string& date, const string& timeOfDay, double bloodSugarLevel) {
                if (entryCount < MAX_ENTRIES) {
                    entries[entryCount++] = {date, timeOfDay, bloodSugarLevel};
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
                cout << "-----------------------------------------------------" << endl;
                cout <<left<< setw(12) << "Date" << setw(15) << "Time of Day" 
                     << right << setw(15) << "Sugar Level" << endl;
                cout << "-----------------------------------------------------" << endl;
        
                for (int i = 0; i < entryCount; i++) {
                    cout << left << setw(12) << entries[i].date 
                         << setw(15) << entries[i].timeOfDay 
                         << right << setw(15) << entries[i].bloodSugarLevel << " mg/dL" << endl;
                    total += entries[i].bloodSugarLevel;
                    if (entries[i].bloodSugarLevel > highest) highest = entries[i].bloodSugarLevel;
                    if (entries[i].bloodSugarLevel < lowest) lowest = entries[i].bloodSugarLevel;
                }
        
                double average = total / entryCount;
        
                cout << "-----------------------------------------------------" << endl;
                cout << "Average Level: " << average << " mg/dL" << endl;
                cout << "Highest Level: " << highest << " mg/dL" << endl;
                cout << "Lowest Level: " << lowest << " mg/dL" << endl;
            }
        
            void saveToFile(const string& username, const string& password) const {
                string filename = username + "_" + password + "_blood_sugar.txt";
                cout << "Attempting to save data to file: " << filename << endl;
                ofstream fout(filename, ios::trunc);
                if (!fout.is_open()) {
                    cout << "Error: Could not open file for saving blood sugar data. Check file path or permissions." << endl;
                    return;
                }
        
                // Save username and password at the beginning of the file
                fout << "Username: " << username << endl;
                fout << "Password: " << password << endl;
                fout << "-------------------------------------" << endl;
        
                // Save blood sugar entries with date
                for (int i = 0; i < entryCount; i++) {
                    fout << entries[i].date << " " 
                         << entries[i].timeOfDay << " " 
                         << entries[i].bloodSugarLevel << endl;
                }
        
                fout.close();
                cout << "Data saved to file: " << filename << endl;
            }
        
            void loadFromFile(const string& username, const string& password) {
                string filename = username + "_" + password + "_blood_sugar.txt";
                ifstream fin(filename);
                if (!fin.is_open()) {
                    cout << "No existing blood sugar data found." << endl;
                    return;
                }
        
                // Read and ignore the username and password lines
                string line;
                getline(fin, line); // Username line
                getline(fin, line); // Password line
                getline(fin, line); // Separator line
        
                // Read blood sugar entries with date
                entryCount = 0;
                string date, timeOfDay;
                double bloodSugarLevel;
        
                while (fin >> date >> timeOfDay >> bloodSugarLevel && entryCount < MAX_ENTRIES) {
                    entries[entryCount++] = {date, timeOfDay, bloodSugarLevel};
                }
        
                fin.close();
            }
        };
        class InsulinDosageTracker : public persons {
            protected:
                struct InsulinEntry {
                    string date;
                    string insulinType;
                    double dosage;
                    string timeOfDay;
                };
            
                static const int MAX_INSULIN_ENTRIES = 100;
                InsulinEntry insulinEntries[MAX_INSULIN_ENTRIES];
                int insulinEntryCount;
            
            public:
                InsulinDosageTracker() : insulinEntryCount(0) {}
            
                void addInsulinEntry(const string& date,const string& insulinType, double dosage, const string& timeOfDay) {
                    if (insulinEntryCount < MAX_INSULIN_ENTRIES) {
                        insulinEntries[insulinEntryCount++] = {date,insulinType, dosage, timeOfDay};
                    } else {
                        cout << "Error: Maximum entries reached." << endl;
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
                    cout << left << setw(12) << "Date" << setw(15) << "Insulin Type" << setw(10) << "Time of Day" << right << setw(15) << "Dosage" << endl;
                    cout << "-------------------------------------------------" << endl;
            
                    for (int i = 0; i < insulinEntryCount; i++) {
                        cout << left << setw(12) << insulinEntries[i].date  << setw(15) << insulinEntries[i].insulinType 
                             << setw(10) << insulinEntries[i].timeOfDay <<right <<setw(15) << insulinEntries[i].dosage << endl;
                        totalDosage += insulinEntries[i].dosage;
                    }
            
                    cout << "-------------------------------------------------" << endl;
                    cout << "Total Dosage: " << totalDosage << " units" << endl;
                }
            
                void saveToFile(const string& username, const string& password) const {
                    string filename = username + "_" + password + "_insulin.txt";
                    cout << "Attempting to save data to file: " << filename << endl; // Debugging output
                    ofstream fout(filename, ios::trunc); // Overwrite the file if it exists
                    if (!fout.is_open()) {
                        cout << "Error: Could not open file for saving insulin data. Check file path or permissions." << endl;
                        return;
                    }
            
                    // Save username and password at the beginning of the file
                    fout << "Username: " << username << endl;
                    fout << "Password: " << password << endl;
                    fout << "-------------------------------------" << endl;
            
                    // Save insulin dosage entries
                    for (int i = 0; i < insulinEntryCount; i++) {
                    fout<< insulinEntries[i].date << " " 
                             << insulinEntries[i].insulinType << " " 
                             << insulinEntries[i].dosage << " " 
                             << insulinEntries[i].timeOfDay << endl;
                    }
            
                    fout.close();
                    cout << "Data saved to file: " << filename << endl; // Debugging output
                }
            
                void loadFromFile(const string& username, const string& password) {
                    string filename = username + "_" + password + "_insulin.txt";
                    ifstream fin(filename);
                    if (!fin.is_open()) {
                        cout << "No existing insulin data found." << endl;
                        return;
                    }
            
                    // Read and ignore the username and password lines
                    string line;
                    getline(fin, line); // Username line
                    getline(fin, line); // Password line
                    getline(fin, line); // Separator line
            
                    // Read insulin dosage entries
                    insulinEntryCount = 0;
                    string date,insulinType, timeOfDay;
                    double dosage;
            
                    while (fin >> date>>insulinType >> dosage >> timeOfDay && insulinEntryCount < MAX_INSULIN_ENTRIES) {
                        insulinEntries[insulinEntryCount++] = {date,insulinType, dosage, timeOfDay};
                    }
            
                    fin.close();
                }
            double recommendDosage(double bloodSugarLevel) const {
                if (bloodSugarLevel < 70) {
                    cout<<endl<<"Hypoglycemia, no insulin needed"<<endl;
                    return 0; // Hypoglycemia, no insulin needed
                } else if (bloodSugarLevel >= 70 && bloodSugarLevel <= 130) {
                    cout<<endl<<"Normal range, small dose"<<endl;
                    return 2;  
                } else if (bloodSugarLevel > 130 && bloodSugarLevel <= 180) {
                    cout<<endl<<"Moderate dose"<<endl;
                    return 4; // Moderate dose
                } else {
                    cout<<endl<<"High dose"<<endl;
                    return 6; // High dose
                }
            }
        };
        class Questionnaire : public persons {
            protected:
                int score; // Risk score calculated from answers
            
            public:
                Questionnaire() { score = 0; } // Constructor initializes score to 0
            
                // Function to ask a question and return score
                int askQuestion(string question, int low, int moderate, int high) {
                    int choice;
                    cout << question << "\n";
                    cout << "1. Low risk \n";
                    cout << "2. Moderate risk \n";
                    cout << "3. High risk \n";
                    cout << "Enter choice (1/2/3): ";
                    cin >> choice;
            
                    // Assign points based on user's choice
                    if (choice == 1) return low;
                    else if (choice == 2) return moderate;
                    else return high;
                }
            
                // Function to conduct the questionnaire
                void conductTest() {
                    cout << "\n--- Diabetes Risk Assessment ---\n";
            
                    // Asking questions and adding to score
                    score += askQuestion("1. Age Group:\n   Below 30 (Low) | 30-50 (Moderate) | Above 50 (High)", 0, 2, 4);
                    score += askQuestion("2. Family history of diabetes:\n   None (Low) | One close relative (Moderate) | More than one (High)", 0, 2, 4);
                    score += askQuestion("3. Weight Category:\n   Normal (Low) | Overweight (Moderate) | Obese (High)", 0, 2, 4);
                    score += askQuestion("4. Physical Activity Level:\n   Active (Low) | Moderate (Moderate) | Sedentary (High)", 0, 2, 4);
                    score += askQuestion("5. Sugar consumption:\n   Rarely (Low) | Occasionally (Moderate) | Frequently (High)", 0, 2, 4);
                    score += askQuestion("6. Sleep Quality:\n   Good (Low) | Disturbed (Moderate) | Poor (High)", 0, 2, 4);
                    score += askQuestion("7. Frequent thirst:\n   No (Low) | Sometimes (Moderate) | Always (High)", 0, 2, 4);
                    score += askQuestion("8. Frequent urination:\n   No (Low) | Sometimes (Moderate) | Always (High)", 0, 2, 4);
                    score += askQuestion("9. Sudden weight loss:\n   No (Low) | Mild (Moderate) | Significant (High)", 0, 2, 4);
                    score += askQuestion("10. Fatigue levels:\n   Normal (Low) | Sometimes tired (Moderate) | Constantly exhausted (High)", 0, 2, 4);
                    score += askQuestion("11. Frequent infections or slow healing:\n   No (Low) | Occasionally (Moderate) | Frequently (High)", 0, 2, 4);
                    score += askQuestion("12. Numbness or tingling in hands/feet:\n   No (Low) | Sometimes (Moderate) | Frequently (High)", 0, 2, 4);
                    score += askQuestion("13. Blurred vision:\n   No (Low) | Sometimes (Moderate) | Frequently (High)", 0, 2, 4);
                    score += askQuestion("14. Skin darkening in folds:\n   No (Low) | Mild (Moderate) | Severe (High)", 0, 2, 4);
                    score += askQuestion("15. High blood sugar in previous tests:\n   No (Low) | Occasionally (Moderate) | Frequently (High)", 0, 2, 4);
                    score += askQuestion("16. High blood pressure or cholesterol:\n   No (Low) | One condition (Moderate) | Both conditions (High)", 0, 2, 4);
                    score += askQuestion("17. Unexplained dizziness or fainting:\n   No (Low) | Sometimes (Moderate) | Frequently (High)", 0, 2, 4);
                }
            
                // Function to return the total score
                int getScore() { return score; }
            };
            
        class DiabetesRiskEvaluator : public Questionnaire {
            private:
                persons* user; // Pointer to the persons object
            
            public:
                // Constructor to initialize with a persons object
                DiabetesRiskEvaluator(persons* u) : user(u) {}
            
                // Function to evaluate and display results
                void displayResults() {
                    cout << "\n--- Diabetes Risk Evaluation ---\n";
                    if (score <= 8) {
                        cout << " Low Risk: No immediate concern. Maintain a healthy lifestyle.\n";
                    } else if (score <= 18) {
                        cout << " Moderate Risk: Consider a health check-up and improve diet & exercise.\n";
                    } else if (score <= 30) {
                        cout << " High Risk: Schedule a doctor's appointment soon and get tested.\n";
                    } else {
                        cout << " Critical Risk: Seek **immediate** medical consultation!\n";
                    }
            
                    // Save results to file
                    saveResults();
                }
            
                // Function to save results to a file
                void saveResults() {
                    string filename = user->getName() + "_" + user->getPassword() + "_DiabetesReport.txt";
                    ofstream file(filename);
                    if (file.is_open()) {
                        file << "Diabetes Risk Assessment Report\n";
                        file << "------------------------------\n";
                        file << "Username: " << user->getName() << "\n";
                        file << "Password: " << user->getPassword() << "\n";
                        file << "Total Score: " << score << "\n";
            
                        if (score <= 8) {
                            file << " Low Risk: No immediate concern.\n";
                        } else if (score <= 18) {
                            file << " Moderate Risk: Consider a health check-up.\n";
                        } else if (score <= 30) {
                            file << " High Risk: Schedule a doctor's appointment.\n";
                        } else {
                            file << " Critical Risk: Immediate medical consultation required!\n";
                        }
            
                        file.close();
                        cout << " Results saved to '" << filename << "'.\n";
                    } else {
                        cout << " Error saving results!\n";
                    }
                }
            };      
            class MealPlanner : public persons {
                private:

                    float weight, height, bmi;
                    string sugarLevel,date; // Low, Normal, or High blood sugar level
                    persons* user; // Pointer to the persons object
                
                public:
                    // Constructor to initialize with a persons object
                    MealPlanner(persons* u) : user(u) {}
                
                    // Function to take user input
                    void getUserData() {
                        /*cout << "Enter your weight (kg): ";
                        cin >> weight;
                        cout << "Enter your height (m): ";
                        cin >> height;*/
                        weight = user ->getWeight();
                        cout<<weight;
                        height=user->getHeight();
                        cout<<height;
                        cout << "\nEnter date (YYYY-MM-DD): ";
                        cin>>date;
                        cout << "Enter your blood sugar level (Low/Normal/High): ";
                        cin >> sugarLevel;
                    }
                
                    // Function to calculate BMI
                    void calculateBMI() {
                        bmi = weight / (height * height);
                        cout << "\nYour BMI is: " << bmi << endl;
                    }
                
                    // Function to generate and display meal plan
                    void suggestMealPlan() {
                        cout << "\n--- Personalized Meal Plan ---\n";
                
                        // Underweight Meal Plan
                        if (bmi < 18.5) {
                            cout << " Underweight: Increase calorie intake with healthy carbs and proteins.\n";
                            cout << "Breakfast Options:\n"
                                 << "- Oatmeal with nuts & honey + Banana + Full-fat milk\n"
                                 << "- Peanut butter toast + Apple + Almond milk\n"
                                 << "- Scrambled eggs + Whole wheat bread + Avocado smoothie\n";
                            cout << "Lunch Options:\n"
                                 << "- Brown rice + Lentils + Chicken/Fish + Vegetables\n"
                                 << "- Whole wheat pasta + Grilled chicken + Yogurt\n"
                                 << "- Paneer curry + Roti + Chia pudding\n";
                            cout << "Dinner Options:\n"
                                 << "- Whole wheat chapati + Paneer curry + Avocado salad\n"
                                 << "- Quinoa + Lentil soup + Nuts\n"
                                 << "- Fish curry + Steamed rice + Mixed greens\n";
                        }
                        // Normal Weight Meal Plan
                        else if (bmi >= 18.5 && bmi <= 24.9) {
                            cout << " Normal Weight: Maintain a balanced diet with proteins, fiber, and healthy fats.\n";
                            cout << "Breakfast Options:\n"
                                 << "- Whole wheat toast + Scrambled eggs + Fresh fruit\n"
                                 << "- Greek yogurt + Granola + Berries\n"
                                 << "- Poha with peanuts + Green tea\n";
                            cout << "Lunch Options:\n"
                                 << "- Quinoa + Grilled chicken + Steamed veggies + Yogurt\n"
                                 << "- Dal + Brown rice + Green salad + Cottage cheese\n"
                                 << "- Lentil soup + Whole grain bread + Nuts\n";
                            cout << "Dinner Options:\n"
                                 << "- Stir-fried tofu + Brown rice + Vegetable soup\n"
                                 << "- Grilled salmon + Roasted sweet potatoes + Steamed broccoli\n"
                                 << "- Vegetable khichdi + Cucumber raita\n";
                        }
                        // Overweight Meal Plan
                        else if (bmi >= 25 && bmi <= 29.9) {
                            cout << "Overweight: Reduce carbs and increase fiber intake.\n";
                            cout << "Breakfast Options:\n"
                                 << "- Boiled eggs + Spinach smoothie + Almonds\n"
                                 << "- Chia pudding + Walnuts + Black coffee\n"
                                 << "- Sprouts salad + Herbal tea\n";
                            cout << "Lunch Options:\n"
                                 << "- Grilled salmon + Mixed greens + Olive oil dressing\n"
                                 << "- Tofu stir-fry + Cauliflower rice + Steamed broccoli\n"
                                 << "- Lentil soup + Cabbage salad + Greek yogurt\n";
                            cout << "Dinner Options:\n"
                                 << "- Stir-fried tofu + Quinoa + Steamed broccoli\n"
                                 << "- Grilled fish + Roasted vegetables + Greek yogurt\n"
                                 << "- Spinach and mushroom omelet + Whole wheat bread\n";
                        }
                        // Obese Meal Plan
                        else {
                            cout << " Obese: Follow a low-carb, high-protein diet.\n";
                            cout << "Breakfast Options:\n"
                                 << "- Chia seed pudding + Walnuts + Green tea\n"
                                 << "- Scrambled eggs with spinach + Herbal tea\n"
                                 << "- Keto smoothie (Almond milk + Chia seeds + Berries)\n";
                            cout << "Lunch Options:\n"
                                 << "- Lean chicken breast + Cauliflower rice + Spinach\n"
                                 << "- Zucchini noodles + Pesto sauce + Grilled salmon\n"
                                 << "- Boiled eggs + Avocado + Cabbage salad\n";
                            cout << "Dinner Options:\n"
                                 << "- Grilled fish + Roasted vegetables + Greek yogurt\n"
                                 << "- Stir-fried mushrooms + Tofu + Green salad\n"
                                 << "- Cottage cheese with flaxseeds + Mixed nuts\n";
                        }
                
                        // Sugar Level Adjustments
                        if (sugarLevel == "High") {
                            cout << "\n **High Blood Sugar Alert!** Adjustments:\n";
                            cout << "- Avoid sugary drinks, white bread, and processed foods.\n";
                            cout << "- Stick to whole grains and lean proteins.\n";
                            cout << "- Use natural sweeteners like stevia instead of sugar.\n";
                        } else if (sugarLevel == "Low") {
                            cout << "\n**Low Blood Sugar Alert!** Adjustments:\n";
                            cout << "- Include slow-digesting carbs like oats and sweet potatoes.\n";
                            cout << "- Snack on nuts, yogurt, or fruit between meals.\n";
                            cout << "- Avoid skipping meals to maintain steady sugar levels.\n";
                        }
                
                        saveMealPlan(); // Save the meal plan to a file
                    }
                
                    // Function to save meal plan to a file
                    void saveMealPlan() {
                        string filename = user->getName() + "_" + user->getPassword() + "_MealPlan.txt";
                        ofstream file(filename);
                        if (file.is_open()) {
                            file << "BMI-Based & Blood Sugar Level Meal Plan\n";
                            file << "---------------------------------------\n";
                            file << "Username: " << user->getName() << "\n";
                            file << "Password: " << user->getPassword() << "\n";
                            file <<endl<<"Date: "<<date<<"\n";
                            file << "BMI: " << bmi << "\n";
                
                            if (bmi < 18.5) {
                                file << "Underweight: High-calorie meals.\n";
                                file << "Breakfast: Oatmeal with nuts, Peanut butter toast, Scrambled eggs.\n";
                                file << "Lunch: Brown rice with chicken, Whole wheat pasta, Paneer curry.\n";
                                file << "Dinner: Roti with paneer, Quinoa with soup, Fish curry with rice.\n";
                            } else if (bmi >= 18.5 && bmi <= 24.9) {
                                file << "Normal Weight: Balanced diet.\n";
                                file << "Breakfast: Scrambled eggs, Greek yogurt, Poha.\n";
                                file << "Lunch: Quinoa with chicken, Dal with rice, Lentil soup with bread.\n";
                                file << "Dinner: Stir-fry tofu, Grilled salmon, Vegetable khichdi.\n";
                            } else if (bmi >= 25 && bmi <= 29.9) {
                                file << " Overweight: Low-carb, high-fiber diet.\n";
                                file << "Breakfast: Boiled eggs, Chia pudding, Sprouts salad.\n";
                                file << "Lunch: Grilled salmon, Tofu stir-fry, Lentil soup.\n";
                                file << "Dinner: Stir-fried tofu, Grilled fish, Spinach omelet.\n";
                            } else {
                                file << " Obese: Strict low-carb, high-protein diet.\n";
                                file << "Breakfast: Chia pudding, Scrambled eggs, Keto smoothie.\n";
                                file << "Lunch: Chicken with cauliflower rice, Zucchini noodles, Avocado salad.\n";
                                file << "Dinner: Grilled fish, Stir-fried mushrooms, Cottage cheese with flaxseeds.\n";
                            }
                
                            if (sugarLevel == "High") {
                                file << "\n High Sugar: Avoid processed sugars and refined carbs.\n";
                            } else if (sugarLevel == "Low") {
                                file << "\n Low Sugar: Eat steady, slow-digesting carbs throughout the day.\n";
                            }
                
                            file.close();
                            cout << "\n Meal plan saved to '" << filename << "'.\n";
                        } else {
                            cout << " Error saving meal plan!\n";
                        }
                    }
                };    
class HealthTracker : public persons {
private:
    string filename;

public:
    // Constructor to set the username and file
    HealthTracker(persons* u) : persons(u->getName(),u->getPassword()) {
        // Set the filename based on the user's name
        filename = getName() +getPassword()+ "_health_records.txt";
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

        cout << "\n--- Health Records for " << getName() << getPassword()<< " ---\n";
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
bool manager::menu(){
  int i;
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
        return false;
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
  
    // Get user details during account creation
    cout << endl << "WARNING: ONLY NUMERICAL VALUES ALLOWED!" << endl << endl;
    
    int inches;
    cout << endl << "Please Enter Your Height In Inches (NOTE: 60 Inches is 5 Feet):" << endl << endl;
    cin >> inches;
    while(!inches){
        cout << endl << "Invalid Input, Please Enter Your Height In Inches(NOTE: 60 Inches is 5 Feet):" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> inches;
    }
    
    int weight;
    cout << endl << "Please Enter Your Weight In Pounds:" << endl << endl;
    cin >> weight;
    while(!weight){
        cout << endl << "Invalid Input, Please Enter Your Weight In Pounds:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> weight;
    }
    
    int age;
    cout << endl << "Please Enter Your Age:" << endl << endl;
    cin >> age;
    while(!age){
        cout << endl << "Invalid Input, Please Enter Your Age:" << endl << endl;
        cin.clear();
        cin.ignore();
        cin >> age;
    }
  
    // Create person with all details
    persons* person = new persons(name, password);
    person->setHeight(inches);
    person->setWeight(weight);
    person->setAge(age);
  
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
  
  bool manager::play(persons* person){
    cout << endl << "................................................................................. Successfully Logged In! ................................................................................" << endl << endl;
    // No need to ask for height/weight/age here as they're collected during creation
    return true;
  }
  bool manager::login() {
    persons* person = nullptr;
    
    cout << endl << ".........................................................................................................................................................................................." << endl << endl;
    cout << "Please Enter Your User Name To Login: ";
    cout << "                                                                                                              WARNING: DO NOT USE SPACES IN YOUR NAME!" << endl;
    cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;

    string name;
    cin >> name;

    if ((name == "q") || (name == "Q")) {
        return false;
    }

    cout << endl << ".........................................................................................................................................................................................." << endl << endl;
    cout << "Please Enter Your Password: ";
    cout << "               WARNING: DO NOT USE SPACES IN YOUR NAME!" << endl;
    cout << endl << "Or Enter Q To Return To Menu:" << endl << endl;

    string password;
    char ch;
    
    while (true) {
        ch = _getch(); 
        if (ch == '\r') { 
            break;
        } else if (ch == '\b' && !password.empty()) { 
            cout << "\b \b"; 
            password.pop_back();
        } else if (ch != '\b') {
            cout << '*'; 
            password += ch;
        }
    }

    cout << endl;

    if ((password == "q") || (password == "Q")) {
        return false;
    }

    person = storage(name, password);
    if (person != nullptr) {
        play(person);
        options(person);
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

void manager::save(persons* person) {
    const int MAX_RECORDS = 1000; // Maximum number of records
    string dataArray[MAX_RECORDS];
    int recordCount = 0;

    ifstream fin("DATA.txt");
    string line;

    // Reading data from the file
    while (getline(fin, line) && recordCount < MAX_RECORDS) {
        istringstream ins(line);
        string name, password;
        int height, weight, age;

        if (ins >> name >> password >> height >> weight >> age ) {
            // Store each line in the array
            dataArray[recordCount++] = line;
        }
    }
    fin.close();

    // Construct the new entry for the person
    ostringstream newPersonData;
    newPersonData << person->getName() << " " << person->getPassword() << " " 
                  << person->getHeight() << " " << person->getWeight() << " " << person->getAge() ;

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
    if (!fin.is_open()) {
        cout << "File Not Found!" << endl;
        return nullptr;
    }

    string line;
    while (getline(fin, line) && recordCount < MAX_RECORDS) {
        istringstream ins(line);
        for (int i = 0; i < 9; i++) {
            if (!(ins >> dataArray[recordCount][i])) {
                dataArray[recordCount][i] = ""; // If data is missing, assign empty string
            }
        }
        recordCount++;
    }
    fin.close();

    // Searching for the user in the data
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
    user->setName(dataArray[userIndex][0]); // Set name
    user->setPassword(dataArray[userIndex][1]); // Set password

    // Convert and set other fields
    try {
        user->setHeight(stoi(dataArray[userIndex][3]));
    } catch (...) {
        user->setHeight(0); // Default value if data is invalid
    }

    try {
        user->setWeight(stoi(dataArray[userIndex][4]));
    } catch (...) {
        user->setWeight(0);
    }

    try {
        user->setAge(stoi(dataArray[userIndex][5]));
    } catch (...) {
        user->setAge(0);
    }
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
    ofstream fout;
    string info = person->getName() + " " + person->getPassword() + " " +  to_string(person->getHeight()) + " " + to_string(person->getWeight()) + " " + to_string(person->getAge());
    fout.open("DATA.txt", ios_base::app);
  
    if(!fout.is_open()){
      cout << "File Not Found!" << endl;
    }
  
    fout << info << endl;
  
    fout.close();
  
  }
  bool manager::options(persons* person) {
    string o;
    while(1) {
        // Main Menu Header
        cout << "\n\n";
        cout << "===============================================================================\n";
        cout << "                            WELCOME " << person->getName() << "!\n";
        cout << "===============================================================================\n\n";

        // Main Menu Options
        cout << "+------------------------------------------------------------------------------+\n";
        cout << "|                             MAIN MENU OPTIONS                                |\n";
        cout << "+-----+-----------------------------------------------------------------------+\n";
        cout << "|  1  | Personalized Blood Sugar Report                                       |\n";
        cout << "|  2  | Personalized Insulin Dosage Report                                    |\n";
        cout << "|  3  | Personalized Meal Plan                                                |\n";
        cout << "|  4  | Diabetic Risk Assessment Test                                         |\n";
        cout << "|  5  | Water and Sleep Tracker                                               |\n";
        cout << "|  6  | Exit Program                                                          |\n";
        cout << "+-----+-----------------------------------------------------------------------+\n\n";
        cout << "Enter your choice (1-6): ";
        cin >> o;

        if (o == "1") {
            BloodSugarTracker tracker;
            string timeOfDay;
            double sugarLevel;
            int choice;

            string name = person->getName();
            string password = person->getPassword();
            tracker.loadFromFile(name, password);

            do {
                cout << "\n==============================================================\n";
                cout << "                   BLOOD SUGAR TRACKER MENU                   \n";
                cout << "--------------------------------------------------------------\n";
                cout << "1. Add a new blood sugar entry                               \n";
                cout << "2. View all entries and statistics                           \n";
                cout << "3. Return to Main Menu                                       \n";
                cout << "--------------------------------------------------------------\n";
                cout << "Enter your choice (1-3): ";
                cin >> choice;

                switch (choice) {
                    case 1: {
                        string date;
                        cout << "\n+-------------------------------------------------------------+\n";
                        cout << "|                     ADD BLOOD SUGAR ENTRY                   |\n";
                        cout << "+-------------------------------------------------------------+\n";
                        cout << "| Enter date (YYYY-MM-DD): ";
                        cin >> date;
                        cout << "| Enter time of day (Morning/Afternoon/Evening/Fasting): ";
                        cin >> timeOfDay;
                        cout << "| Enter blood sugar level (mg/dL): ";
                        cin >> sugarLevel;
                        cout << "+-------------------------------------------------------------+\n";
                        
                        tracker.addEntry(date, timeOfDay, sugarLevel);
                        tracker.saveToFile(name, password);
                        cout << "\n==============================================================\n";
                        cout << "                ENTRY ADDED SUCCESSFULLY!                    \n";
                        cout << "==============================================================\n";
                        break;
                    }
                    case 2:
                        tracker.loadFromFile(name, password);
                        tracker.displayResults();
                        break;
                    case 3:
                        cout << "\n==============================================================\n";
                        cout << "             RETURNING TO MAIN MENU... DATA SAVED            \n";
                        cout << "==============================================================\n";
                        break;
                    default:
                        cout << "\n+-------------------------------------------------------------+\n";
                        cout << "|              INVALID CHOICE. PLEASE TRY AGAIN.              |\n";
                        cout << "+-------------------------------------------------------------+\n";
                }
            } while (choice != 3);
        }
        else if(o == "2") {
            InsulinDosageTracker tracker;
            string insulinType, timeOfDay, date;
            double dosage;
            int choice;

            string name = person->getName();
            string password = person->getPassword();
            tracker.loadFromFile(name, password);

            do {
                cout << "\n==============================================================\n";
                cout << "                  INSULIN DOSAGE TRACKER MENU                 \n";
                cout << "--------------------------------------------------------------\n";
                cout << "1. Add Insulin Dosage Entry                                   \n";
                cout << "2. View Dosage Report                                        \n";
                cout << "3. Get Dosage Recommendation                                 \n";
                cout << "4. Return to Main Menu                                       \n";
                cout << "--------------------------------------------------------------\n";
                cout << "Enter your choice (1-4): ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "\n+-------------------------------------------------------------+\n";
                        cout << "|                    ADD INSULIN DOSAGE ENTRY                  |\n";
                        cout << "+-------------------------------------------------------------+\n";
                        cout << "| Enter date (YYYY-MM-DD): ";
                        cin >> date;
                        cout << "| Enter Insulin Type (e.g., Rapid, Long-acting): ";
                        cin >> insulinType;
                        cout << "| Enter Time of Day (e.g., Morning, Afternoon, Night): ";
                        cin >> timeOfDay;
                        cout << "| Enter Dosage (in units): ";
                        cin >> dosage;
                        cout << "+-------------------------------------------------------------+\n";
                        
                        tracker.addInsulinEntry(date, insulinType, dosage, timeOfDay);
                        tracker.saveToFile(name, password);
                        cout << "\n==============================================================\n";
                        cout << "                ENTRY ADDED SUCCESSFULLY!                    \n";
                        cout << "==============================================================\n";
                        break;
                    case 2:
                        tracker.loadFromFile(name, password);
                        tracker.displayInsulinResults();
                        break;
                    case 3: {
                        double bloodSugarLevel;
                        cout << "\n+-------------------------------------------------------------+\n";
                        cout << "|                  INSULIN DOSAGE RECOMMENDATION             |\n";
                        cout << "+-------------------------------------------------------------+\n";
                        cout << "| Enter Current Blood Sugar Level (mg/dL): ";
                        cin >> bloodSugarLevel;
                        cout << "+-------------------------------------------------------------+\n";
                        cout << "| Recommended Insulin Dosage: " << tracker.recommendDosage(bloodSugarLevel) << " units" << setw(25) << "|\n";
                        cout << "+-------------------------------------------------------------+\n";
                        break;
                    }
                    case 4:
                        cout << "\n==============================================================\n";
                        cout << "             RETURNING TO MAIN MENU... DATA SAVED            \n";
                        cout << "==============================================================\n";
                        break;
                    default:
                        cout << "\n+-------------------------------------------------------------+\n";
                        cout << "|              INVALID CHOICE. PLEASE TRY AGAIN.              |\n";
                        cout << "+-------------------------------------------------------------+\n";
                }
            } while (choice != 4);
        }
        else if (o == "3") {
            string name = person->getName();
            string password = person->getPassword();
            persons user(name, password);
            
            cout << "\n==============================================================\n";
            cout << "                   PERSONALIZED MEAL PLANNER                  \n";
            cout << "==============================================================\n";
            
            MealPlanner planner(&user);
            planner.getUserData();
            planner.calculateBMI();
            planner.suggestMealPlan();
        }
        else if (o == "4") {
            string name = person->getName();
            string password = person->getPassword();
            persons user(name, password);
            
            cout << "\n==============================================================\n";
            cout << "                   DIABETES RISK ASSESSMENT                   \n";
            cout << "==============================================================\n";
            
            DiabetesRiskEvaluator test(&user);
            test.conductTest();
            test.displayResults();
        }
        else if (o == "5") {
            string name = person->getName();
            string password = person->getPassword();
            persons user(name, password);
            HealthTracker tracker(&user);
            int choice;

            do {
                cout << "\n==============================================================\n";
                cout << "                    WATER & SLEEP TRACKER                     \n";
                cout << "--------------------------------------------------------------\n";
                cout << "1. Add New Record                                            \n";
                cout << "2. View All Records                                          \n";
                cout << "3. View Record by Date                                       \n";
                cout << "4. Return to Main Menu                                       \n";
                cout << "--------------------------------------------------------------\n";
                cout << "Enter your choice (1-4): ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        tracker.addRecord();
                        break;
                    case 2:
                        tracker.viewRecords();
                        break;
                    case 3:
                        tracker.viewRecordByDate();
                        break;
                    case 4:
                        cout << "\n==============================================================\n";
                        cout << "             RETURNING TO MAIN MENU...                        \n";
                        cout << "==============================================================\n";
                        break;
                    default:
                        cout << "\n+-------------------------------------------------------------+\n";
                        cout << "|              INVALID CHOICE. PLEASE TRY AGAIN.              |\n";
                        cout << "+-------------------------------------------------------------+\n";
                }
            } while (choice != 4);
        }
        else if (o == "6") {
            cout << "\n==============================================================\n";
            cout << "              THANK YOU FOR USING DiaWell!                    \n";
            cout << "                     GOODBYE!                                 \n";
            cout << "==============================================================\n";
            return false;
        }
        else {
            cout << "\n+-------------------------------------------------------------+\n";
            cout << "|              INVALID OPTION. PLEASE TRY AGAIN.              |\n";
            cout << "+-------------------------------------------------------------+\n";
        }
    }
    return true;
}
