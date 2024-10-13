#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

class Categories {
	public:
		virtual void Category() = 0;
};

class Clothing : public Categories {
	public:
		void Category() override {
			cout << "Items in clothing category:\n";
        	cout << "-------------------------------------------\n";
        	cout << "ID\tName\t\tQuantity\tPrice\n";
        	cout << "-------------------------------------------\n";	
			}
};

class Electronics : public Categories {
	public:
		void Category() override {
			cout << "Items in electronics category:\n";
        	cout << "-------------------------------------------\n";
        	cout << "ID\tName\t\tQuantity\tPrice\n";
        	cout << "-------------------------------------------\n";	
			}
};

class Entertainment : public Categories {
	public:
		void Category() override {
			cout << "Items in entertainment category:\n";
        	cout << "-------------------------------------------\n";
        	cout << "ID\tName\t\tQuantity\tPrice\n";
        	cout << "-------------------------------------------\n";	
			}
};

class Item {
private:
    string id, name, category;
    int quantity;
    double price;

public:
    Item(string id, string name, int quantity, double price, string category)
        : id(id), name(name), quantity(quantity), price(price), category(category) {}

    string getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }

    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }
};

class Inventory {
private:
    vector<Item*> items;

    void swap(Item*& a, Item*& b) {
        Item* temp = a;
        a = b;
        b = temp;
    }

    void sortItemsByQuantity(bool ascending) {
        int n = items.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if ((ascending && items[j]->getQuantity() > items[j + 1]->getQuantity()) ||
                    (!ascending && items[j]->getQuantity() < items[j + 1]->getQuantity())) {
                    swap(items[j], items[j + 1]);
                }
            }
        }
    }
    
    void sortItemsByPrice(bool ascending) {
        int n = items.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if ((ascending && items[j]->getPrice() > items[j + 1]->getPrice()) ||
                    (!ascending && items[j]->getPrice() < items[j + 1]->getPrice())) {
                    swap(items[j], items[j + 1]);
                }
            }
        }
    }
    
