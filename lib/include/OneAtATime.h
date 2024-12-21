#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_ONEATATIME_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_ONEATATIME_H

#include <VS3Common.h>
#include <IHash.h>

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            namespace Hash {
                class OneAtATime : public IHash
                {
                public:
                    virtual uint32_t Compute(std::vector<uint8_t>* data);
                    virtual uint32_t Compute(std::vector<uint8_t>& data);
                };
            }
        }
    }
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_ONEATATIME_H