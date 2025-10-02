#include <iostream>
#include <string>
#include <vector>
#include <limits>

class Product {
private:
    std::string name;
    double price;

public:
    Product(const std::string& name, double price) : name(name), price(price) {}

    std::string getName() const { return name; }
    double getPrice() const { return price; }
};

class Category {
private:
    std::string name;
    std::vector<Product> products;

public:
    Category(const std::string& name) : name(name) {}

    std::string getName() const { return name; }

    void addProduct(const Product& product) {
        products.push_back(product);
    }

    void displayProducts() const {
        std::cout << "Products in category \"" << name << "\":" << std::endl;
        for (size_t i = 0; i < products.size(); ++i) {
            std::cout << i + 1 << ". Name: " << products[i].getName() << ", Price: " << products[i].getPrice() << " rupees" << std::endl;
        }
        std::cout << std::endl;
    }

    const Product& getProductAtIndex(int index) const {
        return products[index];
    }

    int getProductCount() const {
        return products.size();
    }
};

class User {
private:
    std::string username;
    std::string password;
    std::vector<Product> cart;
    std::vector<Product> wishlist;
    std::vector<Product> orders;
    std::string paymentOption; // New member for payment option

public:
    User(const std::string& username, const std::string& password) : username(username), password(password) {}

    std::string getUsername() const { return username; }
    bool checkPassword(const std::string& pw) const { return password == pw; }

    void updatePassword(const std::string& new_password) {
        password = new_password;
        std::cout << "Password updated successfully." << std::endl;
    }

    void addToCart(const Product& product) {
        cart.push_back(product);
        std::cout << product.getName() << " added to cart." << std::endl;
    }

    void addToWishlist(const Product& product) {
        wishlist.push_back(product);
        std::cout << product.getName() << " added to wishlist." << std::endl;
    }

