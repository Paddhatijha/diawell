#include <fstream>
#include <iomanip>
#include <cctype>
#include <sstream>
#include <limits>
#include <conio.h>
#include <iostream>
using namespace std;
#include <string>

// Terminal display constants and helpers
const int termWidth = 150;   // Terminal width (you can adjust this)
const int boxWidth = 70;    // Width of password box

// Helper to print centered line inside the box
// Helper to print centered line inside the box
void printCenteredLine(char left, const string& text, char right) {
    int padding = (boxWidth - text.length() - 2) / 2; // -2 accounts for the border characters
    cout << setw((termWidth - boxWidth) / 2) << "" << left 
         << setw(padding) << "" << text 
         << setw(boxWidth - text.length() - padding - 2) << "" << right << endl;
}

// Helper to print full border line
void printBorder(char left, char fill, char right) {
    cout << setw((termWidth - boxWidth) / 2) << "" << left;
    for (int i = 0; i < boxWidth - 2; ++i) cout << fill; // -2 accounts for border chars
    cout << right << endl;
}
// Function to center-align text within a given width
string centerText(const string& text, int width = boxWidth) {
    if (text.length() >= width) return text;
    int padding = (width - text.length()) / 2;
    return string(padding, ' ') + text;
}

// Function to print horizontal border
void printBorder(int width = boxWidth, char borderChar = '=') {
    cout << setw((termWidth - width) / 2) << "" << string(width, borderChar) << endl;
}

// Function to print section header
void printHeader(const string& title, int width = boxWidth) {
    printBorder(width, '=');
    cout << setw((termWidth - width) / 2) << "" << centerText(title, width) << endl;
    printBorder(width, '=');
    cout << endl;
}

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

    void setName(string n) { name = n; }
    string getName() const { return name; }
    void setPassword(string p) { password = p; }
    string getPassword() { return password; }
    void setHeight(int h) { height = h; }
    int getHeight() { return height; }
    void setWeight(int w) { weight = w; }
    int getWeight() { return weight; }
    void setAge(int a) { age = a; }
    int getAge() { return age; }
};

