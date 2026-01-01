#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string FILE_PATH = R"(C:\Users\JahanBakhsh\Desktop\users.txt)";

enum CarStatus { AVAILABLE, RENTED, MAINTENANCE };

unsigned long long hashPassword(string str) {
    unsigned long long hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

class User {
public:
    string username;
    unsigned long long passwordHash;
    string role;
    double balance_due;
    string history;
    User* next;

    User(string un, string pw, string r) {
        username = un;
        passwordHash = hashPassword(pw);
        role = r;
        balance_due = 0.0;
        history = "No_History";
        next = nullptr;
    }
};



class Car {
public:
    string model;
    double pricePerDay;
    CarStatus status;
    Car* next;
    Car* prev;

    Car(string m, double p) {
        model = m;
        pricePerDay = p;
        status = AVAILABLE;
        next = prev = nullptr;
    }
};

class UserManager {
private:
    static const int HASH_TABLE_SIZE = 100;
    User* hashTable[HASH_TABLE_SIZE];
    User* head;

    int getHash(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % HASH_TABLE_SIZE;
    }

public:
    UserManager() {
        head = nullptr;
        for (int i = 0; i < HASH_TABLE_SIZE; i++) hashTable[i] = nullptr;
        loadFromFile();
    }

    void showDefaulters() {
        User* temp = head;
        cout << "--- Users with Outstanding Debt ---\n";
        while (temp) {
            if (temp->balance_due > 0) {
                cout << "User: " << temp->username << " | Debt: " << temp->balance_due << endl;
            }
            temp = temp->next;
        }
    }

    void saveToFile() {
        ofstream outFile(FILE_PATH);
        if (!outFile) return;
        User* temp = head;
        while (temp != nullptr) {

            outFile << temp->username << " "
                    << temp->passwordHash << " "
                    << temp->role << " "
                    << temp->balance_due << " "
                    << temp->history << endl;
            temp = temp->next;
        }
        outFile.close();
    }

    void loadFromFile() {
        ifstream inFile(FILE_PATH);
        if (!inFile) return;
        string un, r, hist;
        unsigned long long ph;
        double bal;
        while (inFile >> un >> ph >> r >> bal >> hist) {
            User* newUser = new User(un, "", r);
            newUser->passwordHash = ph;
            newUser->balance_due = bal;
            newUser->history = hist;

            newUser->next = head;
            head = newUser;
            hashTable[getHash(un)] = newUser;
        }
        inFile.close();
    }

    bool signUp(string username, string password, string role) {
        if (findUser(username) != nullptr) {
            cout << "Error: Username exists!" << endl;
            return false;
        }
        User* newUser = new User(username, password, role);
        newUser->next = head;
        head = newUser;
        hashTable[getHash(username)] = newUser;
        saveToFile();
        return true;
    }

    User* findUser(string username) {
        User* temp = head;
        while (temp != nullptr) {
            if (temp->username == username) return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    User* login(string username, string password) {
        User* user = findUser(username);
        if (user != nullptr && user->passwordHash == hashPassword(password)) {
            return user;
        }
        return nullptr;
    }
};

const string CAR_FILE_PATH = R"(C:\Users\JahanBakhsh\Desktop\cars.txt)";

class FleetManager {
public:
    Car* head;
    Car* tail;
    double totalRevenue;

    FleetManager() {
        head = tail = nullptr;
        totalRevenue = 0.0;
        loadCars();
    }

    void addCar(string model, double price) {
        Car* newCar = new Car(model, price);
        if (!head) {
            head = tail = newCar;
        } else {
            tail->next = newCar;
            newCar->prev = tail;
            tail = newCar;
        }
        saveCars();
    }

    void setMaintenance(string model) {
        Car* temp = head;
        while (temp) {
            if (temp->model == model) {
                temp->status = MAINTENANCE;
                saveCars();
                return;
            }
            temp = temp->next;
        }
    }

    void saveCars() {
        ofstream outFile(CAR_FILE_PATH);
        Car* temp = head;
        while (temp) {
            outFile << temp->model << " " << temp->pricePerDay << " " << temp->status << endl;
            temp = temp->next;
        }
        outFile.close();
    }

    void loadCars() {
        ifstream inFile(CAR_FILE_PATH);
        if (!inFile) return;
        string m; double p; int s;
        while (inFile >> m >> p >> s) {
            Car* newCar = new Car(m, p);
            newCar->status = static_cast<CarStatus>(s);
            if (!head) head = tail = newCar;
            else { tail->next = newCar; newCar->prev = tail; tail = newCar; }
        }
    }
};

void showManagerMenu(UserManager& uManager, FleetManager& fManager) {
    int choice;
    while (true) {
        cout << "\n--- MANAGER PANEL ---\n";
        cout << "1. Add New Car \n";
        cout << "2. Set Car to Maintenance \n";
        cout << "3. View Total Revenue \n";
        cout << "4. View Bad Debtors \n";
        cout << "5. Logout\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            string m; double p;
            cout << "Model: "; cin >> m;
            cout << "Price/Day: "; cin >> p;
            fManager.addCar(m, p);
        }
        else if (choice == 3) {
            cout << "Total Revenue: " << fManager.totalRevenue << endl; 
        }
        else if (choice == 4) {
            uManager.showDefaulters();
        }
        else if (choice == 5) break;
    }
}


void showCustomerMenu(User* user, UserManager& manager) {
    int choice;
    while (true) {
        cout << "\n--- CUSTOMER PANEL (" << user->username << ") ---\n";
        cout << "1. View History \n"; // [cite: 19]
        cout << "2. Rent Car \n"; // [cite: 19]
        cout << "3. Pay Fines " << user->balance_due << ")\n";
        cout << "4. Logout\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Your History: " << user->history << endl;
        } else if (choice == 2) {
            string carName;
            cout << "Enter Car Name to rent: "; cin >> carName;
            user->history += "," + carName;
            manager.saveToFile();
            cout << "Car " << carName << " rented successfully!\n";
        } else if (choice == 3) {
            if (user->balance_due > 0) {
                user->balance_due = 0;
                manager.saveToFile();
                cout << "All fines paid.\n";
            } else cout << "No fines to pay.\n";
        } else if (choice == 4) break;
    }
}

int main() {
    UserManager system;
    FleetManager fleet;

    int choice;
    string u, p;

    while (true) {
        cout << "\n===============================";
        cout << "\n--- CAR RENTAL SYSTEM MENU ---";
        cout << "\n1. Sign Up (Customer)";
        cout << "\n2. Customer Login";
        cout << "\n3. Manager Login (Admin)";
        cout << "\n4. Exit";
        cout << "\n===============================";
        cout << "\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Username: "; cin >> u;
            cout << "Enter Password: "; cin >> p;
            system.signUp(u, p, "Customer");
        }
        else if (choice == 2) {
            cout << "Username: "; cin >> u;
            cout << "Password: "; cin >> p;
            User* loggedInUser = system.login(u, p);
            if (loggedInUser) {
                cout << "Login Successful!\n";
                showCustomerMenu(loggedInUser, system);
            } else {
                cout << "Invalid Username or Password!\n";
            }
        }
        else if (choice == 3) {
            cout << "Admin Username: "; cin >> u;
            cout << "Admin Password: "; cin >> p;

            if (u == "admin" && p == "admin123") {
                cout << "Manager Access Granted!\n";
                showManagerMenu(system, fleet);
            } else {
                cout << "Access Denied! Incorrect Admin Credentials.\n";
            }
        }
        else if (choice == 4) {
            cout << "Exiting System. Saving data...\n";
            break; 
        }
        else {
            cout << "Invalid Choice! Please try again.\n";
        }
    }
    return 0;
}