    void displayCart() const {
        if (cart.empty()) {
            std::cout << "Cart is empty." << std::endl;
        } else {
            std::cout << "Cart Items:" << std::endl;
            for (size_t i = 0; i < cart.size(); ++i) {
                std::cout << "- " << cart[i].getName() << ", Price: " << cart[i].getPrice() << " rupees" << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void placeOrder(const std::string& paymentOption) {
        if (cart.empty()) {
            std::cout << "Cart is empty. Cannot place order." << std::endl;
        } else {
            std::cout << "Order placed for items in cart." << std::endl;
            orders.insert(orders.end(), cart.begin(), cart.end());
            cart.clear();
            this->paymentOption = paymentOption; // Store payment option
        }
    }

    void cancelLastOrder() {
        if (orders.empty()) {
            std::cout << "No orders to cancel." << std::endl;
        } else {
            std::cout << "Cancelled last placed order." << std::endl;
            orders.pop_back();
        }
    }

    void displayOrders() const {
        if (orders.empty()) {
            std::cout << "No orders placed yet." << std::endl;
        } else {
            std::cout << "Order History:" << std::endl;
            for (size_t i = 0; i < orders.size(); ++i) {
                std::cout << "- " << orders[i].getName() << ", Price: " << orders[i].getPrice() << " rupees" << std::endl;
            }
            std::cout << "Payment Option Used: " << paymentOption << std::endl; // Display payment option
        }
        std::cout << std::endl;
    }
};

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void registerUser(std::vector<User>& users) {
    std::string username, password;
    std::cout << "\nEnter a username: ";
    std::getline(std::cin, username);

    bool usernameExists = false;
    for (int i = 0; i < users.size(); ++i) {
        if (users[i].getUsername() == username) {
            usernameExists = true;
            break;
        }
    }

    if (usernameExists) {
        std::cout << "Username already exists. Please choose a different username." << std::endl;
        return;
    }

    std::cout << "Enter a password: ";
    std::getline(std::cin, password);

    users.push_back(User(username, password));
    std::cout << "User registered successfully!" << std::endl;
}

User* loginUser(const std::vector<User>& users) {
    std::string username, password;
    std::cout << "\nEnter your username: ";
    std::getline(std::cin, username);

    for (int i = 0; i < users.size(); ++i) {
        if (users[i].getUsername() == username) {
            std::cout << "Enter your password: ";
            std::getline(std::cin, password);

            if (users[i].checkPassword(password)) {
                std::cout << "Login successful. Welcome, " << users[i].getUsername() << "!" << std::endl;
                return const_cast<User*>(&users[i]);
            } else {
                std::cout << "Incorrect password. Please try again." << std::endl;
                return 0;
            }
        }
    }

    std::cout << "User not found. Please register or check your username." << std::endl;
    return 0;
}

int main() {
    Category shoes("Shoes");
    shoes.addProduct(Product("Boots", 79.99));
    shoes.addProduct(Product("Heels", 99.99));
    shoes.addProduct(Product("Sneakers", 59.99));
    shoes.addProduct(Product("Sandals", 39.99));
    shoes.addProduct(Product("Slippers", 29.99));

    Category clothes("Clothes");
    clothes.addProduct(Product("T-Shirt", 29.99));
    clothes.addProduct(Product("Jeans", 49.99));
    clothes.addProduct(Product("Dress", 79.99));
    clothes.addProduct(Product("Jacket", 89.99));
    clothes.addProduct(Product("Socks", 9.99));

    Category electronics("Electronics");
    electronics.addProduct(Product("Laptop", 999.99));
    electronics.addProduct(Product("Smartphone", 699.99));
    electronics.addProduct(Product("Tablet", 399.99));
    electronics.addProduct(Product("Smartwatch", 199.99));
    electronics.addProduct(Product("Camera", 299.99));

    Category books("Books");
    books.addProduct(Product("Programming in C++", 49.99));
    books.addProduct(Product("Harry Potter and the Sorcerer's Stone", 12.99));
    books.addProduct(Product("The Great Gatsby", 9.99));
    books.addProduct(Product("Educated", 14.99));
    books.addProduct(Product("The Catcher in the Rye", 8.99));

    Category sports("Sports Equipment");
    sports.addProduct(Product("Soccer Ball", 19.99));
    sports.addProduct(Product("Basketball", 29.99));
    sports.addProduct(Product("Tennis Racket", 79.99));
    sports.addProduct(Product("Golf Clubs", 199.99));
    sports.addProduct(Product("Running Shoes", 49.99));

    Category beauty("Beauty Products");
    beauty.addProduct(Product("Perfume", 89.99));
    beauty.addProduct(Product("Makeup Kit", 59.99));
    beauty.addProduct(Product("Facial Cream", 29.99));
    beauty.addProduct(Product("Hair Straightener", 69.99));
    beauty.addProduct(Product("Shaving Kit", 19.99));

    Category home("Home Appliances");
    home.addProduct(Product("Microwave Oven", 149.99));
    home.addProduct(Product("Coffee Maker", 79.99));
    home.addProduct(Product("Vacuum Cleaner", 129.99));
    home.addProduct(Product("Air Purifier", 199.99));
    home.addProduct(Product("Blender", 39.99));

    Category music("Musical Instruments");
    music.addProduct(Product("Acoustic Guitar", 199.99));
    music.addProduct(Product("Keyboard", 299.99));
    music.addProduct(Product("Drum Set", 399.99));
    music.addProduct(Product("Violin", 249.99));
    music.addProduct(Product("Microphone", 79.99));

    std::vector<User> users;

    int choice;
    do {
        std::cout << "\nMain Menu:" << std::endl;
        std::cout << "1. Register" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Update Password" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1: {
                registerUser(users);
                break;
            }
            case 2: {
                User* currentUser = loginUser(users);
                if (currentUser != 0) {
                    int userChoice;
                    do {
                        std::cout << "\nWelcome, " << currentUser->getUsername() << "!" << std::endl;
                        std::cout << "User Menu:" << std::endl;
                        std::cout << "1. View Categories and Products" << std::endl;
                        std::cout << "2. View Cart" << std::endl;
                        std::cout << "3. View Wishlist" << std::endl;
                        std::cout << "4. Place Order" << std::endl;
                        std::cout << "5. Cancel Last Order" << std::endl;
                        std::cout << "6. Order History" << std::endl;
                        std::cout << "7. Update Password" << std::endl;
                        std::cout << "8. Logout" << std::endl;
                        std::cout << "Enter your choice: ";
                        std::cin >> userChoice;
                        clearInputBuffer();

                        switch (userChoice) {
                            case 1: {
                                int categoryChoice;
                                std::cout << "\nCategories:" << std::endl;
                                std::cout << "1. Shoes" << std::endl;
                                std::cout << "2. Clothes" << std::endl;
                                std::cout << "3. Electronics" << std::endl;
                                std::cout << "4. Books" << std::endl;
                                std::cout << "5. Sports Equipment" << std::endl;
                                std::cout << "6. Beauty Products" << std::endl;
                                std::cout << "7. Home Appliances" << std::endl;
                                std::cout << "8. Musical Instruments" << std::endl;
                                std::cout << "Enter category number: ";
                                std::cin >> categoryChoice;
                                clearInputBuffer();

                                const Category* chosenCategory = 0;
                                switch (categoryChoice) {
                                    case 1:
                                        chosenCategory = &shoes;
                                        break;
                                    case 2:
                                        chosenCategory = &clothes;
                                        break;
                                    case 3:
                                        chosenCategory = &electronics;
                                        break;
                                    case 4:
                                        chosenCategory = &books;
                                        break;
                                    case 5:
                                        chosenCategory = &sports;
                                        break;
                                    case 6:
                                        chosenCategory = &beauty;
                                        break;
                                    case 7:
                                        chosenCategory = &home;
                                        break;
                                    case 8:
                                        chosenCategory = &music;
                                        break;
                                    default:
                                        std::cout << "Invalid category choice." << std::endl;
                                        continue;
                                }

                                if (chosenCategory != 0) {
                                    chosenCategory->displayProducts();

                                    int productChoice;
                                    std::cout << "\nEnter product operation:" << std::endl;
                                    std::cout << "1. Add to Cart" << std::endl;
                                    std::cout << "2. Add to Wishlist" << std::endl;
                                    std::cout << "Enter your choice: ";
                                    std::cin >> productChoice;
                                    clearInputBuffer();

                                    int productIndex;
                                    std::cout << "Enter product number: ";
                                    std::cin >> productIndex;
                                    clearInputBuffer();

                                    if (productIndex > 0 && productIndex <= chosenCategory->getProductCount()) {
                                        const Product& selectedProduct = chosenCategory->getProductAtIndex(productIndex - 1);
                                        switch (productChoice) {
                                            case 1:
                                                currentUser->addToCart(selectedProduct);
                                                break;
                                            case 2:
                                                currentUser->addToWishlist(selectedProduct);
                                                break;
                                            default:
                                                std::cout << "Invalid choice." << std::endl;
                                                break;
                                        }
                                    } else {
                                        std::cout << "Invalid product number." << std::endl;
                                    }
                                }
                                break;
                            }
                            case 2:
                                currentUser->displayCart();
                                break;
                            case 3:
                                std::cout << "\nWishlist:" << std::endl; // Placeholder for display wishlist
                                // Display wishlist functionality (not fully implemented)
                                break;
                            case 4: {
                                std::string paymentOption;
                                std::cout << "Enter payment option (Credit Card, PayPal, etc.): ";
                                std::getline(std::cin, paymentOption);
                                currentUser->placeOrder(paymentOption);
                                break;
                            }
                            case 5:
                                currentUser->cancelLastOrder();
                                break;
                            case 6:
                                currentUser->displayOrders();
                                break;
                            case 7: {
                                std::string new_password;
                                std::cout << "\nEnter new password: ";
                                std::getline(std::cin, new_password);
                                currentUser->updatePassword(new_password);
                                break;
                            }
                            case 8:
                                std::cout << "\nLogging out." << std::endl;
                                break;
                            default:
                                std::cout << "\nInvalid choice. Please enter a valid option." << std::endl;
                        }
                    } while (userChoice != 8);
                }
                break;
            }
            case 3: {
                if (users.empty()) {
                    std::cout << "\nNo users registered yet. Please register first." << std::endl;
                } else {
                    std::string username;
                    std::cout << "\nEnter your username: ";
                    std::getline(std::cin, username);

                    bool found = false;
                    for (size_t i = 0; i < users.size(); ++i) {
                        if (users[i].getUsername() == username) {
                            std::string new_password;
                            std::cout << "Enter new password: ";
                            std::getline(std::cin, new_password);
                            users[i].updatePassword(new_password);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        std::cout << "User not found. Please check your username." << std::endl;
                    }
                }
                break;
            }
            case 4:
                std::cout << "\nExiting program." << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please enter a valid option." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
