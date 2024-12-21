#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_ICHECKSUM16_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_ICHECKSUM16_H

#include <VS3Common.h>
#include <vector>

namespace VS3 {
	namespace CodeFactory {
		namespace Cryptography {
			namespace Checksum {
				class IChecksum16
				{
				public:
					virtual uint16_t Compute(std::vector<uint8_t>* data) = 0;
					virtual uint16_t Compute(std::vector<uint8_t>& data) = 0;
					virtual ~IChecksum16() {};
				};
			}
		}
	}
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_ICHECKSUM16_H