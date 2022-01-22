//
// Created by qyxie on 16/1/2022.
//
#include<cryptopp/rsa.h>
#include<cryptopp/osrng.h>
#include<cryptopp/hex.h>
#include<cryptopp/hmac.h>
#include<cryptopp/sha3.h>
#include<cryptopp/modarith.h>
#include<cryptopp/files.h>
#include<time.h>
#include<iostream>
#include<vector>
#include <sstream>

std::string sha3_256(std::string msg){
    std::string digest;
    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));

    CryptoPP::SHA3_256 hash;
    hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);

    CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));
    return digest;
}

std::string hmac_sha3(std::string key, std::string msg){
    std::string mac, encoded;
    CryptoPP::SecByteBlock key_hmac(reinterpret_cast<const CryptoPP::byte*>(&key[0]), key.size());
    try
    {
        CryptoPP::HMAC<CryptoPP::SHA3_256> hmac(key_hmac, key_hmac.size());

        CryptoPP::StringSource ss2(msg, true,
                         new CryptoPP::HashFilter(hmac,
                                        new CryptoPP::StringSink(mac)
                         ) // HashFilter
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    encoded.clear();
    CryptoPP::StringSource ss3(mac, true,
                     new CryptoPP::HexEncoder(
                             new CryptoPP::StringSink(encoded)
                     ) // HexEncoder
    ); // StringSource
    return encoded;
}

std::pair<CryptoPP::Integer, CryptoPP::Integer> setup(int n_bits){
    CryptoPP::AutoSeededRandomPool rng;

    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, n_bits);

    const CryptoPP::Integer& p = params.GetPrime1();
    const CryptoPP::Integer& q = params.GetPrime2();

    return std::make_pair(p, q);
}

void PoR_setup(std::string PoR_sk[], int n){
    for(int i = 0; i < n; i++){
        CryptoPP::AutoSeededRandomPool prng;
        CryptoPP::SecByteBlock key(16);
        prng.GenerateBlock(key, key.size());

        std::string s;
        CryptoPP::HexEncoder hex(new CryptoPP::StringSink(s));
        hex.Put(key, key.size());
        hex.MessageEnd();

        PoR_sk[i] = s;
    }
}

std::pair<CryptoPP::Integer, CryptoPP::Integer> TDF_setup(CryptoPP::Integer p, CryptoPP::Integer q){
    CryptoPP::Integer pk = p * q;
    CryptoPP::Integer one(1);
    CryptoPP::Integer sk = (p - one) * (q - one);
    return std::make_pair(pk,sk);
}

CryptoPP::Integer TDF_TrapEval(std::string msg, int t, CryptoPP::Integer pk, CryptoPP::Integer sk){
    CryptoPP::Integer e(1 << t);
    e = e % sk;
    CryptoPP::Integer x(msg.c_str());
    CryptoPP::ModularArithmetic ma(pk);
    return ma.Exponentiate(x, e);
}

CryptoPP::Integer TDF_Eval(std::string msg, int t, CryptoPP::Integer pk){
    CryptoPP::Integer g(msg.c_str());
    for(int i = 0; i < (1 << t); i++){
        g = (g * g) % pk;
    }
    return g;
}


// TODO Store
std::pair<std::vector<std::string>, std::vector<std::string>> store(std::string Por_sk[], std::string file, CryptoPP::Integer pk, CryptoPP::Integer sk, int post_k, int por_l){

    std::vector<std::string> challenge_set;
    std::vector<std::string> verify_set;
    challenge_set.clear();
    verify_set.clear();

    for(int i = 0; i < por_l; i++){
        std::string challenge = Por_sk[i];
        for(int j = 0; j < post_k; j++){
            std::string verify = hmac_sha3(challenge, file);
            verify_set.emplace_back(verify);
            std::string u = sha3_256(verify);

            CryptoPP::Integer d_value = TDF_TrapEval(u, post_k, pk, sk);
            std::stringstream ss;
            ss << std::hex  << d_value;
            std::string d = ss.str();

            challenge = sha3_256(d);
        }
        challenge_set.emplace_back(challenge);
    }
    return std::make_pair(challenge_set, verify_set);
}

// TODO Verification
void prove(){

}

int main (int argc, char* argv[])
{
    const int n_bits = 1024;
    const int PoR_n = 32;

    std::string PoR_sk[PoR_n] = {""};
    PoR_setup(PoR_sk, PoR_n);

    auto pq = setup(n_bits);
    const CryptoPP::Integer p = pq.first;
    const CryptoPP::Integer q = pq.second;

//    std::cout << "PoR_sk[0]: " << PoR_sk[0] << std::endl;

//    std::cout << "p: " << p << std::endl;
//    std::cout << "q: " << q << std::endl;

    // Test of sha3_256
//    std::string msg = "Yoda said, Do or do not. There is no try.";
//    std::string dig = sha3_256(msg);
//    std::cout << dig << std::endl;

    // Test of hmac with sha3_256
//    std::string msg = "Yoda said, Do or do not. There is no try.";
//    std::string cipher = hmac_sha3(PoR_sk[0], msg);
//    std::cout << cipher << std::endl;

    auto keys = TDF_setup(p, q);
    const CryptoPP::Integer pk = keys.first;
    const CryptoPP::Integer sk = keys.second;

    // Test of Trapdoor delay function implementation
//    std::string msg = "Yoda said, Do or do not. There is no try.";
//    clock_t trap_start = clock();
//    CryptoPP::Integer trap_re = TDF_TrapEval(msg, 720 , pk, sk);
//    clock_t trap_finish = clock();
//    std::cout << "Trapdoor evaluation Time: " << (trap_finish - trap_start) << "s." << std::endl;
//    clock_t eval_start = clock();
//    CryptoPP::Integer re = TDF_Eval(msg, 720, pk);
//    clock_t eval_finish = clock();
//    std::cout << "Evaluation Time: " << (eval_finish - eval_start) << "s." << std::endl;
//    if(trap_re == re){
//        std::cout << "Evaluation Success." << std::endl;
//    }
    return 0;
}