#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_PARTIALKEY_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_PARTIALKEY_H

#include <VS3Common.h>
#include <IChecksum16.h>
#include <IHash.h>
#include <memory>
#include <vector>
#include <map>

#pragma warning (disable: 4365 4810 4820 4514 4625 4626 5045)
#pragma pack(show)

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            class PartialKey
            {
            public:
                enum ChecksumMode
                {
                    Adler16,
                    Crc16,
                    CrcCcitt
                };

                enum HashMode
                {
                    Fnv1A,
                    Jenkins06,
                    Jenkins96,
                    OneAtATime,
                    SuperFast,
                    Crc32,
                    GeneralizedCrc
                };

                std::string Generate(uint32_t seed);
                std::string Generate(std::string& seed);
                std::map<uint32_t, std::string> Generate(uint32_t numberOfKeys, uint32_t randomSeed);
                bool ValidateKey(ChecksumMode checksumMode, HashMode hashMode, std::string& key, int32_t subkeyIndex, uint32_t subkeyBase, uint32_t seedOfJenkins06 = 0);
                bool ValidateKey(ChecksumMode checksumMode, HashMode hashMode, std::string& key, int32_t subkeyIndex, uint32_t subkeyBase, std::string& seedString, uint32_t seedOfJenkins06 = 0);
                bool ValidateKey(ChecksumMode checksumMode, HashMode hashMode, std::vector<uint8_t>& key, uint32_t seed, int32_t subkeyIndex, uint32_t subkeyBase, std::string& seedString, uint32_t seedOfJenkins06 = 0);
                bool ValidateChecksum(ChecksumMode checksumMode, std::vector<uint8_t>& key);
                bool ValidateKey(Checksum::IChecksum16* checksum, Hash::IHash* hash, std::vector<uint8_t>& key, uint32_t seed, int32_t subkeyIndex, uint32_t subkeyBase);
                bool ValidateChecksum(Checksum::IChecksum16* checksum, std::vector<uint8_t>& key);
                uint32_t GetSerialNumberFromKey(std::string& key);
                uint32_t GetSerialNumberFromSeed(std::string& seed, HashMode hashMode = HashMode::Fnv1A, uint32_t seedOfJenkins06 = 0);
                std::vector<uint8_t> GetKeyBytes(std::string& key);
                void SetSpacing(uint8_t spacing = 0) { m_spacing = spacing; }

                PartialKey(ChecksumMode checksumMode, HashMode hashMode, std::vector<uint32_t>& baseKeys, uint8_t spacing = 0, uint32_t seedOfJenkins06 = 0);
                PartialKey(Checksum::IChecksum16* checksum, Hash::IHash* hash, std::vector<uint32_t>& baseKeys);
                PartialKey(Checksum::IChecksum16* checksum, std::vector<Hash::IHash*> hashFunctions, std::vector<uint32_t>& baseKeys);
                PartialKey(Checksum::IChecksum16* checksum, std::vector<Hash::IHash*>* hashFunctions, std::vector<uint32_t>* baseKeys);                

            private:
                uint8_t m_spacing;
                std::vector<uint32_t>  m_baseKeys;
                std::unique_ptr<Checksum::IChecksum16> m_checksum;
                std::vector<std::shared_ptr<Hash::IHash>> m_hashFunctions;
            };
        }
    }
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_PARTIALKEY_H