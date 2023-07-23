#include <iostream>
#include <string>
#include <map>

class Miner {
public:
    std::string address;
    double balance;

    Miner(std::string address) : address(address), balance(0.0) {}

    void receiveReward(double amount) {
        balance += amount;
    }
};

class Block {
public:
    std::string minerAddress;

    Block(std::string minerAddress) : minerAddress(minerAddress) {}
};

class Blockchain {
public:
    std::vector<Block> chain;
    std::map<std::string, Miner> miners;
    double blockReward;

    Blockchain(double blockReward) : blockReward(blockReward) {}

    void addMiner(Miner miner) {
        miners[miner.address] = miner;
    }

    void addBlock(Block block) {
        chain.push_back(block);
        miners[block.minerAddress].receiveReward(blockReward);
    }
};

int main() {
    Blockchain blockchain(50.0);

    Miner miner("MinerAddress");
    blockchain.addMiner(miner);

    Block block("MinerAddress");
    blockchain.addBlock(block);

    std::cout << "Block has been mined and miner has received reward!" << std::endl;
    std::cout << "Miner balance: " << blockchain.miners["MinerAddress"].balance << std::endl;

    return 0;
}
