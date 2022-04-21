add_executable(sha3 sha3.cpp)
target_link_libraries(sha3 cryptopp)

add_executable(hmac hmac_sha3.cpp ../include/toolkit.h)
target_link_libraries(hmac cryptopp)

add_executable(rsa rsa.cpp)
target_link_libraries(rsa cryptopp)

add_executable(post PoSt.cpp)
target_link_libraries(post cryptopp)