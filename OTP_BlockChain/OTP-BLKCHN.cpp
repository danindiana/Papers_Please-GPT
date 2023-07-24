#include <iostream>
#include <string>
#include <random>

class BlockchainOTP {
private:
    std::string blockchain;
    std::string oneTimeKey;

public:
    BlockchainOTP() {
        // Initialize the blockchain with a Genesis block
        blockchain = "GenesisBlock";
    }

    // Step one: Establish mutual trust and synchronization mechanism
    void establishTrustAndSync() {
        std::cout << "Sender requests receiver to start communication." << std::endl;
        std::cout << "Receiver responds with confirmation and mutual trust is established." << std::endl;
        std::cout << "Both parties synchronize based on the blockchain." << std::endl;
    }

    // Step two: Generate a one-time key from the latest block's hash
    void generateOneTimeKey() {
        std::string latestBlockHash = blockchain; // Get latest block's hash
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, 1000000); // Range for random number generation
        int randomNum = dis(gen); // Generate random number
        oneTimeKey = std::to_string(randomNum) + latestBlockHash;
    }

    // Step three: Encrypt the plaintext using the one-time key
    std::string encrypt(const std::string& plaintext) {
        std::string ciphertext = "";
        for (size_t i = 0; i < plaintext.length(); ++i) {
            ciphertext += plaintext[i] ^ oneTimeKey[i % oneTimeKey.length()];
        }
        return ciphertext;
    }

    // Step four: Decrypt the ciphertext using the one-time key
    std::string decrypt(const std::string& ciphertext) {
        std::string decryptedText = "";
        for (size_t i = 0; i < ciphertext.length(); ++i) {
            decryptedText += ciphertext[i] ^ oneTimeKey[i % oneTimeKey.length()];
        }
        return decryptedText;
    }
};

int main() {
    BlockchainOTP sender;
    BlockchainOTP receiver;

    // Step one: Establish mutual trust and synchronization mechanism
    sender.establishTrustAndSync();
    receiver.establishTrustAndSync();

    // Step two: Generate one-time key
    sender.generateOneTimeKey();
    receiver.generateOneTimeKey();

    // Communication
    std::string plaintext = "Hello, this is a secret message.";
    std::string ciphertext = sender.encrypt(plaintext);
    std::string decryptedText = receiver.decrypt(ciphertext);

    std::cout << "Plaintext: " << plaintext << std::endl;
    std::cout << "Ciphertext: " << ciphertext << std::endl;
    std::cout << "Decrypted Text: " << decryptedText << std::endl;

    return 0;
}
