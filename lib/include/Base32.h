#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_BASE32_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_BASE32_H

#include <VS3Common.h>
#include <vector>

namespace VS3 {
	namespace CodeFactory {
		namespace Cryptography {
			class Base32
			{
			public:
				static std::string ToBase32(std::vector<uint8_t> data);
				static std::vector<uint8_t> FromBase32(std::string& data);
			};
		}
	}
}

#endif // VS3_CODEFACTORY_CRYPTOGRAPHY_BASE32_H