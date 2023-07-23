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
    std::string previousHash;
    std::string hash;
    int nonce;

    Block(std::vector<Transaction> transactions, std::string previousHash) : transactions(transactions), previousHash(previousHash), nonce(0) {}

    void addTransaction(Transaction transaction) {
        transactions.push_back(transaction);
    }

    std::string calculateHash() {
        // Here you would typically calculate the hash of the block data
        return "Hash";
    }

    void mineBlock(int difficulty) {
        // Here you would typically perform the PoW algorithm until a hash with 'difficulty' leading zeros is found
        hash = calculateHash();
    }
};

class Blockchain {
public:
    std::vector<Block> chain;
    int difficulty;
    double totalSupply;

    Blockchain(int difficulty) : difficulty(difficulty), totalSupply(0.0) {}

    void addBlock(Block block) {
        block.mineBlock(difficulty);
        chain.push_back(block);

        // Update total supply based on transactions in block
        for (Transaction transaction : block.transactions) {
            totalSupply += transaction.amount;
        }
    }

    double getAverageTransactionValue() {
        double totalValue = 0.0;
        int transactionCount = 0;

        for (Block block : chain) {
            for (Transaction transaction : block.transactions) {
                totalValue += transaction.amount;
                transactionCount++;
            }
        }

        return totalValue / transactionCount;
    }
};

int main() {
    Blockchain blockchain(2);

    std::vector<Transaction> transactions;
    transactions.push_back(Transaction("Alice", "Bob", 1.0));
    Block block(transactions, blockchain.chain.back().hash);
    blockchain.addBlock(block);

    std::cout << "Block has been mined and added to the blockchain!" << std::endl;
    std::cout << "Average transaction value: " << blockchain.getAverageTransactionValue() << std::endl;

    return 0;
}
