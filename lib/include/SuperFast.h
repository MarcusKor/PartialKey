#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_SUPERFAST_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_SUPERFAST_H

#include <VS3Common.h>
#include <IHash.h>

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            namespace Hash {
                class SuperFast : public IHash
                {
                public:
                    virtual uint32_t Compute(std::vector<uint8_t>* bytes);
                    virtual uint32_t Compute(std::vector<uint8_t>& bytes);
                };
            }
        }
    }
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_SUPERFAST_H