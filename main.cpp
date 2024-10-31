#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

void clearScreen();

class Ornament {
    std::string name;
    float amount;
    float price; // per bucata

public:
    Ornament(std::string  n, float amnt, float p ) : name(std::move(n)), amount(amnt), price(p) {}

    Ornament(const Ornament& other) : name(other.name), amount(other.amount), price(other.price) {}

    Ornament& operator=(const Ornament& other) {
        if (this != &other) {
            name = other.name;
            amount = other.amount;
            price = other.price;
        }
        return *this;
    }

    [[nodiscard]] const std::string& getName() const& {
        return name;
    }

    [[nodiscard]] float getAmount() const {
        return amount;
    }

    [[nodiscard]] float getPrice() const {
        return price;
    }

    ~Ornament() {}

    friend std::ostream& operator<<(std::ostream& os, const Ornament& ornm) {
        os << ornm.name << " (" << ornm.amount << " grams)";
        return os;
    }
};

class CakeDetails {
    std::string CakeName;
    std::string flavor;
    std::string cream;
    std::string message;
    std::vector<Ornament> ornaments;
    int tiers;
    int days_until_expiration;
    float weight_without_ornaments;
    float price_per_kg;
    bool sugarfree;
    bool glutenfree;

public:
    CakeDetails(const std::string &cknm, const std::string& flv, std::string cr, const std::string& msg,
             const std::vector<Ornament>& ornm, int t, int days, float w, float price , bool nosugar, bool nogluten)
    : CakeName(cknm), flavor(flv), cream(std::move(cr)), message(msg), ornaments(ornm), tiers(t),
      days_until_expiration(days), weight_without_ornaments(w), price_per_kg(price), sugarfree(nosugar), glutenfree(nogluten) {}

    [[nodiscard]] bool isSugarfree() const {
        return sugarfree;
    }

    [[nodiscard]] bool isGlutenfree() const {
        return glutenfree;
    }

    // [[nodiscard]] const std::string& getCakeName() const {
    //     return CakeName;
    // }

    [[nodiscard]] const std::string& getFlavor() const {
        return flavor;
    }

    [[nodiscard]] const std::string& getCream() const {
        return cream;
    }

    [[nodiscard]] int getTiers() const {
        return tiers;
    }

    [[nodiscard]] float getWeight() const {
        return weight_without_ornaments;
    }

    [[nodiscard]] float getPricePerKg() const {
        return price_per_kg;
    }

    [[nodiscard]] const std::string& getMessage() const {
        return message;
    }

    [[nodiscard]] int getDaysUntilExpiration() const {
        return days_until_expiration;
    }

    // const std::vector<Ornament>& getOrnaments() const {
    //     return ornaments;
    // }
    void TotalWeight() const {
        float total_weight = this->weight_without_ornaments;
        for (const auto& ornm : ornaments) {
            total_weight += ornm.getAmount();
        }
        std::cout << "Total weight for the cake is: " << total_weight << " killograms "<< std::endl;
    }

    void CostOfCake() const {
        float price = this->weight_without_ornaments * this->price_per_kg;
        for (const auto& ornm : ornaments) {
            price += ornm.getPrice();
        }
        std::cout << "Cost of Cake with ornaments: " << price << std::endl;
    }

    void displaySummary() const {
        std::cout << "Flavor of the cake base: " << getFlavor() << std::endl;
        std::cout << "Number of tiers: " << getTiers() << std::endl;
        std::cout << "Weight of the cake (edible): " << getWeight() << " killograms" << std::endl;
        std::cout << "Covering cream: " << getCream() << std::endl;
        std::cout << "Price per kg: " << getPricePerKg() << std::endl;
        std::cout << "Days until expiration: " << getDaysUntilExpiration() << std::endl;
        std::cout << "Message on the cake(can be changed if requested) : " << getMessage() << std::endl;
        std::cout << "Ornaments (on top of cake): ";
        for (const auto& ornm : ornaments) {
            std::cout << ornm.getName() << " "<<std::endl;
        }
        std::cout <<"\n";
        std::cout << "Does it contain sugar? " << (isSugarfree() ? " no" : " yes") << "\n";
        std::cout << "Is it gluten free? " << (isGlutenfree() ? " yes\n" : " no\n") << "\n";
        std::cout << "All cakes have carefully chosen details that add to the weight and the price of the cake. Here are some more details: \n\n";
        TotalWeight();
        CostOfCake();
        std::cout << std::endl;
    }

};

