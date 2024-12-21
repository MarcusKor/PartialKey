#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_JENKINS06_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_JENKINS06_H

#include <VS3Common.h>
#include <IHash.h>

#pragma pack(push, 1) 

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            namespace Hash {
                class Jenkins06 : public IHash
                {
                public:
                    virtual uint32_t Compute(std::vector<uint8_t>* data);
                    virtual uint32_t Compute(std::vector<uint8_t>& data);

                    Jenkins06(uint32_t seed);

                private:
                    static uint32_t Rot(uint32_t x, int32_t k);
                    static void Final(uint32_t& a, uint32_t& b, uint32_t& c);
                    static void Mix(uint32_t& a, uint32_t& b, uint32_t& c);

                    uint32_t m_seed;
                };
            }
        }
    }
}

#pragma pack(pop)

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_JENKINS06_H