class manager : public persons {
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
            entries[entryCount++] = { date, timeOfDay, bloodSugarLevel };
        }
        else {
            cout << centerText("Error: Maximum entries reached.") << endl;
        }
    }

    void displayResults() const {
        if (entryCount == 0) {
            printHeader("NO BLOOD SUGAR RECORDS AVAILABLE");
            return;
        }

        double total = 0;
        double highest = entries[0].bloodSugarLevel;
        double lowest = entries[0].bloodSugarLevel;

        printHeader("BLOOD SUGAR TRACKING REPORT");
        cout << setw((termWidth - boxWidth) / 2) << "" << left << setw(12) << "Date" << setw(15) << "Time of Day"
            << right << setw(15) << "Sugar Level" << endl;
        printBorder('|', '-', '|');

        for (int i = 0; i < entryCount; i++) {
            cout << setw((termWidth - boxWidth) / 2) << "" << left << setw(12) << entries[i].date
                << setw(15) << entries[i].timeOfDay
                << right << setw(15) << entries[i].bloodSugarLevel << " mg/dL" << endl;
            total += entries[i].bloodSugarLevel;
            if (entries[i].bloodSugarLevel > highest) highest = entries[i].bloodSugarLevel;
            if (entries[i].bloodSugarLevel < lowest) lowest = entries[i].bloodSugarLevel;
        }

        double average = total / entryCount;

        printBorder('|', '-', '|');
        cout << centerText("Average Level: " + to_string(average) + " mg/dL") << endl;
        cout << centerText("Highest Level: " + to_string(highest) + " mg/dL") << endl;
        cout << centerText("Lowest Level: " + to_string(lowest) + " mg/dL") << endl;
    }

    void saveToFile(const string& username, const string& password) const {
        string filename = username + "_" + password + "_blood_sugar.txt";
        ofstream fout(filename, ios::trunc);
        if (!fout.is_open()) {
            cout << centerText("Error: Could not open file for saving blood sugar data.") << endl;
            return;
        }

        fout << "Username: " << username << endl;
        fout << "Password: " << password << endl;
        fout << "-------------------------------------" << endl;

        for (int i = 0; i < entryCount; i++) {
            fout << entries[i].date << " "
                << entries[i].timeOfDay << " "
                << entries[i].bloodSugarLevel << endl;
        }

        fout.close();
        //cout << centerText("Data saved to file: " + filename) << endl;
    }

    void loadFromFile(const string& username, const string& password) {
        string filename = username + "_" + password + "_blood_sugar.txt";
        ifstream fin(filename);
        if (!fin.is_open()) {
            cout << centerText("No existing blood sugar data found.") << endl;
            return;
        }

        string line;
        getline(fin, line);
        getline(fin, line);
        getline(fin, line);

        entryCount = 0;
        string date, timeOfDay;
        double bloodSugarLevel;

        while (fin >> date >> timeOfDay >> bloodSugarLevel && entryCount < MAX_ENTRIES) {
            entries[entryCount++] = { date, timeOfDay, bloodSugarLevel };
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

    void addInsulinEntry(const string& date, const string& insulinType, double dosage, const string& timeOfDay) {
        if (insulinEntryCount < MAX_INSULIN_ENTRIES) {
            insulinEntries[insulinEntryCount++] = { date, insulinType, dosage, timeOfDay };
        }
        else {
            cout << centerText("Error: Maximum entries reached.") << endl;
        }
    }

    void displayInsulinResults() const {
        if (insulinEntryCount == 0) {
            printHeader("NO INSULIN DOSAGE RECORDS AVAILABLE");
            return;
        }

        double totalDosage = 0;

        printHeader("INSULIN DOSAGE MONITORING REPORT");
        cout << setw((termWidth - boxWidth) / 2) << "" << left << setw(12) << "Date" << setw(15) << "Insulin Type"
            << setw(10) << "Time of Day" << right << setw(15) << "Dosage" << endl;
        printBorder('|', '-', '|');

        for (int i = 0; i < insulinEntryCount; i++) {
            cout << setw((termWidth - boxWidth) / 2) << "" << left << setw(12) << insulinEntries[i].date << setw(15) << insulinEntries[i].insulinType
                << setw(10) << insulinEntries[i].timeOfDay << right << setw(15) << insulinEntries[i].dosage << endl;
            totalDosage += insulinEntries[i].dosage;
        }

        printBorder('|', '-', '|');
        cout << centerText("Total Dosage: " + to_string(totalDosage) + " units") << endl;
    }

    void saveToFile(const string& username, const string& password) const {
        string filename = username + "_" + password + "_insulin.txt";
        ofstream fout(filename, ios::trunc);
        if (!fout.is_open()) {
            cout << centerText("Error: Could not open file for saving insulin data.") << endl;
            return;
        }

        fout << "Username: " << username << endl;
        fout << "Password: " << password << endl;
        fout << "-------------------------------------" << endl;

        for (int i = 0; i < insulinEntryCount; i++) {
            fout << insulinEntries[i].date << " "
                << insulinEntries[i].insulinType << " "
                << insulinEntries[i].dosage << " "
                << insulinEntries[i].timeOfDay << endl;
        }

        fout.close();
        //cout << centerText("Data saved to file: " + filename) << endl;
    }

    void loadFromFile(const string& username, const string& password) {
        string filename = username + "_" + password + "_insulin.txt";
        ifstream fin(filename);
        if (!fin.is_open()) {
            cout << centerText("No existing insulin data found.") << endl;
            return;
        }

        string line;
        getline(fin, line);
        getline(fin, line);
        getline(fin, line);

        insulinEntryCount = 0;
        string date, insulinType, timeOfDay;
        double dosage;

        while (fin >> date >> insulinType >> dosage >> timeOfDay && insulinEntryCount < MAX_INSULIN_ENTRIES) {
            insulinEntries[insulinEntryCount++] = { date, insulinType, dosage, timeOfDay };
        }

        fin.close();
    }

    double recommendDosage(double bloodSugarLevel) const {
        if (bloodSugarLevel < 70) {
            cout << centerText("Hypoglycemia, no insulin needed") << endl;
            return 0;
        }
        else if (bloodSugarLevel >= 70 && bloodSugarLevel <= 130) {
            cout << centerText("Normal range, small dose") << endl;
            return 2;
        }
        else if (bloodSugarLevel > 130 && bloodSugarLevel <= 180) {
            cout << centerText("Moderate dose") << endl;
            return 4;
        }
        else {
            cout << centerText("High dose") << endl;
            return 6;
        }
    }
};

class Questionnaire : public persons {
protected:
    int score;

public:
    Questionnaire() { score = 0; }

    int askQuestion(string question, int low, int moderate, int high) {
        int choice;
        printCenteredLine('|', question, '|');
        printCenteredLine('|', "1. Low risk", '|');
        printCenteredLine('|', "2. Moderate risk", '|');
        printCenteredLine('|', "3. High risk", '|');
        printCenteredLine('|', "Enter choice (1/2/3): ", '|');
        cin >> choice;

        if (choice == 1) return low;
        else if (choice == 2) return moderate;
        else return high;
    }

    void conductTest() {
        printHeader("DIABETES RISK ASSESSMENT");

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
    }

    int getScore() { return score; }
};

class DiabetesRiskEvaluator : public Questionnaire {
private:
    persons* user;

public:
    DiabetesRiskEvaluator(persons* u) : user(u) {}

    void displayResults() {
        printHeader("DIABETES RISK EVALUATION");
        if (score <= 8) {
            cout << centerText("Low Risk: No immediate concern. Maintain a healthy lifestyle.") << endl;
        }
        else if (score <= 18) {
            cout << centerText("Moderate Risk: Consider a health check-up and improve diet & exercise.") << endl;
        }
        else if (score <= 30) {
            cout << centerText("High Risk: Schedule a doctor's appointment soon and get tested.") << endl;
        }
        else {
            cout << centerText("Critical Risk: Seek **immediate** medical consultation!") << endl;
        }

        saveResults();
    }

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
                file << "Low Risk: No immediate concern.\n";
            }
            else if (score <= 18) {
                file << "Moderate Risk: Consider a health check-up.\n";
            }
            else if (score <= 30) {
                file << "High Risk: Schedule a doctor's appointment.\n";
            }
            else {
                file << "Critical Risk: Immediate medical consultation required!\n";
            }

            file.close();
            cout << centerText("Results saved to '" + filename + "'.") << endl;
        }
        else {
            cout << centerText("Error saving results!") << endl;
        }
    }
};

