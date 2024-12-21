#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_GENERALIZEDCRC_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_GENERALIZEDCRC_H

#include <VS3Common.h>
#include <IHash.h>

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            namespace Hash {
                class GeneralizedCrc : public Hash::IHash
                {
                public:
                    virtual uint32_t Compute(std::vector<uint8_t>* data);
                    virtual uint32_t Compute(std::vector<uint8_t>& data);
                    static std::vector<uint32_t> CreateCrcTable();

                private:
                    static std::vector<uint32_t> crcTable;
                };
            }
        }
    }
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_GENERALIZEDCRC_H