public:
	bool inventoryChecker() {
        if (items.empty()) {
            cout << "No items in inventory.\n";
            system("pause");
            system("cls");
            return true;
        }
        return false;
    }
    
    void displayAvailableItems() {
    	cout << "\nAvailable items in the inventory:\n";
	    cout << "----------------------------------------------------------------------------------\n";
	    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(20) << "Category" << endl;
	    cout << "----------------------------------------------------------------------------------\n";
	
	    for (const auto& item : items) {
	        cout << left << setw(10) << item->getId() << setw(20) << item->getName() << setw(10) << item->getQuantity() << setw(10) << fixed << setprecision(2) << item->getPrice() << setw(20) << item->getCategory() << endl;
	        }
	    cout << "----------------------------------------------------------------------------------\n";
	}
	 
    void addItem() {
	    string category, id, name ,quantityStr, priceStr;
	    int quantity;
	    double price;
	    bool condition = true;
	
	    while (condition) {
	    	system("cls");
	        cout << "=======================================\n";
            cout << "               Add Item\n";
            cout << "=======================================\n";
            cout << "             ~CATEGORIES~\n-Clothing\n-Electronics\n-Entertainment\n";
            cout << "\nEnter Category: ";
            cin >> category;
	
	        for (char &c : category) {
	            c = toupper(c);
	        }
	
	        if (category == "CLOTHING" || category == "ELECTRONICS" || category == "ENTERTAINMENT") {
	            condition = false;
	            break;
	        } else {
	            cout << "Category " << category << " does not exist! Please enter a valid category.\n";
	            system("pause");
	            system("cls");
	        }
	    }
	    
	    condition = true;
	    while (condition) {
	        cout << "Enter Item ID: ";
	        cin >> id;
	
	        bool idExists = false;
	        for (const auto& item : items) {
	            if (item->getId() == id) {
	                idExists = true;
	                break;
	            }
	        }
	
	        if (idExists) {
	            cout << "Item with ID " << id << " already exists! Please enter a different ID.\n";
	        } else {
	            condition = true;
	            break;
	        }
	    }
	
	    cout << "Enter Item Name: ";
	    cin.ignore();
	    getline(cin, name);
	
	    condition = true;
	    while (condition) {
	        cout << "Enter Quantity: ";
	        cin >> quantityStr;
	
	        bool isValid = true;
	        for (char c : quantityStr) {
	            if (!isdigit(c)) {
	                isValid = false;
	                break;
	            }
	        }
	
	        if (isValid) {
	            quantity = stoi(quantityStr);
	            if (quantity > 0) {
	                condition = false;
	            } else {
	                cout << "Quantity must be a positive integer. Please try again.\n";
	            }
	        } else {
	            cout << "Invalid input! Please enter a positive integer for Quantity.\n";
	        }
	    }
	
	    condition = true; 
	    while (condition) {
	        cout << "Enter Price: ";
	        cin >> priceStr;
	
	        bool isValid = true;
	        bool hasDecimalPoint = false;
	
	        for (size_t i = 0; i < priceStr.length(); ++i) {
	            if (priceStr[i] == '.') {
	                if (hasDecimalPoint) {
	                    isValid = false;
	                    break;
	                }
	                hasDecimalPoint = true;
	            } else if (!isdigit(priceStr[i])) {
	                isValid = false;
	                break;
	            }
	        }
	
	        if (isValid) {
	            price = stod(priceStr);
	            if (price > 0) {
	                condition = false;
	            } else {
	                cout << "Price must be a positive number. Please try again.\n";
	            }
	        } else {
	            cout << "Invalid input! Please enter a positive number for Price (use '.' for decimals).\n";
	        }
	    }
	
	    items.push_back(new Item(id, name, quantity, price, category));
	    cout << "Item added successfully!\n";
	
	    string addMore;
	    condition = true;
	    while (condition) {
	        cout << "Would you like to add another item? (y/n): ";
	        cin >> addMore;
	
	        if (addMore == "y" || addMore == "n") {
	            condition = false;
	            system("pause");
	        } else {
	            cout << "Invalid input! Please enter 'y' for Yes or 'n' for No.\n";
	        }
	    }
	
	    if (addMore == "y") {
	        addItem();
	    } else {
	        system("cls");
	    }
	}

    void updateItem() {
    	bool updateAnother = true;
	    
	    while (updateAnother) {
    	cout << "=======================================\n";
        cout << "              Update Item\n";
        cout << "=======================================\n";
        
	    if (inventoryChecker()) {
            return;
        }
	    	
	    displayAvailableItems();
	    	
	        string id;
	        bool itemFound = false;
	
	        while (!itemFound) {
	            cout << "Enter Item ID to update: ";
	            cin >> id;
	
	            for (auto& item : items) {
	                if (item->getId() == id) {
	                    itemFound = true;
	
	                    int choice;
	                    while (true) {
	                        cout << "What would you like to update?\n";
	                        cout << "1 - Quantity\n";
	                        cout << "2 - Price\n";
	                        cout << "Enter your choice: ";
	                        cin >> choice;
	
	                        if (cin.fail() || (choice != 1 && choice != 2)) {
	                            cout << "Invalid choice! Please enter 1 or 2.\n";
	                            cin.clear();
	                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	                        } else {
	                            break;
	                        }
	                    }
	
	                    if (choice == 1) {
	                        string inputQuantity;
	                        int newQuantity;
	
	                        while (true) {
	                            cout << "Enter new Quantity: ";
	                            cin >> inputQuantity;
	
	                            bool isValid = true;
	                            if (inputQuantity.empty()) {
	                                isValid = false;
	                            } else {
	                                for (char c : inputQuantity) {
	                                    if (!isdigit(c)) {
	                                        isValid = false;
	                                        break;
	                                    }
	                                }
	                                
	                                if (isValid && inputQuantity[0] == '0') {
	                                    isValid = false;
	                                }
	                            }
	
	                            if (isValid) {
	                                newQuantity = stoi(inputQuantity);
	                                break;
	                            } else {
	                                cout << "Invalid input! Please enter a pure positive integer.\n";
	                            }
	                        }
	
	                        int oldQuantity = item->getQuantity();
	                        item->setQuantity(newQuantity);
	                        cout << "Quantity of Item " << item->getName() << " is updated from " 
	                             << oldQuantity << " to " << newQuantity << ".\n";
	                    } else if (choice == 2) {
	                        string inputPrice;
	                        double newPrice;
	
	                        while (true) {
	                            cout << "Enter new Price: ";
	                            cin >> inputPrice;
	
	                            bool isValid = true;
	                            if (inputPrice.empty()) {
	                                isValid = false;
	                            } else {
	                                bool hasDecimalPoint = false;
	                                for (char c : inputPrice) {
	                                    if (!isdigit(c)) {
	                                        if (c == '.' && !hasDecimalPoint) {
	                                            hasDecimalPoint = true;
	                                        } else {
	                                            isValid = false;
	                                            break;
	                                        }
	                                    }
	                                }
	                                
	                                if (isValid && (inputPrice == "." || inputPrice == "0." || inputPrice[0] == '0')) {
	                                    isValid = false;
	                                }
	                            }
	
	                            if (isValid) {
	                                newPrice = stod(inputPrice);
	                                break;
	                            } else {
	                                cout << "Invalid input! Please enter a positive number.\n";
	                            }
	                        }
	
	                        double oldPrice = item->getPrice();
	                        item->setPrice(newPrice);
	                        cout << "Price of Item " << item->getName() << " is updated from " 
	                             << oldPrice << " to " << newPrice << ".\n";
	                    }
	                    
	                    string updateAgain;
	                    while (true) {
	                        cout << "Would you like to update another item? (y/n): ";
	                        cin >> updateAgain;
	                        if (updateAgain == "y") {
	                            updateAnother = true;
	                            system("cls");
	                            break;
	                        } else if (updateAgain == "n") {
	                            updateAnother = false;
	                            cout << "Returning to the main menu.\n";
	                            system("pause");
	                            system("cls");
	                            break;
	                        } else {
	                            cout << "Invalid input! Please enter 'y' for Yes or 'n' for No.\n";
	                        }
	                    }
	
	                    break;
	                }
	            }
	
	            if (!itemFound) {
	                cout << "Item not found! Please try again.\n";
	            }
	        }
	    }
	}

    void removeItem() {
	    string choice;
	    
	    do {
	        bool itemFound = false;
	        cout << "=======================================\n";
	        cout << "              Remove Item\n";
	        cout << "=======================================\n";
	
	        if (inventoryChecker()) {
            	return;
        	}
	
	        displayAvailableItems();
	
	        string id;
	        cout << "Enter Item ID to remove: ";
	        cin >> id;
	
	        for (auto it = items.begin(); it != items.end(); ++it) {
	            if ((*it)->getId() == id) {
	                cout << "Item " << (*it)->getName() << " has been removed from the inventory.\n";
	                delete *it;
	                items.erase(it);
	                itemFound = true;
	                break;
	            }
	        }
	
	        if (!itemFound) {
	            cout << "Item not found! Please enter a valid Item ID.\n";
	        }
	
	        while (true) {
	            cout << "Would you like to remove another item? (y/n): ";
	            cin >> choice;
	            
	            if (choice.length() == 1 && (choice[0] == 'y' || choice[0] == 'n')) {
	                break;
	            } else {
	                cout << "Invalid input! Please enter only 'y' for yes or 'n' for no.\n";
	            }
	        }
	
	        system("pause");
	        system("cls");
	
	    } while (choice[0] == 'y');
	}

	void displayItemsByCategory() {
		Clothing clothingCat;
    	Electronics electronicsCat;
    	Entertainment entertainmentCat;
	    string choice;
	
	    do {
	    	cout << "=======================================\n";
	        cout << "       Display Items By Category\n";
	        cout << "=======================================\n";
	        
	        if (inventoryChecker()) {
            	return;
        	}
	
	        string category;
	        bool validCategory = false;
	
	        while (!validCategory) {
	            cout << "             ~CATEGORIES~\n-Clothing\n-Electronics\n-Entertainment\n";
            	cout << "\nEnter Category: ";
	            cin >> category;
	
	            for (char &c : category) {
	                c = toupper(c);
	            }
	
	            if (category == "CLOTHING" || category == "ELECTRONICS" || category == "ENTERTAINMENT") {
	                validCategory = true;
	            } else {
	                cout << "Category " << category << " does not exist! Please enter a valid category.\n";
	                system("pause");
	                system("cls");
	            }
	        }
	
	        bool found = false;
	        clothingCat.Category();
	
	        for (const auto& item : items) {
	            if (item->getCategory() == category) {
	                found = true;
	                cout << item->getId() << "\t" << item->getName() << "\t\t" 
	                     << item->getQuantity() << "\t\t" << item->getPrice() << "\n";
	            }
	        }
	
	        if (!found) {
	            cout << "No items found in the " << category << " category.\n";
	        }
	
	        while (true) { // Loop until valid input is received
	            cout << "\nWould you like to enter another category? (y/n): ";
	            cin >> choice;
	
	            // Validate that input is exactly one character
	            if (choice.length() == 1 && (choice[0] == 'y' || choice[0] == 'n')) {
	                break; // Valid input, exit the loop
	            } else {
	                cout << "Invalid input! Please enter only 'y' for yes or 'n' for no.\n";
	            }
	        }
	
	        system("pause");
	        system("cls");
	
	    } while (choice[0] == 'y'); 
	}

	void displayAllItems() {
		cout << "=======================================\n";
        cout << "           Display All Items\n";
        cout << "=======================================\n";
            
        if (inventoryChecker()) {
            	return;
        	}

        displayAvailableItems();
        system("pause");
        system("cls");
    }
    
    void searchItem() {
	    string choice;
	
	    do {
	        cout << "=======================================\n";
	        cout << "              Search Item\n";
	        cout << "=======================================\n";
	
	        if (inventoryChecker()) {
            	return; 
        	}
	
	        displayAvailableItems();
	
	        string id;
	        cout << "Enter Item ID to search: ";
	        cin >> id;
	
	        bool itemFound = false;
	
	        for (const auto& item : items) {
	            if (item->getId() == id) {
	                cout << "\nItem Found:\n";
	                cout << "-------------------------------------------\n";
	                cout << "ID: " << item->getId() << "\n";
	                cout << "Name: " << item->getName() << "\n";
	                cout << "Quantity: " << item->getQuantity() << "\n";
	                cout << "Price: " << item->getPrice() << "\n";
	                cout << "Category: " << item->getCategory() << "\n";
	                cout << "-------------------------------------------\n";
	                itemFound = true;
	                break;
	            }
	        }
	
	        if (!itemFound) {
	            cout << "Item not found!\n";
	        }
	
	        while (true) { 
	            cout << "Would you like to search for another item? (y/n): ";
	            cin >> choice;
	
	            if (choice.length() == 1 && (choice[0] == 'y' || choice[0] == 'n')) {
	                break; 
	            } else {
	                cout << "Invalid input! Please enter only 'y' for yes or 'n' for no.\n";
	            }
	        }
	
	        system("pause");
	        system("cls");
	
	    } while (choice[0] == 'y'); 
	}
	
    void sortItems() {
    	string choice;

    	do {
		    cout << "=======================================\n";
		    cout << "               Sort Items\n";
		    cout << "=======================================\n";
		    
		    if (inventoryChecker()) {
            	return;
        	}
		
		    string sortChoice, orderChoice;
		    bool validSortChoice = false, validOrderChoice = false; 
		
		    while (!validSortChoice) {
		        cout << "Sort by:\n";
		        cout << "1 - Quantity\n";
		        cout << "2 - Price\n";
		        cout << "Enter your choice: ";
		        cin >> sortChoice;
		
		        if (sortChoice.length() == 1 && (sortChoice[0] == '1' || sortChoice[0] == '2')) {
		            validSortChoice = true;
		        } else {
		            cout << "Invalid input! Please enter only '1' for Quantity or '2' for Price.\n";
		        }
		    }
		
		    while (!validOrderChoice) {
		        cout << "Sort order:\n";
		        cout << "1 - Ascending\n";
		        cout << "2 - Descending\n";
		        cout << "Enter your choice: ";
		        cin >> orderChoice;
		
		        if (orderChoice.length() == 1 && (orderChoice[0] == '1' || orderChoice[0] == '2')) {
		            validOrderChoice = true; 
		        } else {
		            cout << "Invalid input! Please enter only '1' for Ascending or '2' for Descending.\n";
		        }
		    }
		
		    int sortOption = stoi(sortChoice);
		    int orderOption = stoi(orderChoice);
		    bool ascending = (orderOption == 1);
		
		    if (sortOption == 1) {
		        sortItemsByQuantity(ascending);
		    } else if (sortOption == 2) {
		        sortItemsByPrice(ascending);
		    }
		
		    cout << "\nSorted Items:\n";
		    cout << "------------------------------------------------------\n";
		    cout << "ID\tName\t\tQuantity\tPrice\n";
		    cout << "------------------------------------------------------\n";
		    for (const auto& item : items) {
		        cout << item->getId() << "\t" << item->getName() << "\t\t"
		             << item->getQuantity() << "\t\t" << item->getPrice() << "\n";
		    }
		    
	        while (true) {
	            cout << "Would you like to search for another item? (y/n): ";
	            cin >> choice;
	
	            if (choice.length() == 1 && (choice[0] == 'y' || choice[0] == 'n')) {
	                break;
	            } else {
	                cout << "Invalid input! Please enter only 'y' for yes or 'n' for no.\n";
	            }
	        }
	        system("pause");
	        system("cls");
	    } while (choice[0] == 'y');
	}
    
    void displayLowStockItems() {
    	cout << "=======================================\n";
        cout << "        Display Low Stock Items\n";
        cout << "=======================================\n";
        
    	if (inventoryChecker()) {
            	return; 
        	}
	    
        cout << "\nLow Stock Items (Quantity <= 5):\n";
        cout << "------------------------------------------------------\n";
        cout << "ID\tName\t\tQuantity\tPrice\tCategory\n";
        cout << "------------------------------------------------------\n";

        bool foundLowStock = false;

        for (const auto& item : items) {
            if (item->getQuantity() <= 5) {
                cout << item->getId() << "\t" << item->getName() << "\t\t"
                     << item->getQuantity() << "\t\t" << item->getPrice() << "\t"
                     << item->getCategory() << "\n";
                foundLowStock = true;
            }
        }
        if (!foundLowStock) {
            cout << "No low stock items found!\n";
        }

        cout << "------------------------------------------------------\n";
        system("pause");
        system("cls");
    }

    ~Inventory() {
        for (auto item : items) delete item;
    }
};

