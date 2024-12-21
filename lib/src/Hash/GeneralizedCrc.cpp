#include <GeneralizedCrc.h>
#include <algorithm>

#pragma warning(disable: 5045)

std::vector<uint32_t> VS3::CodeFactory::Cryptography::Hash::GeneralizedCrc::crcTable =
	VS3::CodeFactory::Cryptography::Hash::GeneralizedCrc::CreateCrcTable();

uint32_t VS3::CodeFactory::Cryptography::Hash::GeneralizedCrc::Compute(std::vector<uint8_t>* data)
{
    if (data == nullptr)
        throw std::invalid_argument("The argument data is null.");
    return Compute(*data);
}

uint32_t VS3::CodeFactory::Cryptography::Hash::GeneralizedCrc::Compute(std::vector<uint8_t>& data)
{
    if (data.empty())
        throw std::invalid_argument("The argument data is null.");

    uint32_t len = ToUint32(data.size()), result = ToUint32(len);

    for (uint32_t i = 0; i < len; ++i)
        result = (result >> 8) ^ crcTable[(result & 0xff) ^ static_cast<uint32_t>(data[i])];

    return result;
}

std::vector<uint32_t> VS3::CodeFactory::Cryptography::Hash::GeneralizedCrc::CreateCrcTable()
{
    std::vector<uint32_t> table(256);

    // Fill table with random permutations of 0..255 in each byte
    for (size_t i = 0; i < 256; i++)
    {
        uint8_t x = (uint8_t)i;
        
        for (size_t j = 0; j < 5; ++j)
        {
            x += 1;
            x += (uint8_t)(x << 1);
            x ^= (uint8_t)(x >> 1);
        }

        table[i] = x;

        for (uint8_t j = 0; j < 5; ++j)
        {
            x += 2;
            x += (uint8_t)(x << 1);
            x ^= (uint8_t)(x >> 1);
        }

        table[i] ^= (uint8_t)(x << 8);

        for (uint8_t j = 0; j < 5; ++j)
        {
            x += 3;
            x += (uint8_t)(x << 1);
            x ^= (uint8_t)(x >> 1);
        }

        table[i] ^= ((uint8_t)x << 16);

        for (uint8_t j = 0; j < 5; ++j)
        {
            x += 4;
            x += (uint8_t)(x << 1);
            x ^= (uint8_t)(x >> 1);
        }

        table[i] ^= (uint8_t)(x << 24);
    }

    return table;
}
