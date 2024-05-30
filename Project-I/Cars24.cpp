#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Vehicle {
public:
    virtual void showInventory() const = 0;
};

class Car : public Vehicle {
public:
    Car() {
        inventory["MINI"] = 5;
        inventory["SUV"] = 4;
        inventory["PRIME"] = 8;
    }

    void showInventory() const override {
        cout << "Available Cars:" << endl;
        for (const auto& item : inventory) {
            cout << item.first << ": " << item.second << endl;
        }
    }

    bool isAvailable(const string& type) const {
        auto it = inventory.find(type);
        return it != inventory.end() && it->second > 0;
    }

    void rentCar(const string& type) {
        inventory[type]--;
    }

    void returnCar(const string& type) {
        inventory[type]++;
    }

private:
    map<string, int> inventory;
};

class RentalDetails {
public:
    RentalDetails(const string& name, const string& contact, const string& email, int timespan, const string& cartype)
        : name(name), contact(contact), email(email), time(timespan), type(cartype), amount(0) {}

    void setDetails(const string& name, const string& contact, const string& email, int timespan, const string& cartype) {
        this->name = name;
        this->contact = contact;
        this->email = email;
        this->time = timespan;
        this->type = cartype;
        this->amount = 0;
    }

    void calculateAmount() {
        if (time >= 12) {
            if (type == "MINI") {
                amount = 5000 * time;
            } else if (type == "SUV") {
                amount = 8000 * time;
            } else if (type == "PRIME") {
                amount = 10000 * time;
            }
        } else {
            cout << "Sorry!! We don't rent cars below 12 hrs" << endl;
            amount = 0;
        }
    }

    void printBill() const {
        if (amount > 0) {
            cout << "\n        Welcome to CDAC Cars-24 Service" << endl;
            cout << "" << endl;
            cout << "Renters Name: " << name << endl;
            cout << "Renters Contact: " << contact << endl;
            cout << "Renters Email ID: " << email << endl;
            cout << "Renters timespan: " << time << endl;
            cout << "Renters Cartype: " << type << endl;
            cout << "Total Amount: " << amount << endl;
        }
    }

    void printDetails() const {
        cout << "\n        Rental Details" << endl;
        cout << "" << endl;
        cout << "Renters Name: " << name << endl;
        cout << "Renters Contact: " << contact << endl;
        cout << "Renters Email ID: " << email << endl;
        cout << "Renters timespan: " << time << endl;
        cout << "Renters Cartype: " << type << endl;
    }

    const string& getType() const {
        return type;
    }

private:
    string name;
    string contact;
    string email;
    int time;
    int amount;
    string type;
};

void displayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Show Inventory" << endl;
    cout << "2. Rent a Car" << endl;
    cout << "3. Modify Rental Details" << endl;
    cout << "4. Recalculate Amount" << endl;
    cout << "5. Print Rental Details" << endl;
    cout << "6. Delete Rental Entry" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

void deleteRental(vector<RentalDetails*>& rentals, Car& carRental) {
    if (rentals.empty()) {
        cout << "No rentals to delete!" << endl;
        return;
    }

    cout << "Enter the index of the rental to delete: ";
    int index;
    cin >> index;
    cin.ignore();

    if (index < 0 || index >= rentals.size()) {
        cout << "Invalid index!" << endl;
        return;
    }

    carRental.returnCar(rentals[index]->getType());
    delete rentals[index];
    rentals.erase(rentals.begin() + index);
    cout << "Rental entry deleted successfully!" << endl;
}

int main() {
    Car carRental;
    vector<RentalDetails*> rentals;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            carRental.showInventory();
        } else if (choice == 2) {
            string name, contact, email, cartype;
            int timespan;

            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter your contact number: ";
            getline(cin, contact);
            cout << "Enter your Email ID: ";
            getline(cin, email);
            cout << "Enter number of hours you want to rent the car: ";
            cin >> timespan;
            cin.ignore();

            if (timespan < 12) {
                cout << "Sorry!! We don't rent cars below 12 hrs" << endl;
                continue;
            }

            cout << "Enter type of car you want to rent (MINI, SUV, PRIME): ";
            getline(cin, cartype);

            if (carRental.isAvailable(cartype)) {
                auto rental = new RentalDetails(name, contact, email, timespan, cartype);
                rentals.push_back(rental);
                carRental.rentCar(cartype);
                rental->calculateAmount();
                rental->printBill();
            } else {
                cout << "Sorry, " << cartype << " is not available." << endl;
            }
        } else if (choice == 3) {
            string name, contact, email, cartype;
            int timespan;

            if (rentals.empty()) {
                cout << "No rentals to modify!" << endl;
                continue;
            }

            cout << "Enter your new name: ";
            getline(cin, name);
            cout << "Enter your new contact number: ";
            getline(cin, contact);
            cout << "Enter your new Email ID: ";
            getline(cin, email);
            cout << "Enter new number of hours you want to rent the car: ";
            cin >> timespan;
            cin.ignore();

            if (timespan < 12) {
                cout << "Sorry!! We don't rent cars below 12 hrs" << endl;
                continue;
            }

            cout << "Enter new type of car you want to rent (MINI, SUV, PRIME): ";
            getline(cin, cartype);

            auto rental = rentals.back();
            carRental.returnCar(rental->getType());
            rental->setDetails(name, contact, email, timespan, cartype);
            carRental.rentCar(cartype);
            cout << "Details updated successfully!" << endl;
        } else if (choice == 4) {
            if (rentals.empty()) {
                cout << "No rentals to recalculate!" << endl;
                continue;
            }
            auto rental = rentals.back();
            rental->calculateAmount();
            rental->printBill();
        } else if (choice == 5) {
            if (rentals.empty()) {
                cout << "No rentals to show details!" << endl;
                continue;
            }
            auto rental = rentals.back();
            rental->printDetails();
        } else if (choice == 6) {
            deleteRental(rentals, carRental);
        } else if (choice == 7) {
            cout << "Exiting the program. Thank you!" << endl;
            for (auto rental : rentals) {
                delete rental;
            }
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
