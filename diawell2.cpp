#include <iostream>
#include <fstream>

using namespace std;

// Class to calculate BMI and suggest meal plan
class MealPlanner {
private:
    float weight, height, bmi;
    string sugarLevel; // Low, Normal, or High blood sugar level

public:
    // Function to take user input
    void getUserData() {
        cout << "Enter your weight (kg): ";
        cin >> weight;
        cout << "Enter your height (m): ";
        cin >> height;
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
        ofstream file("MealPlan.txt");
        if (file.is_open()) {
            file << "BMI-Based & Blood Sugar Level Meal Plan\n";
            file << "---------------------------------------\n";
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
            cout << "\n Meal plan saved to 'MealPlan.txt'.\n";
        } else {
            cout << " Error saving meal plan!\n";
        }
    }
};

// Main function
int main() {
    MealPlanner planner;
    planner.getUserData();  // Get user input
    planner.calculateBMI(); // Calculate BMI
    planner.suggestMealPlan(); // Generate meal plan

    return 0;
}
