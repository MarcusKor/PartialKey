#include <SuperFast.h>

uint32_t VS3::CodeFactory::Cryptography::Hash::SuperFast::Compute(std::vector<uint8_t>* bytes)
{
	if (bytes == nullptr)
		throw std::invalid_argument("The argument data is null.");
	return Compute(*bytes);
}

uint32_t VS3::CodeFactory::Cryptography::Hash::SuperFast::Compute(std::vector<uint8_t>& bytes)
{
	if (bytes.empty())
		throw std::invalid_argument("The argument data is null.");

    size_t len = bytes.size(), rem = len & 3;
    uint32_t i = 0, result = ToUint32(len);
    len >>= 2;

    // Main loop
    for (; len > 0; len--)
    {
        result += *reinterpret_cast<uint16_t*>(bytes.data() + i);
        i += 2;
        uint16_t next = *reinterpret_cast<uint16_t*>(bytes.data() + i);
        i += 2;
        uint32_t tmp = (uint32_t)(next << 11) ^ result;
        result = (result << 16) ^ tmp;
        result += result >> 11;
    }

    // Handle end cases
    switch (rem)
    {
    case 3:
        {
            result += *reinterpret_cast<uint16_t*>(bytes.data() + i);
            i += 2;
            result ^= result << 16;
            result ^= (uint32_t)(bytes[i] << 18);
            result += result >> 11;
        }
        break;
    case 2:
        {
            result += *reinterpret_cast<uint16_t*>(bytes.data() + i);
            result ^= result << 11;
            result += result >> 17;
        }
        break;
    case 1:
        {
            result += bytes[i];
            result ^= result << 10;
            result += result >> 1;
        }
        break;
    }

    // Force "avalanching" of final 127 bits
    result ^= result << 3;
    result += result >> 5;
    result ^= result << 4;
    result += result >> 17;
    result ^= result << 25;
    result += result >> 6;
    return result;
}
