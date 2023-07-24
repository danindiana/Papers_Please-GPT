#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/sha.h>

class ElectronicDevice {
private:
    RSA* firstPair;
    RSA* secondPair;
    std::string deterministicKey;
    
public:
    ElectronicDevice() {
        this->firstPair = RSA_generate_key(<RSA_KEY_SIZE>, RSA_F4, nullptr, nullptr);
        this->deterministicKey = generateDeterministicKey();
    }
    
    std::string getPublicKey() {
        BIO* bio = BIO_new(BIO_s_mem());
        PEM_write_bio_RSAPublicKey(bio, this->firstPair);
        char* pem_key;
        long size = BIO_get_mem_data(bio, &pem_key);
        std::string result(pem_key, size);
        BIO_free(bio);
        return result;
    }
    
    std::string generateDeterministicKey() {
        // Replace with your chosen hash algorithm
        unsigned char hash[<HASH_ALGO>_DIGEST_LENGTH];
        <HASH_ALGO>((unsigned char*)"message", strlen("message"), hash);
        char mdString[<HASH_ALGO>_DIGEST_LENGTH*2+1];
        for(int i = 0; i < <HASH_ALGO>_DIGEST_LENGTH; i++)
             sprintf(&mdString[i*2], "%02x", (unsigned int)hash[i]);
        return std::string(mdString);
    }
    
    void receivePublicKey(std::string pubKey) {
        BIO* bio = BIO_new_mem_buf(pubKey.c_str(), -1);
        this->secondPair = PEM_read_bio_RSAPublicKey(bio, nullptr, nullptr, nullptr);
        BIO_free(bio);
    }
    
    // Here you would implement encryption, decryption and sending of the deterministic key to the key device
};

int main() {
    ElectronicDevice device;
    return 0;
}
