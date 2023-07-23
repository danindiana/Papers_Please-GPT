#include <iostream>
#include <string>
#include <map>

class Wallet {
private:
    std::string privateKey;
    std::string publicKey;
    std::map<std::string, double> balances;

public:
    Wallet(std::string privateKey, std::string publicKey) : privateKey(privateKey), publicKey(publicKey) {}

    void receiveFunds(std::string token, double amount) {
        balances[token] += amount;
    }

    bool sendFunds(std::string token, double amount) {
        if (balances[token] < amount) {
            return false;
        }
        balances[token] -= amount;
        // Here you would typically create a transaction and broadcast it to the network
        return true;
    }

    double getBalance(std::string token) {
        return balances[token];
    }
};

int main() {
    Wallet myWallet("myPrivateKey", "myPublicKey");

    myWallet.receiveFunds("BTC", 1.0);
    std::cout << "Balance: " << myWallet.getBalance("BTC") << std::endl;

    myWallet.sendFunds("BTC", 0.5);
    std::cout << "Balance: " << myWallet.getBalance("BTC") << std::endl;

    return 0;
}
