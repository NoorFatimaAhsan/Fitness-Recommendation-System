
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
bool isNumber(const string& s) {
    if (s.empty()) return false;
    size_t i = 0;
    if (s[0] == '-' || s[0] == '+') i = 1; 
    bool hasDecimal = false;
    for (; i < s.size(); ++i) {
        if (s[i] == '.') {
            if (hasDecimal) return false; 
            hasDecimal = true;
        } else if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}
//abstract class
//observer
class FitnessRecommendationObserver {
public:
    virtual void update() = 0;
    virtual ~FitnessRecommendationObserver() {}
};
//subject
class UserHealthMetrics {
private:
    string bmi_category;
    float bmi;
    float height;
    float weight;
    string activityLevel;
    vector<FitnessRecommendationObserver*> observers;

public:
    UserHealthMetrics() : activityLevel("firstlogin") {}
    ~UserHealthMetrics() {}

    void attach(FitnessRecommendationObserver* observer) {
        observers.push_back(observer);
    }
    void detach(FitnessRecommendationObserver* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notify() {
        for (auto obs : observers)
            obs->update();
    }

    float getHeight() const { return height; }
    float getWeight() const { return weight; }
    string getActivityLevel() const { return activityLevel; }
    string getBMI() const { return bmi_category; }

    bool validateAndSetHeight(float h) {
        if (h < 1.42 || h > 1.96) {
            cout << "\nSorry!! Given height falls out of our BMI chart range. Try Again\n\n";
            return false;
        } else {
            height = h;
            return true;
        }
    }
    bool validateAndSetWeight(float w) {
        if (w >= 36.3 && w <= 117.9) {
            weight = w;
            return true;
        } else {
            cout << "Sorry!! Given weight falls out of our BMI chart range. Try Again\n\n";
            return false;
        }
    }
    bool validateAndSetActivityLevel(const string& level) {
        if (level == "Beginner" || level == "Intermediate" || level == "Advanced" ||
            level == "beginner" || level == "intermediate" || level == "advanced") {
        
            if (activityLevel == level) {
                cout << "\nYou are already at this activity level!\n .Try a different level. \n";
                return false;
            }
            activityLevel = level;
            return true;
        } else {
            cout << "\nIncorrect activity level!\n Try again!! ";
            return false;
        }
    }

    void inputMetrics() {
        string input;
        float h, w;
        string level;
        while (true) {
            cout << "Enter height between (1.42-1.96)(m): ";
            cin >> input;
            if (!isNumber(input)) {
                cout << "Invalid input! Please enter a numeric value.\n";
                continue;
            }
            h = stof(input);
            if (validateAndSetHeight(h))
                break;
        }
        while (true) {
            cout << "Enter weight between (36.3-117.9)(kg): ";
            cin >> input;
            if (!isNumber(input)) {
                cout << "Invalid input! Please enter a numeric value.\n";
                continue;
            }
            w = stof(input);
            if (validateAndSetWeight(w))
                break;
        }
        while (true) {
            cout << "Enter activity level (Beginner/Intermediate/Advanced): ";
            cin >> level;
            if (validateAndSetActivityLevel(level))
                break;
        }

        cout << "\nActivity Level Updated Successfully!\n";
        notify();
    }

    void setHeight() {
        string input;
        float h;
        while (true) {
            cout << "Enter new height between (1.42-1.96)(m): ";
            cin >> input;
            if (!isNumber(input)) {
                cout << "Invalid input! Please enter a numeric value.\n";
                continue;
            }
            h = stof(input);
            if (validateAndSetHeight(h))
                break;
        }
        cout << "\nHeight Updated Successfully!\n";
        notify();
    }

    void setWeight() {
        string input;
        float w;
        while (true) {
            cout << "Enter new weight between (36.3-117.9)(kg): ";
            cin >> input;
            if (!isNumber(input)) {
                cout << "Invalid input! Please enter a numeric value.\n";
                continue;
            }
            w = stof(input);
            if (validateAndSetWeight(w))
                break;
        }
        cout << "\nWeight Updated Successfully!\n";
        notify();
    }

    void setActivityLevel() {
        string lvl;
        while (true) {
            cout << "Enter new ActivityLevel (Beginner/Intermediate/Advanced): ";
            cin >> lvl;
            if (validateAndSetActivityLevel(lvl))
                break;
        }
        notify();
    }

    float calculateBMI() {
        bmi = weight / (height * height);
        return bmi;
    }

    void updateBMI() {
        if (bmi < 18.5)
            bmi_category = "underweight";
        else if (bmi >= 18.5 && bmi < 25)
            bmi_category = "normal";
        else if (bmi >= 25 && bmi < 30)
            bmi_category = "overweight";
        else
            bmi_category = "obese";
    }
};
// strategy pattern abstract class
class FitnessRecommendationStrategy {
public:
    virtual void recommend(const UserHealthMetrics& metrics) = 0;
    virtual ~FitnessRecommendationStrategy() {}
};
//concrete class 1
class BeginnerFriendly : public FitnessRecommendationStrategy {
public:
    void recommend(const UserHealthMetrics& metrics) override {
        string bmi = metrics.getBMI();
        if (bmi == "underweight") {
            cout << "\n BMI Category: UnderWeight \n";
            cout << "\n -Light bodyweight exercises (squats, push-ups)";
            cout << "\n -Yoga/stretching for flexibility";
            cout << "\n -Walking 20-30 min daily";
            cout << "\n -Emphasis on nutrition and gradual strength training";
        } else if (bmi == "normal") {
            cout << "\n BMI Category: Normal \n";
            cout << "\n -Brisk walking 30 mins";
            cout << "\n -Light strength (resistance bands)";
            cout << "\n -Bodyweight exercises (planks, lunges)";
            cout << "\n -2x/week yoga or flexibility training";
        } else if (bmi == "overweight") {
            cout << "\n BMI Category: OverWeight \n";
            cout << "\n  -Walking 30 mins/day";
            cout << "\n  -Low-impact cardio (cycling, elliptical)";
            cout << "\n  -Chair or wall exercises";
            cout << "\n  -Gentle core exercises";
        } else if (bmi == "obese") {
            cout << "\n BMI Category: Obese \n";
            cout << "\n  -Chair exercises";
            cout << "\n  -Water aerobics or pool walking (low impact)";
            cout << "\n  -Short walks (3x10 min/day)";
            cout << "\n  -Focus on mobility & breathing exercises";
        } else
            cout << "\n No Strategies recommended";
    }
};
//concrete class 2
class Intermediate : public FitnessRecommendationStrategy {
public:
    void recommend(const UserHealthMetrics& metrics) override {
        string bmi = metrics.getBMI();
        if (bmi == "underweight") {
            cout << "\n BMI Category: UnderWeight \n";
            cout << "\n  -Full-body strength training 3x/week";
            cout << "\n  -Cardio (light jog, cycling)";
            cout << "\n  -Core stability";
        } else if (bmi == "normal") {
            cout << "\n BMI Category: Normal \n";
            cout << "\n  -Jogging or swimming 3x/week";
            cout << "\n  -Resistance training (dumbbells/machines)";
            cout << "\n  -HIIT 1x/week";
            cout << "\n  -Pilates or yoga once a week";
        } else if (bmi == "overweight") {
            cout << "\n BMI Category: OverWeight \n\n";
            cout << "\n  -Low-impact HIIT (short circuits)";
            cout << "\n  -Strength training (2x/week)";
            cout << "\n  -Walking or elliptical 45 mins";
            cout << "\n  -Posture and mobility drills";
        } else if (bmi == "obese") {
            cout << "\n BMI Category: Obese \n";
            cout << "\n  -Stationary bike or aqua aerobics";
            cout << "\n  -Circuit training with long rests";
            cout << "\n  -Core strengthening with stability ball";
            cout << "\n  -Personalized trainer sessions (optional)";
        } else
            cout << "\n No Strategies recommended";
    }
};
//concrete class 3
class Advanced : public FitnessRecommendationStrategy {
public:
    void recommend(const UserHealthMetrics& metrics) override {
        string bmi = metrics.getBMI();
        if (bmi == "underweight") {
            cout << "\n BMI Category: UnderWeight \n";
            cout << "\n -Progressive overload strength training";
            cout << "\n -Compound lifts (deadlifts, squats)";
            cout << "\n -Muscle mass focus (5-6x/week split routine)";
        } else if (bmi == "normal") {
            cout << "\n BMI Category: Normal \n";
            cout << "\n  -Intense HIIT 3x/week";
            cout << "\n  -strength training (5x/week split)";
            cout << "\n  -Cardio endurance (cycling, running)";
            cout << "\n  -Agility & speed training";
        } else if (bmi == "overweight") {
            cout << "\n BMI Category: overweight \n";
            cout << "\n  -Advanced resistance workouts";
            cout << "\n  -HIIT with low rest periods";
            cout << "\n  -Long-distance walking/jogging";
            cout << "\n  -Recovery routines (foam rolling)";
        } else if (bmi == "obese") {
            cout << "\n BMI Category: Obese \n";
            cout << "\n   -Trainer-guided progressive program";
            cout << "\n   -Interval walking on incline";
            cout << "\n   -Assisted strength training";
            cout << "\n   -Yoga for joint care & flexibility";
        } else {
            cout << "\n BMI: " << bmi;
            cout << "\n No Strategies recommended";
        }
    }
};
//concrete class 1+singleton
class FitnessRecommendationEngine : public FitnessRecommendationObserver {
private:
    static FitnessRecommendationEngine* instance;
    UserHealthMetrics& userMetrics;
    FitnessRecommendationStrategy* strategy;

    FitnessRecommendationEngine(UserHealthMetrics& m) : userMetrics(m), strategy(nullptr) {
        userMetrics.attach(this);
        update();
    }
    ~FitnessRecommendationEngine() {
    	userMetrics.detach(this);
    	delete strategy;
    	strategy=nullptr;
        
    }

public:
    static FitnessRecommendationEngine* getinstance(UserHealthMetrics& m) {
        if (!instance) instance = new FitnessRecommendationEngine(m);
        return instance;
    }
 
    static void destroyInstance() {
    	delete instance;
    	instance=nullptr;
    }
    void update() override {
        userMetrics.calculateBMI();
        userMetrics.updateBMI();
        string level = userMetrics.getActivityLevel();
        if (level == "Beginner" || level == "beginner")
            strategy = new BeginnerFriendly();
        else if (level == "Intermediate" || level == "intermediate")
            strategy = new Intermediate();
        else if (level == "Advanced" || level == "advanced")
            strategy = new Advanced();
        else
            cout << "\n Incorrect Level!\n";
    }
    void recommend() {
        if (strategy)
            strategy->recommend(userMetrics);
        else
            cout << "\n[no recommendation available. Check profile]\n" << endl;
        return;
    }
};

FitnessRecommendationEngine* FitnessRecommendationEngine::instance = nullptr;
//concrete class 2+singleton
class DietRecommendationEngine : public FitnessRecommendationObserver {
private:
    static DietRecommendationEngine* instance;
    UserHealthMetrics& userMetrics;

    DietRecommendationEngine(UserHealthMetrics& m) : userMetrics(m) {
        userMetrics.attach(this);
        update();
    }
    ~ DietRecommendationEngine()  {
       userMetrics.detach(this);
    }

public:
    static DietRecommendationEngine* getinstance(UserHealthMetrics& m) {
        if (!instance) instance = new DietRecommendationEngine(m);
        return instance;
    }
    
     static void destroyInstance() {	
    	delete instance;
    	instance=nullptr;
    }
    void update() override {
        userMetrics.calculateBMI();
        userMetrics.updateBMI();
    }
    void recommend() {
        string bmi = userMetrics.getBMI();
        if (bmi == "normal") {
            cout << "\n Goal: Maintain energy and balance.";
            cout << "\n Breakfast:\n   -Oats with fruit + black coffee";
            cout << "\n Lunch:\n   -Whole grain chapati + dal + vegetables";
            cout << "\n Snack:\n   -Apple or yogurt";
            cout << "\n Dinner:\n   -Grilled veggies + light protein (tofu or egg)\n";
        } else if (bmi == "overweight") {
            cout << "\n Goal: Gradual fat loss.";
            cout << "\n Breakfast:\n   -Scrambled eggs (2) + multigrain toast";
            cout << "\n Lunch:\n   -Quinoa + legumes + salad";
            cout << "\n Snack:\n   -Roasted chickpeas or green tea";
            cout << "\n Dinner:\n   -Vegetable soup + grilled paneer\n";
        } else if (bmi == "underweight") {
            cout << "\n Goal: Healthy weight gain.";
            cout << "\n\n Breakfast:\n   -Full fat milk + banana + peanut butter toast";
            cout << "\n Lunch:\n   -Brown rice + lentils or chicken + salted veggies";
            cout << "\n Snack:\n   -Handful of nuts or a boiled egg";
            cout << "\n Dinner:\n   -Paneer curry + chapati + salad\n";
        } else if (bmi == "obese") {
            cout << "\n Goal: Fat loss and low calorie intake.";
            cout << "\n\n Breakfast:\n   -Chia seed pudding or oats + herbal tea";
            cout << "\n Lunch:\n   -Lentil salad + cucumber + lemon dressing";
            cout << "\n Snack:\n   -Fruit slices or a handful of seeds";
            cout << "\n Dinner:\n   -Steamed vegetables + soup\n";
        } else
            cout << "\n No Recommendations suggested!" << endl;
    }
};

DietRecommendationEngine* DietRecommendationEngine::instance = nullptr;
// single user
class User {
private:
    string username;
    string password;
    UserHealthMetrics metrics;

public:
    User() {}
    User(string uname, string pwd) : username(uname), password(pwd) {}
    
    string getUsername() const { 
	return username; 
	}
    
    bool isValidUsername(const string& uname) {
	    if (uname.length() > 10){
	    	cout<<"\n username cannot be longer than 10 characters";
	        return false;}
		int c=0;
	    bool hasLetter = false; 
	
	    for (int i = 0; i < uname.length(); ++i) {
	        char ch = uname[i];
	        if (!((ch >= 'A' && ch <= 'Z') ||
	              (ch >= 'a' && ch <= 'z') ||
	              (ch >= '0' && ch <= '9')||(ch==' '))) {
	              	cout<<"\n username cannot contain special characters ";
	            return false; 
	        }
	        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
	            hasLetter = true; 
	        }
	        if(ch==' '){
				c++;
				}
	        
	    }
	    if(c>2)
		{
		   cout<<"\n username cannot contain more than 2 spaces!!"; 
		   return false;}
	
	    if (!hasLetter) {
	    	cout<<"\n username cannot be only numbers";
	        return false;
	    }
	
	    return true;
	}


	bool isValidPassword(const string& pwd) {
	    if (pwd.length() < 4 || pwd.length()>10)
		 return false;
	    for (int i = 0; i < pwd.length(); ++i) {
	        if (pwd[i] == ' ') 
			return false; 
	    }
	    return true;
	}

    bool authenticate(const string& uname, const string& pwd) {
        return username == uname && password == pwd;
    }
    void loginSuccess() {
        cout << "Login is successful!\n";
        FitnessRecommendationEngine::getinstance(metrics);
        DietRecommendationEngine::getinstance(metrics);
    }
    void inputHealthMetrics() {
        metrics.inputMetrics();
    }
    void viewMetrics() {
    	cout << "\n\n-------HEALTH METRICS & ACTIVITY LEVEL-------\n";
        cout << "\n1.Name: " << username;
        cout << "\n2.Height: " << metrics.getHeight()<< " m";
        cout << "\n3.Weight: " << metrics.getWeight()<<" kg";
        cout << "\n4.BMI: " << metrics.calculateBMI();
        cout << "\n5.BMI Category: " << metrics.getBMI();
        cout << "\n6.Activity Level: " << metrics.getActivityLevel() << endl;
        cout<<"\n------------------------------------------------\n";
        
    }
    void viewRecommendation() {
        FitnessRecommendationEngine* fit = FitnessRecommendationEngine::getinstance(metrics);
        DietRecommendationEngine* diet = DietRecommendationEngine::getinstance(metrics);
        if (fit) {
            cout << "\n\n---------EXERCISE RECOMMENDATION---------\n";
            fit->recommend();
        }
        if (diet) {
            cout << "\n\n-----------DIET RECOMMENDATION-----------\n";
            diet->recommend();
        }
         
           cout<<"\n------------------------------------------------\n";
    }
    void updateHealthMetrics() {
        char choice;
		do {
		    cout << "\n1. Update Height\n2. Update Weight\n3. Update Activity Level\n4. Back\nChoice: ";
		    cin.clear(); cin.sync();
		    string input;
		    getline(cin, input);
		
		    if (input.length() == 1) {
		        choice = input[0];
		    } else {
		        choice = '\0';
		    }
		
		    switch (choice) {
		        case '1': metrics.setHeight(); break;
		        case '2': metrics.setWeight(); break;
		        case '3': metrics.setActivityLevel(); break;
		        case '4': break;
		        default: cout << "\n Invalid Choice \n Try Again!!\n"; break;
		    }
		} while (choice != '4');

    }
    void logout() {
         FitnessRecommendationEngine::destroyInstance();
         DietRecommendationEngine::destroyInstance();
    }
    void serialize(ofstream& out) const {
        out << username << '\n' << password << '\n'
            << metrics.getHeight() << '\n' << metrics.getWeight() << '\n'
            << metrics.getActivityLevel() << '\n';
    }
    bool deserialize(ifstream& in) {
        string uname, pwd, level;
        float height, weight;
        if (!getline(in, uname)) return false;
        if (!getline(in, pwd)) return false;
        if (!(in >> height)) return false;
        if (!(in >> weight)) return false;
        in.ignore();
        if (!getline(in, level)) return false;
        username = uname;
        password = pwd;
        if (!metrics.validateAndSetHeight(height)) return false;
        if (!metrics.validateAndSetWeight(weight)) return false;
        if (!metrics.validateAndSetActivityLevel(level)) return false;
        metrics.notify();
        return true;
    }
};

void loadAllUsers(vector<User>& users) {
    ifstream inFile("fitness.txt");
    if (!inFile) return;
    while (inFile) {
        User u;
        if (u.deserialize(inFile)) {
            users.push_back(u);
        }
    }
    inFile.close();
}

void saveAllUsers(const vector<User>& users) {
    ofstream outFile("fitness.txt", ios::trunc);
    for (const auto& u : users) {
        u.serialize(outFile);
    }
    outFile.close();
}

// multiple user handing
int main() {
    vector<User> users;
    User* currentUser = nullptr;
    User tempuser;

    loadAllUsers(users);
    cout << "\t\t--------FITNESS RECOMMENDATION SYSTEM--------\n";
    char choice;
    do {
        string input;
        xy:
        cout << "\n MENU\n ";
        cout << "\n1. Register\n2. Login\n3. Exit\nChoice: ";
        cin.clear(); cin.sync();  
        getline(cin, input);

        if (input.length() == 1 && (input[0] == '1' || input[0] == '2' || input[0] == '3')) {
            choice = input[0];
        } else {
            cout << "\nInvalid choice! ";
            cout << "Try Again\n";
            goto xy;
        }

        if (choice == '1') {
            string uname, pwd;
            cout<<" \n Read this before registration :";
            cout << "\n  -username can be max 10 characters, letters and numbers allowed, only numbers not allowed ";
            cout << "\n  -password must be 4 - 10 characters with no spaces allowed \n";

            do {
                cout << "\n Enter username: ";
                getline(cin, uname);

                if (!tempuser.isValidUsername(uname)) {
                    cout << "\n Invalid username. Try Again\n";
                } else {
                    break;
                }
            } while (true);

            do {
                cout << "\n Enter password:  ";
                getline(cin, pwd);

                if (!tempuser.isValidPassword(pwd)) {
                    cout << "\n Invalid password. Try Again \n";
                } else {
                    break;
                }
            } while (true);

            bool exists = false;
            for (int i = 0; i < users.size(); ++i) {
                if (users[i].getUsername() == uname) {
                    exists = true;
                    break;
                }
            }

            if (exists) {
                cout << "User already exists.\n";
            } else {
                User newUser(uname, pwd);
                newUser.inputHealthMetrics();
                users.push_back(newUser);
                saveAllUsers(users);
                cout << "Registration successful!\n";
                system("cls");
            }

        } else if (choice == '2') {
            string uname, pwd;
            cout << "Enter username: "; getline(cin, uname);
            cout << "Enter password: "; getline(cin, pwd);

            bool found = false;
            for (int i = 0; i < users.size(); ++i) {
                if (users[i].getUsername() == uname && users[i].authenticate(uname, pwd)) {
                    currentUser = &users[i];
                    users[i].loginSuccess();
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Authentication failed.\n";
            } else {
                string optInput;
                char opt;
                do {
                    cout << "\n1. View Metrics \n2. View Recommendation\n3. Update Metrics\n4. Logout\nChoice: ";
                    cin.clear(); cin.sync();
                    getline(cin, optInput);

                    if (optInput.length() == 1 && (optInput[0] >= '1' && optInput[0] <= '4')) {
                        opt = optInput[0];
                    } else {
                        cout << "\nInvalid choice\n";
                        continue;
                    }

                    switch (opt) {
                        case '1': currentUser->viewMetrics(); break;
                        case '2': currentUser->viewRecommendation(); break;
                        case '3': currentUser->updateHealthMetrics(); break;
                        case '4':
                            currentUser->logout();
                            saveAllUsers(users);
                            currentUser = nullptr;
                            cout << "Logged out.\n";
                            system("cls");
                            break;
                       
                    }
                } while (opt != '4');
            }
        }

    } while (choice != '3');

    saveAllUsers(users); 
    return 0;
}

