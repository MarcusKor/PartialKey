#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_CRC16_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_CRC16_H

#include <VS3Common.h>
#include <IChecksum16.h>

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            namespace Checksum {
                class Crc16 : public IChecksum16
                {
                public:
                    virtual uint16_t Compute(std::vector<uint8_t>* data);
                    virtual uint16_t Compute(std::vector<uint8_t>& data);                        
                    static uint32_t Reflect(uint32_t data, uint8_t numberOfBits);
                    static std::vector<uint16_t> CreateCrcTable();

                    Crc16();

                private:
                    static std::vector<uint16_t> crcTable;
                };
            }
        }
    }
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_CRC16_H