void validateChoice(int &choice, int min, int max) {
    string input;

    while (true) {
        cout << "Enter your choice: "; 
        cin >> input;

        bool isValid = true;
        for (char c : input) {
            if (!isdigit(c)) {
                isValid = false;
                break;
            }
        }
        
        if (isValid) {
            choice = stoi(input); 
            if (choice >= min && choice <= max) {
                break; 
            }
        }
        cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
    }
}

int main() {
    Inventory inventory;
    int choice;
    bool condition = true;

    while (condition) {
        cout << "=======================================\n";
        cout << "     Inventory Management System\n";
        cout << "=======================================\n";
        cout << "1 - Add Item\n";
        cout << "2 - Update Item\n";
        cout << "3 - Remove Item\n";
        cout << "4 - Display Items by Category\n";
        cout << "5 - Display All Items\n";
        cout << "6 - Search Item\n";
        cout << "7 - Sort Items\n";
        cout << "8 - Display Low Stock Items\n";
        cout << "9 - Exit\n\n";
        validateChoice(choice, 1, 9);
        system("cls");

        if (choice == 1) {
            inventory.addItem();
        } else if (choice == 2) {
            inventory.updateItem();
        } else if (choice == 3) {
            inventory.removeItem();
        } else if (choice == 4) {
            inventory.displayItemsByCategory();
        } else if (choice == 5) {
            inventory.displayAllItems();
        } else if (choice == 6) {
            inventory.searchItem();
        } else if (choice == 7) {
            inventory.sortItems();
        } else if (choice == 8) {
            inventory.displayLowStockItems();
        } else if (choice == 9) {
            cout << "Exiting the program. Goodbye!\n";
            condition = false;
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}