class Order {
    int orderID;
    static int orderCounter;
    CakeDetails cake;
    std::string DateOfDelivery;
    std::string payment;

public:
    Order(const CakeDetails& ck, std::string Delivery, std::string pay)
    : cake(ck), DateOfDelivery(std::move(Delivery)), payment(std::move(pay)) {
        orderID = ++orderCounter;
    }

    [[nodiscard]] int getOrderID() const {
        return orderID;
    }

    [[nodiscard]] const CakeDetails& getCakeDetails() const {
        return cake;
    }

    [[nodiscard]] const std::string& getDateOfDelivery() const {
        return DateOfDelivery;
    }

    [[nodiscard]] const std::string& getPayment() const {
        return payment;
    }

    ~Order() {
        std::cout << "Order destructor for number: " << orderID << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Order& order){
        os << "Order ID: " << order.getOrderID() << " Cake: ";
        order.getCakeDetails().displaySummary();
        os << " Delivery date: " << order.getDateOfDelivery() << " Payment method: " << order.getPayment() << std::endl;
        return os;
    }
};

class Client {
private:
    std::string name;
    std::string phoneNumber;
    std::string OrderAddress;
    std::string EmailAddress;
    Order order;

public:
    Client(std::string nm, std::string phone, std::string adrs, std::string email, const Order &ord)
    : name(std::move(nm)), phoneNumber(std::move(phone)), OrderAddress(std::move(adrs)), EmailAddress(std::move(email)), order(ord) {}

    [[nodiscard]] const std::string& getName() const {
        return name;
    }

    // [[nodiscard]] const std::string& getEmailAddress() const {
    //     return EmailAddress;
    // }

    // [[nodiscard]] const std::string& getPhoneNumber() const {
    //     return phoneNumber;
    // }

    // [[nodiscard]] const std::string& getAddress() const {
    //     return OrderAddress;
    // }

    // [[nodiscard]] const Order& getOrder() const {
    //     return order;
    // }

    friend std::ostream& operator<<(std::ostream& os, const Client& cust) {
        os << "Customer: " << cust.name << ", Phone: " << cust.phoneNumber << " Email: " << cust.EmailAddress << " Address: " << cust.OrderAddress << std::endl;
        return os;
    }
};
int Order::orderCounter = 0;

void displayWelcomeMessage(  ) {
    std::string line1 = "        Welcome to";
    std::string line2 = "    Sweet Spell Bakery!";
    int delay = 300;

    std::cout << "---------------------------------------------------------\n";
    std::cout << "*********************************************************\n";
    std::cout << "*                ";
    std::string word = "";

    for (char caracter : line1) {
        if (caracter == ' ') {
            std::cout << word << " ";
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            word.clear();  // reset word for the next
        } else {
            word += caracter; }
    }
    std::cout << word << "                     *\n";
    std::cout << "*                ";
    word = "";

    for (char caracter : line2) {
        if (caracter == ' ') {
            std::cout << word << " ";
            std::cout.flush();
            std::this_thread::sleep_for( std::chrono::milliseconds(delay) );
            word.clear();
        } else {
            word += caracter;
        }
    }
    std::cout << word << "                *\n";

    std::cout << "---------------------------------------------------------\n"
     << "*********************************************************\n"
     << "*                                                       *\n"
     << "*                        *   *   *                      *\n"
     << "*                        |   |   |                      *\n"
     << "*                     ~~~~~~~~~~~~~~~                   *\n"
     << "*                    |we all love cake|                 *\n"
     << "*                    ******************                 *\n"
     << "*                   |     *      *     |                *\n"
     << "*                  **********************               *\n"
     << "*                 |      *   * *   *     |              *\n"
     << "*                 ************************              *\n"
     << "*                | *       *     *      * |             *\n"
     << "*                |     *      *     *     |             *\n"
     << "*********************************************************\n"
     << "---------------------------------------------------------\n";
}
void displayOrderMessage( const std::vector<CakeDetails>& cakes  ) {
    std::cout << "         Would you like to place an order? yes/no: ";
    std::string s;
    std::cin >> s;

    if (s == "yes") {
        clearScreen();
        std::cout<<"*********************************************************\n"
                << "Thank you for taking an intereset in Sweet Spell Bakery ! \n We make cakes out of love and passion\n"
                << "*********************************************************\n\n"
                << "Our current cake collection is:\n\n"
                << "*********************************************************\n"
                << "\n"
                << "  1. Chocolate Birthday Monster\n"
                << "  2. Vanilla Birthday Lover\n"
                << "  3. Vanilla Wedding Dream\n"
                << "  4. Carrot Cake\n"
                << "  5. Classic Cheesecake Sugar&Gluten Free\n"
                << "  6. Forest Fruit Cheesecake Sugar Free\n"
                << "  7. Lemon Graduation Cake Sugar&Gluten Free\n"
                << "  8. Congratulation Special: Red Velvet\n\n"
                << "*********************************************************\n"
                <<"\n"
                << "Which one would you like to know more about? (choose just the number <3): ";

        int order_temp = 0;
        std::cin >> order_temp;

        if (order_temp >= 1 && order_temp <= 8) {
           std::cout<< "\nAmazing choice! It's one of our top sellers!\n\n";
            cakes[order_temp - 1].displaySummary();
        } else {
            std::cout << "Invalid selection. Please enter a number between 1 and 8.\n";
        }

        std::cout << "\nThank you for visiting Sweet Spell Bakery!\n";
    } else if (s == "no") {
        std::cout << "\n Sorry to hear that but thank you for visiting Sweet Spell Bakery! See you soon! <3\n";
    }
}

