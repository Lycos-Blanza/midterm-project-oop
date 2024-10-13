#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

string toLowerString(const string str) {
    string lowerStr = str;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            lowerStr[i] = str[i] + 32;
        } else {
            lowerStr[i] = str[i];
        }
    }
    return lowerStr;
}

class Item {
protected:
    string id;
    string name;
    int quantity;
    double price;

public:
    Item(string id, string name, int quantity, double price) : id(id), name(name), quantity(quantity), price(price) {}

    virtual void Display() const = 0;

    virtual string GetCategory () const = 0;

    void UpdateQuantity(int newQuantity) {
        cout << "Quantity of Item " << name << " is updated from " << quantity << " to " << newQuantity << endl;
        quantity = newQuantity;
    }

    void UpdatePrice(double newPrice) {
        cout << "Price of Item " << name << " is updated from " << price << " to " << newPrice << endl;
        price = newPrice;
    }

    string getID() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    virtual ~Item() {}
};

class Clothing : public Item {
public:
    Clothing(string id, string name, int quantity, double price) : Item(id, name, quantity, price) {}

    void Display() const override {
        cout << setw(10) << id << setw(20) << name << setw(10) << quantity << setw(10) << price << setw(15) << "Clothing" << endl;
    }

    string GetCategory() const override {
        return "Clothing";
    }
};

class Electronics : public Item {
public:
    Electronics(string id, string name, int quantity, double price) : Item(id, name, quantity, price) {}

    void Display() const override {
        cout << setw(10) << id << setw(20) << name << setw(10) << quantity << setw(10) << price << setw(15) << "Electronics" << endl;
    }

    string GetCategory() const override {
        return "Electronics";
    }
};

class Entertainment : public Item {
public:
    Entertainment(string id, string name, int quantity, double price) : Item(id, name, quantity, price) {}

    void Display() const override {
        cout << setw(10) << id << setw(20) << name << setw(10) << quantity << setw(10) << price << setw(15) << "Entertainment" << endl;
    }

    string GetCategory() const override {
        return "Entertainment";
    }

};

Item* CreateItem(const string category, const string id, const string name, int quantity, double price) {
    string lowerCategory = toLowerString(category);
    if (lowerCategory == "clothing") {
        return new Clothing(id, name, quantity, price);
    } else if (lowerCategory == "electronics") {
        return new Electronics(id, name, quantity, price);
    } else if (lowerCategory == "entertainment") {
        return new Entertainment(id, name, quantity, price);
    } else {
        cout << "Category " << category << " does not exist!" << endl;
        return nullptr;
    }
}

class Inventory {
private:
    Item* inventory[15];
    int itemCount;
    string availableCategories[3] = { "Clothing", "Electronics", "Entertainment" };
public:
    Inventory() : itemCount(0) {
        for (int i = 0; i < 15; i++) {
            inventory[i] = nullptr;
        }
    }

    int getItemCount() const {
    return itemCount;
    }

    bool IDExists(const string id) const {
        for (int i = 0; i < itemCount; i++) {
            if (inventory[i]->getID() == id) {
                return true;
            }
        }
        return false;
    }

    void AddItem(Item* item) {
        if (itemCount < 15) {
            inventory[itemCount++] = item;
            cout << "Item added successfully!" << endl;
        } else {
            cout << "Inventory is full!" << endl;
        }
    }