class MealPlanner : public persons {
private:
    float weight, height, bmi;
    string sugarLevel, date;
    persons* user;

public:
    MealPlanner(persons* u) : user(u) {}

    void getUserData() {
        weight = user->getWeight();
        height = user->getHeight();
        printCenteredLine('|', "Enter date (YYYY-MM-DD): ", '|');
        cin >> date;
        printCenteredLine('|', "Enter your blood sugar level (Low/Normal/High): ", '|');
        cin >> sugarLevel;
    }

    void calculateBMI() {
        bmi = weight / (height * height);
        cout << centerText("Your BMI is: " + to_string(bmi)) << endl;
    }

    void suggestMealPlan() {
        printHeader("PERSONALIZED MEAL PLAN");

        if (bmi < 18.5) {
            cout << centerText("Underweight: Increase calorie intake with healthy carbs and proteins.") << endl;
            cout << centerText("Breakfast Options:") << endl;
            cout << centerText("- Oatmeal with nuts & honey + Banana + Full-fat milk") << endl;
            cout << centerText("- Peanut butter toast + Apple + Almond milk") << endl;
            cout << centerText("- Scrambled eggs + Whole wheat bread + Avocado smoothie") << endl;
        }
        else if (bmi >= 18.5 && bmi <= 24.9) {
            cout << centerText("Normal Weight: Maintain a balanced diet with proteins, fiber, and healthy fats.") << endl;
            cout << centerText("Breakfast Options:") << endl;
            cout << centerText("- Whole wheat toast + Scrambled eggs + Fresh fruit") << endl;
            cout << centerText("- Greek yogurt + Granola + Berries") << endl;
            cout << centerText("- Poha with peanuts + Green tea") << endl;
        }
        else if (bmi >= 25 && bmi <= 29.9) {
            cout << centerText("Overweight: Reduce carbs and increase fiber intake.") << endl;
            cout << centerText("Breakfast Options:") << endl;
            cout << centerText("- Boiled eggs + Spinach smoothie + Almonds") << endl;
            cout << centerText("- Chia pudding + Walnuts + Black coffee") << endl;
            cout << centerText("- Sprouts salad + Herbal tea") << endl;
        }
        else {
            cout << centerText("Obese: Follow a low-carb, high-protein diet.") << endl;
            cout << centerText("Breakfast Options:") << endl;
            cout << centerText("- Chia seed pudding + Walnuts + Green tea") << endl;
            cout << centerText("- Scrambled eggs with spinach + Herbal tea") << endl;
            cout << centerText("- Keto smoothie (Almond milk + Chia seeds + Berries)") << endl;
        }

        if (sugarLevel == "High") {
            cout << centerText("**High Blood Sugar Alert!** Adjustments:") << endl;
            cout << centerText("- Avoid sugary drinks, white bread, and processed foods.") << endl;
        }
        else if (sugarLevel == "Low") {
            cout << centerText("**Low Blood Sugar Alert!** Adjustments:") << endl;
            cout << centerText("- Include slow-digesting carbs like oats and sweet potatoes.") << endl;
        }

        saveMealPlan();
    }

