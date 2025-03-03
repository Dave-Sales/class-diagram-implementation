#include <iostream>
using namespace std;

class Product {
public:
    string productID;
    string name;
    double price;

    Product(string id, string n, double p) {
        productID = id;
        name = n;
        price = p;
    }
};

class ShoppingCart {
private:
    Product* products[100];
    int quantities[100];
    int count;

public:
    ShoppingCart() {
        count = 0;
    }

    int getCount() const {
        return count;
    }

    Product* getProduct(int index) const {
        return products[index];
    }

    int getQuantity(int index) const {
        return quantities[index];
    }

    void addProduct(Product* p, int quantity) {
        for (int i = 0; i < count; i++) {
            if (products[i] == p) {
                quantities[i] += quantity;
                cout << "Product quantity updated!" << endl;
                return;
            }
        }
        if (count < 100) {
            products[count] = p;
            quantities[count] = quantity;
            count++;
            cout << "===================================="<<endl;
            cout << "Product added successfully!" << endl;
            cout << "===================================="<<endl;
        } else {
            cout << "Cart is full!" << endl;
        }
    }

    void viewCart() {
        if (count == 0) {
            cout << "Shopping cart is empty." << endl;
            return;
        }
        cout << "===================================="<<endl;
        cout << "ID\tName\tPrice\tQuantity" << endl;
        for (int i = 0; i < count; i++) {
            cout << products[i]->productID << "\t" << products[i]->name << "\t" << products[i]->price << "\t" << quantities[i] << endl;
        }
    }

    void clearCart() {
        count = 0;
    }
};

class Order {
private:
    Product* orderedProducts[100][100];
    int orderQuantities[100][100];
    int orderCounts[100];
    double totalAmounts[100];
    int totalOrders;

public:
    Order() {
        totalOrders = 0;
    }

    void checkout(ShoppingCart& cart) {
        if (cart.getCount() == 0) {
            cout << "Cart is empty, nothing to checkout." << endl;
            return;
        }
        totalAmounts[totalOrders] = 0;
        orderCounts[totalOrders] = cart.getCount();

        for (int i = 0; i < cart.getCount(); i++) {
            orderedProducts[totalOrders][i] = cart.getProduct(i);
            orderQuantities[totalOrders][i] = cart.getQuantity(i);
            totalAmounts[totalOrders] += orderedProducts[totalOrders][i]->price * orderQuantities[totalOrders][i];
        }

        totalOrders++;
        cart.clearCart();

        cout << "==============================================="<<endl;
        cout << "You have successfully checked out the products!" << endl;
        cout << "==============================================="<<endl;
    }

    void viewOrders() {
        if (totalOrders == 0) {
            cout << "No orders available." << endl;
            return;
        }
        for (int o = 0; o < totalOrders; o++) {
            cout << "===================================="<<endl;
            cout << "Order ID: " << o + 1 << endl;
            cout << "ID:\tName:\tPrice:\tQuantity:" << endl;
            for (int i = 0; i < orderCounts[o]; i++) {
                cout << orderedProducts[o][i]->productID << "\t" << orderedProducts[o][i]->name << "\t" << orderedProducts[o][i]->price << "\t" << orderQuantities[o][i] << endl;
            }
            cout << "===================================="<<endl;
            cout << "Total Amount: " << totalAmounts[o] << endl;
            cout << "===================================="<<endl;
        }
    }
};

int main() {
    Product products[] = {
        Product("ABC", "Paper",  20),
        Product("CDE", "Pencil", 10),
        Product("QWE", "Eraser", 50)
    };
    
    ShoppingCart cart;
    Order order;
    
    int choice;
    do {
        cout << "Menu:\n1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "===================================="<<endl;
            cout << "ID:\tName:\tPrice:" << endl;
            for (int i = 0; i < 3; i++) {
                cout << products[i].productID << "\t" << products[i].name << "\t" << products[i].price << endl;
            }
            string prodID;
            int quantity;
            cout << "===================================="<<endl;
            cout << "Enter product ID to add to cart: ";   
            cin >> prodID;
            cout << "Enter quantity: ";
            cin >> quantity;
            bool found = false;
            for (int i = 0; i < 3; i++) {
                if (products[i].productID == prodID) {
                    cart.addProduct(&products[i], quantity);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Invalid ID!" << endl;
            }
        } else if (choice == 2) {
            cart.viewCart();
            char checkoutChoice;
            cout << "Do you want to check out? (Y/N): ";
            cin >> checkoutChoice;
            if (checkoutChoice == 'Y' || checkoutChoice == 'y') {
                order.checkout(cart);
            }
        } else if (choice == 3) {
            order.viewOrders();
        }
    } while (choice != 4);
    
    return 0;
}
