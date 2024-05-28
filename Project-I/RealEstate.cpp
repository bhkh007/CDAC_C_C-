#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Property {
protected:
    int id;
    string address;
    string type;
    double price;
    double area;

public:
    Property(int id, const string &address, const string &type, double price, double area)
        : id(id), address(address), type(type), price(price), area(area) {}

    virtual ~Property() {}

    int getId() const { return id; }
    string getAddress() const { return address; }
    string getType() const { return type; }
    double getPrice() const { return price; }
    double getArea() const { return area; }

    virtual void display() const {
        cout << "ID: " << id << "\nAddress: " << address << "\nType: " << type
             << "\nPrice: $" << price << "\nArea: " << area << " sq ft\n";
    }

    virtual void save(ofstream &out) const {
        out << id << '\n' << address << '\n' << type << '\n' << price << '\n' << area << '\n';
    }

    virtual void load(ifstream &in) {
        in >> id;
        in.ignore();
        getline(in, address);
        getline(in, type);
        in >> price >> area;
    }

    void updateDetails() {
        cout << "Enter new address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter new type: ";
        getline(cin, type);
        cout << "Enter new price: ";
        cin >> price;
        cout << "Enter new area (in sq ft): ";
        cin >> area;
    }
};

class RealEstateManagement {
private:
    vector<Property*> properties;
    int nextId = 1;

public:
    ~RealEstateManagement() {
        for (Property* prop : properties)
            delete prop;
    }

    void addProperty() {
        string address, type;
        double price, area;

        cout << "Enter address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter type (e.g., Apartment, House, Land): ";
        getline(cin, type);
        cout << "Enter price: ";
        cin >> price;
        cout << "Enter area (in sq ft): ";
        cin >> area;

        properties.push_back(new Property(nextId++, address, type, price, area));
        cout << "Property added successfully.\n";
    }

    void displayProperties() const {
        if (properties.empty()) {
            cout << "No properties available.\n";
            return;
        }
        for (const auto &property : properties) {
            property->display();
            cout << "-------------------\n";
        }
    }

    void searchPropertyById() const {
        int searchId;
        cout << "Enter property ID to search: ";
        cin >> searchId;

        for (const auto &property : properties) {
            if (property->getId() == searchId) {
                property->display();
                return;
            }
        }
        cout << "Property not found.\n";
    }

    void searchPropertyByAddress() const {
        string searchAddress;
        cout << "Enter property address to search: ";
        cin.ignore();
        getline(cin, searchAddress);

        for (const auto &property : properties) {
            if (property->getAddress() == searchAddress) {
                property->display();
                return;
            }
        }
        cout << "Property not found.\n";
    }

    void updateProperty() {
        int updateId;
        cout << "Enter property ID to update: ";
        cin >> updateId;

        for (auto &property : properties) {
            if (property->getId() == updateId) {
                property->updateDetails();
                cout << "Property updated successfully.\n";
                return;
            }
        }
        cout << "Property not found.\n";
    }

    void deleteProperty() {
        int deleteId;
        cout << "Enter property ID to delete: ";
        cin >> deleteId;

        for (auto it = properties.begin(); it != properties.end(); ++it) {
            if ((*it)->getId() == deleteId) {
                delete *it;
                properties.erase(it);
                cout << "Property deleted successfully.\n";
                return;
            }
        }
        cout << "Property not found.\n";
    }

    void saveToFile() const {
        ofstream outFile("properties.txt");
        if (!outFile) {
            cout << "Error opening file for writing.\n";
            return;
        }
        outFile << properties.size() << '\n';
        for (const auto &property : properties) {
            property->save(outFile);
        }
        outFile.close();
        cout << "Properties saved to file successfully.\n";
    }

    void loadFromFile() {
        ifstream inFile("properties.txt");
        if (!inFile) {
            cout << "Error opening file for reading.\n";
            return;
        }
        int propertyCount;
        inFile >> propertyCount;
        for (int i = 0; i < propertyCount; ++i) {
            Property *property = new Property(0, "", "", 0.0, 0.0);
            property->load(inFile);
            properties.push_back(property);
            if (property->getId() >= nextId) {
                nextId = property->getId() + 1;
            }
        }
        inFile.close();
        cout << "Properties loaded from file successfully.\n";
    }
};

int main() {
    RealEstateManagement rem;
    rem.loadFromFile();
    int choice;

    do {
        cout << "\nReal Estate Management System\n";
        cout << "1. Add Property\n";
        cout << "2. Display Properties\n";
        cout << "3. Search Property by ID\n";
        cout << "4. Search Property by Address\n";
        cout << "5. Update Property\n";
        cout << "6. Delete Property\n";
        cout << "7. Save to File\n";
        cout << "8. Load from File\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                rem.addProperty();
                break;
            case 2:
                rem.displayProperties();
                break;
            case 3:
                rem.searchPropertyById();
                break;
            case 4:
                rem.searchPropertyByAddress();
                break;
            case 5:
                rem.updateProperty();
                break;
            case 6:
                rem.deleteProperty();
                break;
            case 7:
                rem.saveToFile();
                break;
            case 8:
                rem.loadFromFile();
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}



