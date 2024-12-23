﻿// app.cpp : 애플리케이션의 진입점을 정의합니다.
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
    for (int i = 0; i < 100; i++)
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

        std::shared_ptr<PartialKey> pk = std::make_shared<PartialKey>(PartialKey(PartialKey::ChecksumMode::Crc16, PartialKey::HashMode::SuperFast, baseKeys, 6));

        uint32_t seedNumber = static_cast<uint32_t>(rand());
        std::string keyNumber = pk->Generate(seedNumber);

        std::cout << "key=" << keyNumber << std::endl;
        std::cout << "key_serial=" << pk->GetSerialNumberFromKey(keyNumber) << std::endl << std::endl;

        for (int32_t j = 0; j < static_cast<int32_t>(baseKeys.size()); j++)
            assert(pk->ValidateKey(PartialKey::ChecksumMode::Crc16, PartialKey::HashMode::SuperFast, keyNumber, j, baseKeys[j]));

        std::string seedString = "owner@email.com";
        std::string KeyString = pk->Generate(seedString, PartialKey::HashMode::SuperFast);

        std::cout << "key=" << KeyString.c_str() << std::endl;
        std::cout << "key_serial=" << pk->GetSerialNumberFromKey(KeyString) << std::endl;
        std::cout << "seed_serial=" << pk->GetSerialNumberFromSeed(seedString, PartialKey::HashMode::SuperFast) << std::endl << std::endl;

        for (int32_t j = 0; j < static_cast<int32_t>(baseKeys.size()); j++)
            assert(pk->ValidateKey(PartialKey::ChecksumMode::Crc16, PartialKey::HashMode::SuperFast, KeyString, j, baseKeys[j], seedString));
    }

	return 0;
}
