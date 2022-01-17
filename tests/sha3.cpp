#include <cryptopp/cryptlib.h>
#include <cryptopp/sha3.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <iostream>

int main (int argc, char* argv[])
{
    using namespace CryptoPP;

//    SHA3_256 hash;
//    std::cout << "Name: " << hash.AlgorithmName() << std::endl;
//    std::cout << "Digest size: " << hash.DigestSize() << std::endl;
//    std::cout << "Block size: " << hash.BlockSize() << std::endl;

    HexEncoder encoder(new FileSink(std::cout));

    std::string msg = "Yoda said, Do or do not. There is no try.";
    std::string digest;

    SHA3_256 hash;
    hash.Update((const byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((byte*)&digest[0]);

    std::cout << "Message: " << msg << std::endl;

    std::cout << "Digest: ";
    StringSource(digest, true, new Redirector(encoder));
    std::cout << std::endl;

    SHA3_256 hash_verify;
    std::string msg_verify = "test msg";
    hash_verify.Update((const byte*)msg_verify.data(), msg_verify.size());
    bool verified = hash_verify.Verify((const byte*)digest.data());

    if (verified == true)
        std::cout << "Verified hash over message" << std::endl;
    else
        std::cout << "Failed to verify hash over message" << std::endl;

    return 0;
}
