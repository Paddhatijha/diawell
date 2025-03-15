#include <iostream>
#include <fstream>

using namespace std;

// Base Class: Handles Questionnaire
class Questionnaire {
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

// Derived Class: Evaluates risk based on score
class DiabetesRiskEvaluator : public Questionnaire {
public:
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
        ofstream file("DiabetesReport.txt");
        if (file.is_open()) {
            file << "Diabetes Risk Assessment Report\n";
            file << "------------------------------\n";
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
            cout << " Results saved to 'DiabetesReport.txt'.\n";
        } else {
            cout << " Error saving results!\n";
        }
    }
};

// Main function
int main() {
	cout<<"are you likely diabetic or at risk.find out through these test"<<endl;
    DiabetesRiskEvaluator test;
    test.conductTest();  // Conduct the questionnaire
    test.displayResults(); // Evaluate and show results

    return 0;
}