void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
}

int main() {
     displayWelcomeMessage();

     std::this_thread::sleep_for(std::chrono::seconds(3));

     clearScreen();

     Ornament ornm1("Mrs&Mr Figurine", 0.3f, 100);
     Ornament ornm2("Boy/Girl Figurine", 0.3f, 20 );
     Ornament ornm4("Animated Character Figurine", 0.1f, 30);

     std::vector<Ornament> birthdayOrnaments= { ornm2, ornm4 };
     std::vector<Ornament> weddingOrnaments= { ornm1 };
     std::vector<Ornament> carrotOrnaments= { ornm4 };
     std::vector<Ornament> cheesecakeOrnaments= { ornm4};
     std::vector<Ornament> lemonOrnaments= {ornm2 };
     std::vector<Ornament> redVelvetOrnaments= {ornm2};

     std::vector<CakeDetails> cakes = {
        CakeDetails("Chocolate Birthday Monster", "Chocolate", "Chocolate Ganache", "Happy Birthday (name and age)!",
            birthdayOrnaments, 1, 5, 2.0f, 100, false, false),
        CakeDetails("Vanilla Birthday Lover", "Vanilla", "Buttercream", "Happy Birthday (name and age)!",
            birthdayOrnaments, 1, 5, 2.0f, 100, false, false),
        CakeDetails("Vanilla Wedding Dream", "Vanilla", "White Chocolate Ganache", "For a lifetime of happiness Mrs&Mr",
            weddingOrnaments, 3, 3, 10.0f, 150, false, false),
        CakeDetails("Carrot Cake", "Carrot", "Cream Cheese", "Don't forget to smile!",
            carrotOrnaments, 1, 6, 1.5f, 80, false, true),
        CakeDetails("Classic Cheesecake Sugar&Gluten Free", "Biscuit Base", "Cream Cheese", "Have a beautiful day",
            cheesecakeOrnaments, 1, 5, 1.5f, 80, true, true),
        CakeDetails("Forest Fruit Cheesecake Sugar Free", "Biscuit Base", "Cream Cheese", "Have a beautiful day",
            cheesecakeOrnaments, 1, 5, 1.5f, 90, true, false),
        CakeDetails("Lemon Graduation Cake Sugar&Gluten free", "Vanilla with Lemon", "Lemon Frosting", "Happy Graduation!",
            lemonOrnaments, 1, 4, 2.0f, 90, true, true),
        CakeDetails("Congratulation Special: Red Velvet", "Red Velvet", "Cream Cheese", "Congratulations!",
            redVelvetOrnaments, 2, 5, 3.0f, 130, false, false)
    };

    displayOrderMessage( cakes );

    return 0;
}
