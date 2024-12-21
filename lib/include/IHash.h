#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_IHASH_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_IHASH_H

#include <VS3Common.h>
#include <vector>

namespace VS3 {
	namespace CodeFactory {
		namespace Cryptography {
			namespace Hash {
				class IHash
				{
				public:
					virtual uint32_t Compute(std::vector<uint8_t>* data) = 0;
					virtual uint32_t Compute(std::vector<uint8_t>& data) = 0;
					virtual ~IHash() {};
				};
			}
		}
	}
}

#endif	// VS3_CODEFACTORY_CRYPTOGRAPHY_HASH_IHASH_H
