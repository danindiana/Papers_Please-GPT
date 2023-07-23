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

    Blockchain(int difficulty) : difficulty(difficulty) {
        chain.push_back(createGenesisBlock());
    }

    Block createGenesisBlock() {
        std::vector<Transaction> transactions;
        return Block(transactions, "0");
    }

    void addBlock(Block block) {
        block.mineBlock(difficulty);
        chain.push_back(block);
    }
};

int main() {
    Blockchain blockchain(2);

    std::vector<Transaction> transactions;
    transactions.push_back(Transaction("Alice", "Bob", 1.0));
    Block block(transactions, blockchain.chain.back().hash);
    blockchain.addBlock(block);

    std::cout << "Block has been mined and added to the blockchain!" << std::endl;

    return 0;
}
