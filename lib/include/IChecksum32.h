#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_ICHECKSUM32_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_ICHECKSUM32_H

#include <VS3Common.h>
#include <vector>

namespace VS3 {
	namespace CodeFactory {
		namespace Cryptography {
			namespace Checksum {
				class IChecksum32
				{
				public:
					virtual uint32_t Compute(std::vector<uint8_t>* data) = 0;
					virtual uint32_t Compute(std::vector<uint8_t>& data) = 0;
					virtual ~IChecksum32() {};
				};
			}
		}
	}
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_ICHECKSUM32_H