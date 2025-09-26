#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

const int MAX_PRODUCTS = 100;
const int NAME_LEN = 50;
const int CATEGORY_LEN = 30;
const int LOW_STOCK_THRESHOLD = 10;

struct Product {
    int id;
    char name[NAME_LEN];
    int quantity;
    float price;
    char category[CATEGORY_LEN];
};

Product inventory[MAX_PRODUCTS];
int productCount = 0;

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        cout << "Inventory full!\n";
        return;
    }

    int id;
    cout << "Enter Product ID: ";
    cin >> id;

    // Check uniqueness
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            cout << "Product ID must be unique.\n";
            return;
        }
    }

    inventory[productCount].id = id;
    cout << "Enter Product Name: ";
    cin.ignore();
    cin.getline(inventory[productCount].name, NAME_LEN);

    cout << "Enter Category: ";
    cin.getline(inventory[productCount].category, CATEGORY_LEN);

    cout << "Enter Quantity in Stock: ";
    cin >> inventory[productCount].quantity;
    cout << "Enter Price per Unit: ";
    cin >> inventory[productCount].price;

    productCount++;
    cout << "Product Added Successfully!\n";
}

void updateProduct() {
    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            cout << "Enter New Quantity: ";
            cin >> inventory[i].quantity;
            cout << "Enter New Price: ";
            cin >> inventory[i].price;
            cout << "Product Updated Successfully!\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void removeProduct() {
    int id;
    cout << "Enter Product ID to remove: ";
    cin >> id;

    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == id) {
            for (int j = i; j < productCount - 1; j++) {
                inventory[j] = inventory[j + 1];
            }
            productCount--;
            cout << "Product Removed Successfully!\n";
            return;
        }
    }
    cout << "Product not found.\n";
}

void viewInventory() {
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Category" << setw(10) << "Qty" << setw(10) << "Price" << endl;
    for (int i = 0; i < productCount; i++) {
        cout << left << setw(10) << inventory[i].id
             << setw(20) << inventory[i].name
             << setw(15) << inventory[i].category
             << setw(10) << inventory[i].quantity
             << setw(10) << inventory[i].price << endl;
    }
}

void searchProduct() {
    char keyword[NAME_LEN];
    cout << "Enter product name or category to search: ";
    cin.ignore();
    cin.getline(keyword, NAME_LEN);

    for (int i = 0; i < productCount; i++) {
        if (strstr(inventory[i].name, keyword) || strstr(inventory[i].category, keyword)) {
            cout << "Found: " << inventory[i].name << " (ID: " << inventory[i].id << ")\n";
        }
    }
}

void lowStockAlert() {
    cout << "Low Stock Products (less than " << LOW_STOCK_THRESHOLD << "):\n";
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].quantity < LOW_STOCK_THRESHOLD) {
            cout << inventory[i].name << " (ID: " << inventory[i].id << ") - Qty: " << inventory[i].quantity << endl;
        }
    }
}

void calculateTotalValue() {
    float total = 0;
    for (int i = 0; i < productCount; i++) {
        total += inventory[i].price * inventory[i].quantity;
    }
    cout << "Total Inventory Value: $" << total << endl;
}

void saveToFile() {
    ofstream out("inventory.txt");
    out << productCount << endl;
    for (int i = 0; i < productCount; i++) {
        out << inventory[i].id << "\n" << inventory[i].name << "\n" << inventory[i].category << "\n"
            << inventory[i].quantity << "\n" << inventory[i].price << endl;
    }
    out.close();
}

void loadFromFile() {
    ifstream in("inventory.txt");
    if (!in) return;
    in >> productCount;
    in.ignore();
    for (int i = 0; i < productCount; i++) {
        in >> inventory[i].id;
        in.ignore();
        in.getline(inventory[i].name, NAME_LEN);
        in.getline(inventory[i].category, CATEGORY_LEN);
        in >> inventory[i].quantity;
        in >> inventory[i].price;
        in.ignore();
    }
    in.close();
}

int main() {
    loadFromFile();
    int choice;
    char again;
    do {
        cout << "\nInventory Management System\n";
        cout << "1. Add New Product\n";
        cout << "2. Update Existing Product\n";
        cout << "3. Remove Product\n";
        cout << "4. View Inventory\n";
        cout << "5. Search Product\n";
        cout << "6. View Low Stock Alerts\n";
        cout << "7. Calculate Total Inventory Value\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
             addProduct(); 
            break;
            case 2:
             updateProduct();
              break;
            case 3:
             removeProduct();
             break;
            case 4: 
            viewInventory();
             break;
            case 5:
             searchProduct();
              break;
            case 6:
             lowStockAlert();
              break;
            case 7: 
            calculateTotalValue(); 
            break;
            case 8:
             saveToFile();
              cout << "Goodbye!\n"; 
              return 0;
            default: 
            cout << "Invalid choice.\n";
        }

        cout << "Would you like to perform another operation? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    saveToFile();
    return 0;
}
