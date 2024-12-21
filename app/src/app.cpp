// app.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "app.h"
#include <Adler16 .h>
#include <Fnv1A.h>
#include <PartialKey.h>
#include <vector>
#include <ctime>
#include <cassert>

#pragma warning (disable: 4242 4365 4810 4820 4514 5045)
using namespace std;
using namespace VS3::CodeFactory::Cryptography;

int main()
{
    srand(static_cast<uint32_t>(time(nullptr)));

    std::vector<uint32_t> baseKeys = 
    {
        static_cast<uint32_t>(rand()),
        static_cast<uint32_t>(rand()),
        static_cast<uint32_t>(rand()),
        static_cast<uint32_t>(rand()),
        static_cast<uint32_t>(rand()),
        static_cast<uint32_t>(rand()),        
    };

    std::shared_ptr<PartialKey> pk = std::make_shared<PartialKey>(PartialKey(PartialKey::ChecksumMode::Adler16, PartialKey::HashMode::Fnv1A, baseKeys));
    pk->SetSpacing(6);
    
    uint32_t seedNumber = static_cast<uint32_t>(rand());
    std::string keyNumber = pk->Generate(seedNumber);

    for (int32_t j = 0; j < static_cast<int32_t>(baseKeys.size()); j++)
        assert(pk->ValidateKey(PartialKey::ChecksumMode::Adler16, PartialKey::HashMode::Fnv1A, keyNumber, j, baseKeys[j]));

    std::cout << "key=" << keyNumber << std::endl;
    std::cout << "key_serial=" << pk->GetSerialNumberFromKey(keyNumber) << std::endl << std::endl;

    std::string seedString = "owner@email.com";
    std::string KeyString = pk->Generate(seedString);

    for (int32_t j = 0; j < static_cast<int32_t>(baseKeys.size()); j++)
        assert(pk->ValidateKey(PartialKey::ChecksumMode::Adler16, PartialKey::HashMode::Fnv1A, KeyString, j, baseKeys[j], seedString));
        
    std::cout << "key=" << KeyString.c_str() << std::endl;
    std::cout << "key_serial=" << pk->GetSerialNumberFromKey(KeyString) << std::endl;
    std::cout << "seed_serial=" << pk->GetSerialNumberFromSeed(seedString) << std::endl;

	return 0;
}
