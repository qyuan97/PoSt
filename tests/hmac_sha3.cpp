//
// Created by qyxie on 16/1/2022.
//
#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha3.h>
#include <cryptopp/hmac.h>
#include <cryptopp/osrng.h>
using namespace CryptoPP;

#include <string>
#include <iostream>

int main (int argc, char* argv[]) {
    using namespace CryptoPP;
    AutoSeededRandomPool prng;

    SecByteBlock key(16);
    prng.GenerateBlock(key, key.size());

    std::string plain = "HMAC Test";
    std::string mac, encoded;

    /*********************************\
    \*********************************/

    // Pretty print key
    encoded.clear();
    StringSource ss1(key, key.size(), true,
                     new HexEncoder(
                             new StringSink(encoded)
                     ) // HexEncoder
    ); // StringSource

    std::cout << "key: " << encoded << std::endl;
    std::cout << "plain text: " << plain << std::endl;

    /*********************************\
    \*********************************/

    try {
        HMAC <SHA3_256> hmac(key, key.size());

        StringSource ss2(plain, true,
                         new HashFilter(hmac, new StringSink(mac)) // HashFilter
        ); // StringSource
    }
    catch (const CryptoPP::Exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    /*********************************\
    \*********************************/

    // Pretty print
    encoded.clear();
    StringSource ss3(mac, true,
                     new HexEncoder(new StringSink(encoded)) // HexEncoder
    ); // StringSource

    std::cout << "hmac: " << encoded << std::endl;


    try
    {
        HMAC<SHA3_256> hmac(key, key.size());
        const int flags = HashVerificationFilter::HASH_AT_END;

        bool result;
        std::string plain_text = "HMAC Test Error";
        StringSource(plain_text + mac, true,
                     new HashVerificationFilter(hmac, new ArraySink((byte*)&result, sizeof(result)), flags)
        ); // StringSource
        if (result == true)
            std::cout << "Verified hash over message" << std::endl;
        else
            std::cout << "Failed to verify hash over message" << std::endl;

    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
