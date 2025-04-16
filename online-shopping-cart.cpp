#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Abstract Product class (Abstraction)
class Product {
protected:
    string name;
    double price;

public:
    Product(string n, double p) : name(n), price(p) {}
    virtual void displayDetails() = 0; // pure virtual function
    double getPrice() const { return price; }
    virtual ~Product() {}
};

// Clothing class (Inheritance)
class Clothing : public Product {
private:
    string size;

public:
    Clothing(string n, double p, string s) : Product(n, p), size(s) {}

    void displayDetails() override {
        cout << "Clothing - " << name << " [Size: " << size << "] - Rs." << price << endl;
    }
};

// Electronics class (Inheritance)
class Electronics : public Product {
private:
    int warrantyMonths;

public:
    Electronics(string n, double p, int w) : Product(n, p), warrantyMonths(w) {}

    void displayDetails() override {
        cout << "Electronics - " << name << " [Warranty: " << warrantyMonths << " months] - Rs." << price << endl;
    }
};

// ShoppingCart class (Encapsulation)
class ShoppingCart {
private:
    vector<Product*> items;

public:
    void addItem(Product* product) {
        items.push_back(product);
        cout << product->getPrice() << " item added to cart." << endl;
    }

    void viewCart() {
        if (items.empty()) {
            cout << "Your cart is empty." << endl;
            return;
        }

        cout << "\nItems in Cart:" << endl;
        for (auto item : items) {
            item->displayDetails();
        }
    }

    double calculateTotal() {
        double total = 0;
        for (auto item : items) {
            total += item->getPrice();
        }
        return total;
    }

    double applyDiscount() {
        double total = calculateTotal();
        double discount = 0.0;

        if (total >= 2000) {
            discount = total * 0.10; // 10% discount
        }

        return discount;
    }

    void checkout() {
        viewCart();
        double total = calculateTotal();
        double discount = applyDiscount();
        double finalAmount = total - discount;

        cout << "\nTotal Amount: Rs." << total;
        if (discount > 0)
            cout << "\nDiscount Applied: Rs." << discount;
        cout << "\nAmount to Pay: Rs." << finalAmount << endl;
    }

    ~ShoppingCart() {
        for (auto item : items) {
            delete item;
        }
    }
};

int main() {
    ShoppingCart cart;
    int choice;

    while (true) {
        cout << "\n===== Online Shopping Cart =====" << endl;
        cout << "1. Add Clothing Item" << endl;
        cout << "2. Add Electronics Item" << endl;
        cout << "3. View Cart" << endl;
        cout << "4. Checkout" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, size;
            double price;
            cout << "Enter Clothing Name: ";
            cin >> name;
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Size: ";
            cin >> size;
            cart.addItem(new Clothing(name, price, size));
        }
        else if (choice == 2) {
            string name;
            double price;
            int warranty;
            cout << "Enter Electronics Name: ";
            cin >> name;
            cout << "Enter Price: ";
            cin >> price;
            cout << "Enter Warranty (months): ";
            cin >> warranty;
            cart.addItem(new Electronics(name, price, warranty));
        }
        else if (choice == 3) {
            cart.viewCart();
        }
        else if (choice == 4) {
            cart.checkout();
        }
        else if (choice == 5) {
            cout << "Thanks for shopping! Goodbye." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
