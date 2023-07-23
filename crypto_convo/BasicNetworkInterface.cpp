#include <iostream>
#include <string>
#include <vector>

class Transaction {
public:
    std::string from;
    std::string to;
    double amount;

    Transaction(std::string from, std::string to, double amount) : from(from), to(to), amount(amount) {}
};

class Block {
public:
    std::vector<Transaction> transactions;

    void addTransaction(Transaction transaction) {
        transactions.push_back(transaction);
    }
};

class NetworkInterface {
public:
    void broadcastTransaction(Transaction transaction) {
        // Here you would typically send the transaction to the network
        std::cout << "Broadcasting transaction from " << transaction.from << " to " << transaction.to << " of amount " << transaction.amount << std::endl;
    }

    Block getLatestBlock() {
        // Here you would typically retrieve the latest block from the network
        return Block();
    }
};

int main() {
    NetworkInterface networkInterface;

    Transaction transaction("Alice", "Bob", 1.0);
    networkInterface.broadcastTransaction(transaction);

    Block latestBlock = networkInterface.getLatestBlock();
    std::cout << "Retrieved latest block with " << latestBlock.transactions.size() << " transactions" << std::endl;

    return 0;
}