    void UpdateItem(const string id, const string field, double newValue) {
        for (int i = 0; i < itemCount; i++) {
            if (inventory[i]->getID() == id) {
                string lowerField = toLowerString(field);
                if (lowerField == "quantity") {
                    inventory[i]->UpdateQuantity(newValue);
                } else if (lowerField == "price") {
                    inventory[i]->UpdatePrice(newValue);
                } else {
                    cout << "Invalid field. Use 'Quantity' or 'Price'." << endl;
                }
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void RemoveItem(string id) {
        for (int i = 0; i < itemCount; i++) {
            if (inventory[i]->getID() == id) {
                delete inventory[i];
                for (int j = i; j < itemCount - 1; j++) {
                    inventory[j] = inventory[j + 1];
                }
                inventory[itemCount--] = nullptr;
                cout << "Item removed successfully!" << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void DisplayItemsByCategory(const string category) const {
        string lowerCategory = toLowerString(category);
        bool categoryFound = false;

        for (int i = 0; i < itemCount; i++) {
            if (toLowerString(inventory[i]->GetCategory()) == lowerCategory) {
                categoryFound = true; 
                break; 
            }
        }

        if (!categoryFound) {
            cout << "No items found in the \"" << category << "\" category." << endl;
            SuggestAvailableCategories();
            return; 
        }

        cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" 
             << setw(10) << "Price" << setw(15) << "Category" << endl;
        cout << "--------------------------------------------------------------------" << endl;

        for (int i = 0; i < itemCount; i++) {
            if (toLowerString(inventory[i]->GetCategory()) == lowerCategory) {
                inventory[i]->Display();
            }
        }
    }

    void SuggestAvailableCategories() const {
        bool clothingAvailable = false;
        bool electronicsAvailable = false;
        bool entertainmentAvailable = false;

        for (int i = 0; i < itemCount; i++) {
            string category = toLowerString(inventory[i]->GetCategory());
            if (category == "clothing") {
                clothingAvailable = true;
            } else if (category == "electronics") {
                electronicsAvailable = true;
            } else if (category == "entertainment") {
                entertainmentAvailable = true;
            }
        }

        cout << "\nAvailable categories with items:" << endl;
        if (clothingAvailable) {cout << "- Clothing" << endl;}
        if (electronicsAvailable) {cout << "- Electronics" << endl;}
        if (entertainmentAvailable) {cout << "- Entertainment" << endl;}

        if (!clothingAvailable && !electronicsAvailable && !entertainmentAvailable) {
            cout << "No categories available." << endl;
        }
    }


    void DisplayAllItems() const {
        cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
        cout << "--------------------------------------------------------------------" << endl;
        for (int i = 0; i < itemCount; i++) {
            inventory[i]->Display();
        }
    }

    bool SearchItem(string id) const {
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i]->getID() == id) {
            cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
            cout << "--------------------------------------------------------------------" << endl;
            inventory[i]->Display();
            return true;
            }
        }
        return false;
    }

    void SortItemsByQuantity() {
        for (int i = 0; i < itemCount - 1; i++) {
            for (int j = 0; j < itemCount - i - 1; j++) {
                if (inventory[j]->getQuantity() > inventory[j + 1]->getQuantity()) {

                    Item* temp = inventory[j];
                    inventory[j] = inventory[j + 1];
                    inventory[j + 1] = temp;
                }
            }
        }
        cout << " ______________________________ \n";
        cout << "|      Sorted as Ascending     |\n";
        cout << "|         (By Quantity)        |\n";
        cout << "|______________________________| \n\n";
        DisplayAllItems();

    }
    
    void SortItemsByPrice() {
        for (int i = 0; i < itemCount - 1; i++) {
            for (int j = 0; j < itemCount - i - 1; j++) {
                if (inventory[j]->getPrice() > inventory[j + 1]->getPrice()) {

                    Item* temp = inventory[j];
                    inventory[j] = inventory[j + 1];
                    inventory[j + 1] = temp;
                }
            }
        }
        cout << " ______________________________ \n";
        cout << "|      Sorted as Ascending     |\n";
        cout << "|           (By Price)          |\n";
        cout << "|______________________________| \n\n";
        DisplayAllItems();

    }

    void SortItemsByQuantityDescending () {
        for (int i = 0; i < itemCount - 1; i++) {
        for (int j = 0; j < itemCount - i - 1; j++) {

            if (inventory[j]->getQuantity() < inventory[j + 1]->getQuantity()) {

                    Item* temp = inventory[j];
                    inventory[j] = inventory[j + 1];
                    inventory[j + 1] = temp;
                }
            }
        }
        cout << " ______________________________ \n";
        cout << "|      Sorted as Descending    |\n";
        cout << "|         (By Quantity)        |\n";
        cout << "|______________________________| \n\n";
        DisplayAllItems();

    }

    void SortItemsByPriceDescending() {
        for (int i = 0; i < itemCount - 1; i++) {
        for (int j = 0; j < itemCount - i - 1; j++) {

            if (inventory[j]->getPrice() < inventory[j + 1]->getPrice()) {

                    Item* temp = inventory[j];
                    inventory[j] = inventory[j + 1];
                    inventory[j + 1] = temp;
                }
            }
        }
        cout << " ______________________________ \n";
        cout << "|      Sorted as Descending    |\n";
        cout << "|          (By Price)          |\n";
        cout << "|______________________________| \n\n";
        DisplayAllItems();
    }

    void DisplayLowStockItems(int limit) const {
        bool hasLowStockItems = false;
        for (int i = 0; i < itemCount; i++) {
        if (inventory[i]->getQuantity() < limit) {
            if (!hasLowStockItems) {
                cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
                cout << "--------------------------------------------------------------------" << endl;
                hasLowStockItems = true;
            }
            inventory[i]->Display();
        }
    }
        if (!hasLowStockItems) {
            cout << "=== No low stock items found. ===" << endl;
        }
    }

    ~Inventory() {
        for (int i = 0; i < itemCount; i++) {
            delete inventory[i];
        }
    }
};

class Menu {
public:
    void MainMenu() {
        cout << " ______________________________ \n";
        cout << "|           Main Menu          |\n";
        cout << "|______________________________| \n\n";
        cout << "[1] Add Item\n";
        cout << "[2] Update Item\n";
        cout << "[3] Remove Item\n";
        cout << "[4] Display items by Category\n";
        cout << "[5] Display All Items\n";
        cout << "[6] Search Item\n";
        cout << "[7] Sort Items\n";
        cout << "[8] Display Low Stock Items\n";
        cout << "[9] Exit\n";
        cout << "\nEnter your Choice: ";
    }
};

int main() {
    Inventory inventory;
    Menu menu;
    int option;

    do {
        menu.MainMenu();
        cin >> option;

        switch (option) {
            case 1: {
                string id, name, category;
                int quantity;
                double price;
                cout << " ______________________________ \n";
                cout << "|          Item Adding         |\n";
                cout << "|______________________________|\n\n";
    
                while (true) {
                    cout << "\n\nAvailable Categories to choose from:"
                         << "\n- Clothing\n- Electronics\n- Entertainment\n";
                    cout << "\nEnter category: ";
                    cin >> category;

                    if (toLowerString(category) == "clothing" || toLowerString(category) == "electronics" || toLowerString(category) == "entertainment") {
                            break;
                    } else {
                        cout << "Invalid category! Please enter a valid category." << endl;
                    }
                }
    
                while (true) {
                    cout << "Enter ID: ";
                    cin >> id;
                    if (!inventory.IDExists(id)) {
                        break;
                    } else {
                        cout << "Item with ID " << id << " already exists! Please enter a different ID.\n" << endl;
                    }
                }

                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter Quantity: ";
                cin >> quantity;
                cout << "Enter Price: ";
                cin >> price;

                Item* item = CreateItem(category, id, name, quantity, price);
                if (item != nullptr) {
                    inventory.AddItem(item);
                }
                break;
            }

            case 2: {
                if (inventory.getItemCount() == 0) {
                    cout << "No items in the Inventory!" << endl;
                } else {
                    string id, field;
                    float newValue;
                    cout << " ______________________________ \n";
                    cout << "|         Updating Item        |\n";
                    cout << "|______________________________|\n\n";
                    cout << "\nEnter Item ID: "; cin >> id;

                if (!inventory.SearchItem(id)) {
                    cout << "Item not found!" << endl;
                    break; 
                }

                while (true) {
                    cout << "\nUpdate Field (Quantity / Price): "; cin >> field;
                    string lowerField = toLowerString(field);
                    if (lowerField == "quantity" || lowerField == "price") {
                        break;
                    } else {
                        cout << "Invalid field. Please enter 'Quantity' or 'Price'." << endl;
                    }
                }
                cout << "\nEnter New Value: "; cin >> newValue;
                inventory.UpdateItem(id, field, newValue);
                }
                break;
            }


            case 3: {
                if (inventory.getItemCount() == 0) {
                    cout << "No items in the Inventory!" << endl;
                } else {
                    string id;
                    cout << " ______________________________ \n";
                    cout << "|         Item Removing        |\n";
                    cout << "|______________________________|\n\n";
                    cout << "Enter ID of item to remove: "; cin >> id;
                    inventory.RemoveItem(id);
                }
                break;
            }

            case 4: {
                if (inventory.getItemCount() == 0) {
                    cout << "There are no items to Display." << endl;
                } else {
                    string category;
                    cout << " ______________________________ \n";
                    cout << "|    Display Items by Category |\n";
                    cout << "|______________________________|\n\n";
                    cout << "Enter Category (Clothing, Electronics, Entertainment): ";
                    cin >> category;

                    for (size_t i = 0; i < category.length(); ++i) {
                        if (category[i] >= 'A' && category[i] <= 'Z') {
                            category[i] = category[i] + ('a' - 'A');
                        }
                    }
                    inventory.DisplayItemsByCategory(category);
                }
                break;
            }

            case 5: {
                if (inventory.getItemCount() == 0) {
                    cout << "There are no items to Display." << endl;
                } else {
                    cout << " ______________________________ \n";
                    cout << "|     Displaying All Items     |\n";
                    cout << "|______________________________|\n\n";
                    inventory.DisplayAllItems();
                }
                break;
            }

            case 6: {
                if (inventory.getItemCount() == 0) {
                    cout << "There are no items in the inventory to search." << endl;
                } else {
                    string id;
                    cout << " ______________________________ \n";
                    cout << "|        Item Searching        |\n";
                    cout << "|______________________________|\n\n";
                    cout << "Enter ID to search: ";
                    cin >> id;
                    if (!inventory.SearchItem(id)) {
                        cout << "No item with ID \"" << id << "\" exists!" << endl;
                    }
                }
                break;
            }

            case 7: {
                if (inventory.getItemCount() == 0) {
                    cout << "There are no items in the Inventory." << endl;
                } else {
                    int sortOption;
                    cout << " ______________________________ \n";
                    cout << "|          Sort Items          |\n";
                    cout << "|______________________________|\n\n";
                    cout << "[1] Sort by Quantity\n";
                    cout << "[2] Sort by Price\n";
                    cout << "Select an option: ";
                    cin >> sortOption;

                    if (cin.fail() || (sortOption != 1 && sortOption != 2)) {
                        cin.clear();
                        cin.ignore(512, '\n');
                        cout << "Invalid sorting option! Please enter 1 or 2.\n" << endl;
                        break;
                    }

                    int order;
                    cout << "\n[1] Ascending\n";
                    cout << "[2] Descending\n";
                    cout << "Select an order option: ";
                    cin >> order;

                    if (cin.fail() || order < 1 || order > 2) {
                        cin.clear();
                        cin.ignore(512, '\n');
                        cout << "Invalid order option! Please enter a number between 1 and 2.\n" << endl;
                    break;
                    }

                    if (sortOption == 1) {
                        if (order == 1) { 
                            inventory.SortItemsByQuantity();
                        } else if (order == 2) {
                            inventory.SortItemsByQuantityDescending();
                        }
                    } else if (sortOption == 2) {
                        if (order == 1) {
                            inventory.SortItemsByPrice();
                        } else if (order == 2) {
                            inventory.SortItemsByPriceDescending();
                        }
                    }
                }
                break;
            }   

            case 8: {
                cout << " ______________________________ \n";
                cout << "|        Low Stock items       |\n";
                cout << "|______________________________|\n\n";
                if (inventory.getItemCount() == 0) {
                    cout << "There are no items in the inventory." << endl;
                } else {
                    inventory.DisplayLowStockItems(6);
                }
                break;
            }

            case 9: {
                cout << "Exiting program." << endl;
                break;
            }
            
            default:
                cout << "Invalid option. Please try again." << endl;
                break;
        }
        
    } while (option != 9);

    return 0;
}