    void saveMealPlan() {
        string filename = user->getName() + "_" + user->getPassword() + "_MealPlan.txt";
        ofstream file(filename);
        if (file.is_open()) {
            file << "BMI-Based & Blood Sugar Level Meal Plan\n";
            file << "---------------------------------------\n";
            file << "Username: " << user->getName() << "\n";
            file << "Password: " << user->getPassword() << "\n";
            file << "Date: " << date << "\n";
            file << "BMI: " << bmi << "\n";

            file.close();
           // cout << centerText("Meal plan saved to '" + filename + "'.") << endl;
        }
        else {
            cout << centerText("Error saving meal plan!") << endl;
        }
    }
};

class HealthTracker : public persons {
private:
    string filename;

public:
    HealthTracker(persons* u) : persons(u->getName(), u->getPassword()) {
        filename = getName() + getPassword() + "_health_records.txt";
    }

    void displayRecord(string date, float sleep, float water) {
        printCenteredLine('|', "--- Record for " + date + " ---", '|');
        printCenteredLine('|', "Sleep: " + to_string(sleep) + " hours " + (sleep < 6 ? "(Too little!)" : sleep > 9 ? "(Too much!)" : ""), '|');
        printCenteredLine('|', "Water: " + to_string(water) + "L " + (water < 2 ? "(Drink more!)" : water > 5 ? "(Too much!)" : ""), '|');
    }

    void addRecord() {
        string date;
        float sleep, water;

        printCenteredLine('|', "Enter date (YYYY-MM-DD): ", '|');
        cin >> date;
        printCenteredLine('|', "Enter sleep hours: ", '|');
        cin >> sleep;
        printCenteredLine('|', "Enter water intake (liters): ", '|');
        cin >> water;

        ofstream file(filename, ios::app);
        if (file) {
            file << date << " " << sleep << " " << water << "\n";
            cout << centerText("Data saved successfully!") << endl;
        }
        else {
            cout << centerText("Error saving data.") << endl;
        }
        file.close();
    }

    void viewRecords() {
        ifstream file(filename);
        if (!file) {
            cout << centerText("No previous records found.") << endl;
            return;
        }

        string date;
        float sleep, water;

        printHeader("HEALTH RECORDS FOR " + getName());
        while (file >> date >> sleep >> water) {
            displayRecord(date, sleep, water);
        }

        file.close();
    }

