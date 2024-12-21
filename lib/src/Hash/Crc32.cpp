#include <Crc32.h>
#include <algorithm>

std::vector<uint32_t> VS3::CodeFactory::Cryptography::Hash::Crc32::crcTable;

uint32_t VS3::CodeFactory::Cryptography::Hash::Crc32::Compute(std::vector<uint8_t>* data)
{
    if (data == nullptr)
        throw std::invalid_argument("The argument data is null.");
    return Compute(*data);
}

uint32_t VS3::CodeFactory::Cryptography::Hash::Crc32::Compute(std::vector<uint8_t>& data)
{
    if (data.empty())
        throw std::invalid_argument("The argument data is null.");

    uint32_t result = 0xFFFFFFFF;

    // Divide the message by the polynomial, a byte at a time.
    std::for_each(data.cbegin(), data.cend(), [&](const uint8_t n)
        {
            uint32_t index = (uint8_t)(Reflect(n, 8) ^ (result >> 24));
            result = crcTable[index] ^ (result << 8);
        });

    return Reflect(result, 32) ^ 0xFFFFFFFF;
}

uint32_t VS3::CodeFactory::Cryptography::Hash::Crc32::Reflect(uint32_t data, uint8_t numberOfBits)
{
    uint32_t result = 0;

    // Reflect the data about the center bit.
    for (uint8_t bit = 0; bit < numberOfBits; ++bit)
    {
        // If the LSB bit is set, set the reflection of it.
        if ((data & 0x01) != 0)
            result |= (uint32_t)(1 << ((numberOfBits - 1) - bit));

        data = (data >> 1);
    }

    return result;
}

std::vector<uint32_t> VS3::CodeFactory::Cryptography::Hash::Crc32::CreateCrcTable()
{
    std::vector<uint32_t> result(256);
    const uint32_t topbit = ((uint32_t)1 << 31);

    // Compute the remainder of each possible dividend.
    for (size_t i = 0; i < 256; ++i)
    {
        // Start with the dividend followed by zeros.
        uint32_t value = (uint32_t)i << 24;

        // Perform modulo-2 division, a bit at a time.
        for (uint8_t bit = 8; bit > 0; --bit)
        {
            // Try to divide the current data bit.
            if ((value & topbit) != 0)
                value = (value << 1) ^ 0x04C11DB7;
            else
                value = value << 1;
        }

        // Store the result into the table.
        result[i] = value;
    }

    return result;
}

VS3::CodeFactory::Cryptography::Hash::Crc32::Crc32()
{
    if (crcTable.empty())
    {
        std::unique_ptr<std::vector<uint32_t>> table = std::make_unique<std::vector<uint32_t>>(VS3::CodeFactory::Cryptography::Hash::Crc32::CreateCrcTable());
        crcTable.assign(table.get()->begin(), table.get()->end());
    }
}