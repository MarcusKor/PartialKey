#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_CRC32_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_CRC32_H

#include <VS3Common.h>
#include <IChecksum32.h>
#include <IHash.h>

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            namespace Hash {
                class Crc32 : public Checksum::IChecksum32, public Hash::IHash
                {
                public:
                    virtual uint32_t Compute(std::vector<uint8_t>* data);
                    virtual uint32_t Compute(std::vector<uint8_t>& data);
                    static uint32_t Reflect(uint32_t data, uint8_t numberOfBits);
                    static std::vector<uint32_t> CreateCrcTable();

                    Crc32();

                private:
                    static std::vector<uint32_t> crcTable;
                };
            }
        }
    }
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_CRC32_H