    void viewRecordByDate() {
        ifstream file(filename);
        if (!file) {
            cout << centerText("No previous records found.") << endl;
            return;
        }

        string searchDate, date;
        float sleep, water;
        bool found = false;

        printCenteredLine('|', "Enter date to search (YYYY-MM-DD): ", '|');
        cin >> searchDate;

        while (file >> date >> sleep >> water) {
            if (date == searchDate) {
                displayRecord(date, sleep, water);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << centerText("No record found for " + searchDate + ".") << endl;
        }

        file.close();
    }
};

bool manager::menu() {
    printHeader("WELCOME TO DiaWell");
    printCenteredLine('|', "1. Create a new account", '|');
    printCenteredLine('|', "2. Login", '|');
    printCenteredLine('|', "3. Exit", '|');
    printBorder('|', '-', '|');
    printCenteredLine('|', "Enter your choice (1-3): ", '|');

    string o;
    cin >> o;

    if (o == "1") {
        return create();
    }
    else if (o == "2") {
        return login();
    }
    else if (o == "3") {
        return false;
    }
    else {
        cout << centerText("Invalid Option") << endl;
    }

    return true;
}

bool manager::create() {
    printHeader("CREATE NEW ACCOUNT");
    printCenteredLine('|', "WARNING: DO NOT USE SPACES IN YOUR NAME!", '|');
    printCenteredLine('|', "Or enter Q to return to menu:", '|');

    string name;
    cin >> name;

    if ((name == "q") || (name == "Q")) {
        return false;
    }

    printCenteredLine('|', "Please Enter Your Password:", '|');
    printCenteredLine('|', "WARNING: DO NOT USE SPACES IN YOUR PASSWORD!", '|');
    printCenteredLine('|', "Or enter Q to return to menu:", '|');

    string password;
    cin >> password;

    if ((password == "q") || (password == "Q")) {
        return false;
    }

    printCenteredLine('|', "WARNING: ONLY NUMERICAL VALUES ALLOWED!", '|');

    int inches;
    printCenteredLine('|', "Please Enter Your Height In Inches (NOTE: 60 Inches is 5 Feet):", '|');
    cin >> inches;
    while (!inches) {
        printCenteredLine('|', "Invalid Input, Please Enter Your Height In Inches:", '|');
        cin.clear();
        cin.ignore();
        cin >> inches;
    }

    int weight;
    printCenteredLine('|', "Please Enter Your Weight In Pounds:", '|');
    cin >> weight;
    while (!weight) {
        printCenteredLine('|', "Invalid Input, Please Enter Your Weight In Pounds:", '|');
        cin.clear();
        cin.ignore();
        cin >> weight;
    }

    int age;
    printCenteredLine('|', "Please Enter Your Age:", '|');
    cin >> age;
    while (!age) {
        printCenteredLine('|', "Invalid Input, Please Enter Your Age:", '|');
        cin.clear();
        cin.ignore();
        cin >> age;
    }

    persons* person = new persons(name, password);
    person->setHeight(inches);
    person->setWeight(weight);
    person->setAge(age);

    if (!checkname(person)) {
        if (!checkpassword(person)) {
            cout << centerText("Congratulations, Your Account Has Been Created " + person->getName() + "!") << endl;
            cout << centerText("Press any key to continue...");
            add(person);
            _getch();
        }
        else {
            cout << centerText("Sorry But The Password Is Already In Use!") << endl;
            cout << centerText("Press any key to continue...");
            _getch();
        }
        return false;
    }
    else {
        cout << centerText("Sorry But there Is Already A User Under This Name") << endl;
        cout << centerText("Press any key to continue...");
        _getch();
        return false;
    }
}

bool manager::play(persons* person) {
    printHeader("SUCCESSFULLY LOGGED IN AS " + person->getName());
    return true;
}

bool manager::login() {
    persons* person = nullptr;

    printHeader("LOGIN");
    printCenteredLine('|', "Please Enter Your User Name:", '|');
    printCenteredLine('|', "WARNING: DO NOT USE SPACES IN YOUR NAME!", '|');
    printCenteredLine('|', "Or enter Q to return to menu:", '|');

    string name;
    cin >> name;

    if ((name == "q") || (name == "Q")) {
        return false;
    }

    printCenteredLine('|', "Please Enter Your Password:", '|');
    printCenteredLine('|', "WARNING: DO NOT USE SPACES IN YOUR PASSWORD!", '|');
    printCenteredLine('|', "Or enter Q to return to menu:", '|');

    string password;
    char ch;

    while (true) {
        ch = _getch();
        if (ch == '\r') {
            break;
        }
        else if (ch == '\b' && !password.empty()) {
            cout << "\b \b";
            password.pop_back();
        }
        else if (ch != '\b') {
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

bool manager::checkpassword(persons* person) {
    ifstream fin;
    fin.open("DATA.txt");
    string temp;
    string password = person->getPassword();

    if (!fin.is_open()) {
        cout << centerText("File Not Found!") << endl;
        return 0;
    }

    while (getline(fin, temp)) {
        istringstream ins(temp);
        string tempname;
        ins >> tempname;
        string temppassword;
        ins >> temppassword;

        if (temppassword == password) {
            return true;
        }
    }

    fin.close();
    return false;
}

void manager::save(persons* person) {
    const int MAX_RECORDS = 1000;
    string dataArray[MAX_RECORDS];
    int recordCount = 0;

    ifstream fin("DATA.txt");
    string line;

    while (getline(fin, line) && recordCount < MAX_RECORDS) {
        istringstream ins(line);
        string name, password;
        int height, weight, age;

        if (ins >> name >> password >> height >> weight >> age) {
            dataArray[recordCount++] = line;
        }
    }
    fin.close();

    ostringstream newPersonData;
    newPersonData << person->getName() << " " << person->getPassword() << " "
        << person->getHeight() << " " << person->getWeight() << " " << person->getAge();

    string newPersonString = newPersonData.str();

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

    if (!updated && recordCount < MAX_RECORDS) {
        dataArray[recordCount++] = newPersonString;
    }

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
        cout << centerText("File Not Found!") << endl;
        return nullptr;
    }

    string line;
    while (getline(fin, line) && recordCount < MAX_RECORDS) {
        istringstream ins(line);
        for (int i = 0; i < 9; i++) {
            if (!(ins >> dataArray[recordCount][i])) {
                dataArray[recordCount][i] = "";
            }
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
        cout << centerText("Incorrect User Name or Password!") << endl;
        cout << centerText("Press any key to continue...");
        _getch();
        return nullptr;
    }

    persons* user = new persons();
    user->setName(dataArray[userIndex][0]);
    user->setPassword(dataArray[userIndex][1]);

    try {
        user->setHeight(stoi(dataArray[userIndex][3]));
    }
    catch (...) {
        user->setHeight(0);
    }

    try {
        user->setWeight(stoi(dataArray[userIndex][4]));
    }
    catch (...) {
        user->setWeight(0);
    }

    try {
        user->setAge(stoi(dataArray[userIndex][5]));
    }
    catch (...) {
        user->setAge(0);
    }
    return user;
}

bool manager::checkname(persons* person) {
    ifstream fin;
    fin.open("DATA.txt");
    string temp;
    string name = person->getName();

    if (!fin.is_open()) {
        cout << centerText("File Not Found!") << endl;
        return 0;
    }

    while (getline(fin, temp)) {
        istringstream ins(temp);
        string tempname;
        ins >> tempname;

        if (tempname == name) {
            return true;
        }
    }

    fin.close();
    return false;
}

void manager::add(persons* person) {
    ofstream fout;
    string info = person->getName() + " " + person->getPassword() + " " +
        to_string(person->getHeight()) + " " + to_string(person->getWeight()) + " " +
        to_string(person->getAge());
    fout.open("DATA.txt", ios_base::app);

    if (!fout.is_open()) {
        cout << centerText("File Not Found!") << endl;
    }

    fout << info << endl;
    fout.close();
}

bool manager::options(persons* person) {
    string o;
    while (1) {
        printHeader("MAIN MENU - " + person->getName());
        printCenteredLine('|', "1. Personalized Blood Sugar Report", '|');
        printCenteredLine('|', "2. Personalized Insulin Dosage Report", '|');
        printCenteredLine('|', "3. Personalized Meal Plan", '|');
        printCenteredLine('|', "4. Diabetic Risk Assessment Test", '|');
        printCenteredLine('|', "5. Water and Sleep Tracker", '|');
        printCenteredLine('|', "6. Exit Program", '|');
        printBorder('|', '-', '|');
        printCenteredLine('|', "Enter your choice (1-6): ", '|');
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
                printHeader("BLOOD SUGAR TRACKER");
                printCenteredLine('|', "1. Add a new blood sugar entry", '|');
                printCenteredLine('|', "2. View all entries and statistics", '|');
                printCenteredLine('|', "3. Return to Main Menu", '|');
                printBorder('|', '-', '|');
                printCenteredLine('|', "Enter your choice (1-3): ", '|');
                cin >> choice;

                switch (choice) {
                case 1: {
                    string date;
                    printHeader("ADD BLOOD SUGAR ENTRY");
                    printCenteredLine('|', "Enter date (YYYY-MM-DD): ", '|');
                    cin >> date;
                    printCenteredLine('|', "Enter time of day (Morning/Afternoon/Evening/Fasting): ", '|');
                    cin >> timeOfDay;
                    printCenteredLine('|', "Enter blood sugar level (mg/dL): ", '|');
                    cin >> sugarLevel;

                    tracker.addEntry(date, timeOfDay, sugarLevel);
                    tracker.saveToFile(name, password);
                    printHeader("ENTRY ADDED SUCCESSFULLY!");
                    break;
                }
                case 2:
                    tracker.loadFromFile(name, password);
                    tracker.displayResults();
                    break;
                case 3:
                    printHeader("RETURNING TO MAIN MENU... DATA SAVED");
                    break;
                default:
                    cout << centerText("INVALID CHOICE. PLEASE TRY AGAIN.") << endl;
                }
            } while (choice != 3);
        }
        else if (o == "2") {
            InsulinDosageTracker tracker;
            string insulinType, timeOfDay, date;
            double dosage;
            int choice;

            string name = person->getName();
            string password = person->getPassword();
            tracker.loadFromFile(name, password);

            do {
                printHeader("INSULIN DOSAGE TRACKER");
                printCenteredLine('|', "1. Add Insulin Dosage Entry", '|');
                printCenteredLine('|', "2. View Dosage Report", '|');
                printCenteredLine('|', "3. Get Dosage Recommendation", '|');
                printCenteredLine('|', "4. Return to Main Menu", '|');
                printBorder('|', '-', '|');
                printCenteredLine('|', "Enter your choice (1-4): ", '|');
                cin >> choice;

                switch (choice) {
                case 1:
                    printHeader("ADD INSULIN DOSAGE ENTRY");
                    printCenteredLine('|', "Enter date (YYYY-MM-DD): ", '|');
                    cin >> date;
                    printCenteredLine('|', "Enter Insulin Type (e.g., Rapid, Long-acting): ", '|');
                    cin >> insulinType;
                    printCenteredLine('|', "Enter Time of Day (e.g., Morning, Afternoon, Night): ", '|');
                    cin >> timeOfDay;
                    printCenteredLine('|', "Enter Dosage (in units): ", '|');
                    cin >> dosage;

                    tracker.addInsulinEntry(date, insulinType, dosage, timeOfDay);
                    tracker.saveToFile(name, password);
                    printHeader("ENTRY ADDED SUCCESSFULLY!");
                    break;
                case 2:
                    tracker.loadFromFile(name, password);
                    tracker.displayInsulinResults();
                    break;
                case 3: {
                    double bloodSugarLevel;
                    printHeader("INSULIN DOSAGE RECOMMENDATION");
                    printCenteredLine('|', "Enter Current Blood Sugar Level (mg/dL): ", '|');
                    cin >> bloodSugarLevel;
                    cout << centerText("Recommended Insulin Dosage: " + to_string(tracker.recommendDosage(bloodSugarLevel)) + " units") << endl;
                    break;
                }
                case 4:
                    printHeader("RETURNING TO MAIN MENU... DATA SAVED");
                    break;
                default:
                    cout << centerText("INVALID CHOICE. PLEASE TRY AGAIN.") << endl;
                }
            } while (choice != 4);
        }
        else if (o == "3") {
            string name = person->getName();
            string password = person->getPassword();
            persons user(name, password);

            printHeader("PERSONALIZED MEAL PLANNER");

            MealPlanner planner(&user);
            planner.getUserData();
            planner.calculateBMI();
            planner.suggestMealPlan();
        }
        else if (o == "4") {
            string name = person->getName();
            string password = person->getPassword();
            persons user(name, password);

            printHeader("DIABETES RISK ASSESSMENT");

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
                printHeader("WATER & SLEEP TRACKER");
                printCenteredLine('|', "1. Add New Record", '|');
                printCenteredLine('|', "2. View All Records", '|');
                printCenteredLine('|', "3. View Record by Date", '|');
                printCenteredLine('|', "4. Return to Main Menu", '|');
                printBorder('|', '-', '|');
                printCenteredLine('|', "Enter your choice (1-4): ", '|');
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
                    printHeader("RETURNING TO MAIN MENU...");
                    break;
                default:
                    cout << centerText("INVALID CHOICE. PLEASE TRY AGAIN.") << endl;
                }
            } while (choice != 4);
        }
        else if (o == "6") {
            printHeader("THANK YOU FOR USING DiaWell!");
            cout << centerText("GOODBYE!") << endl;
            printBorder('|', '=', '|');
            return false;
        }
        else {
            cout << centerText("INVALID OPTION. PLEASE TRY AGAIN.") << endl;
        }
    }
    return true;
}
