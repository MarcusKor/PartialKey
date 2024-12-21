#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_FNV1A_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_FNV1A_H

#include <VS3Common.h>
#include <IHash.h>
#include <IChecksum32.h>

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            namespace Hash {
                class Fnv1A : public IHash
                {
                public:
                    virtual uint32_t Compute(std::vector<uint8_t>* data);
                    virtual uint32_t Compute(std::vector<uint8_t>& data);
                };
            }
        }
    }
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_FNV1A_H