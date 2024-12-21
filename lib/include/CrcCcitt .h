#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_CRCCCITT_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_CRCCCITT_H

#include <VS3Common.h>
#include <IChecksum16.h>

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            namespace Checksum {
                class CrcCcitt : public IChecksum16
                {
                public:
                    virtual uint16_t Compute(std::vector<uint8_t>* data);
                    virtual uint16_t Compute(std::vector<uint8_t>& data);
                    static std::vector<uint16_t> CreateCrcTable();

                private:
                    static std::vector<uint16_t> crcTable;
                };
            }
        }
    }
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_CRCCCITT_H
