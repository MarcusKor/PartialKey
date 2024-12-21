#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_ADLER16_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_ADLER16_H

#include <VS3Common.h>
#include <IChecksum16.h>

namespace VS3 {
	namespace CodeFactory {
		namespace Cryptography {
			namespace Checksum {
				class Adler16 : public IChecksum16
				{
				public:
					virtual uint16_t Compute(std::vector<uint8_t>* data);
					virtual uint16_t Compute(std::vector<uint8_t>& data);
				};
			}
		}
	}
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_CHECKSUM_ADLER16_H
