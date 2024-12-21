#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_JENKINS96_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_JENKINS96_H

#include <VS3Common.h>
#include <IHash.h>

#pragma pack(push, 1) 

namespace VS3 {
    namespace CodeFactory {
        namespace Cryptography {
            namespace Hash {
                class Jenkins96 : public IHash
                {
                public:
                    virtual uint32_t Compute(std::vector<uint8_t>* data);
                    virtual uint32_t Compute(std::vector<uint8_t>& data);

                    Jenkins96();

                private:
                    void Mix();

                    uint32_t m_a, m_b, m_c;
                };
            }
        }
    }
}

#pragma pack(pop)

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_JENKINS96_H