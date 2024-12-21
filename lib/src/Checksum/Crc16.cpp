#include <Crc16.h>
#include <algorithm>
#pragma warning(disable: 5045)

std::vector<uint16_t> VS3::CodeFactory::Cryptography::Checksum::Crc16::crcTable;

uint16_t VS3::CodeFactory::Cryptography::Checksum::Crc16::Compute(std::vector<uint8_t>* data)
{
    if (data == nullptr)
        throw std::invalid_argument("The argument data is null.");
    return Compute(*data);
}

uint16_t VS3::CodeFactory::Cryptography::Checksum::Crc16::Compute(std::vector<uint8_t>& data)
{
    if (data.empty())
        throw std::invalid_argument("The argument data is null.");

    uint16_t result = 0;

    // Divide the message by the polynomial, a byte at a time.
    std::for_each(data.cbegin(), data.cend(), [&](const uint8_t n)
        {
            uint32_t i = (uint32_t)Reflect(n, 8) ^ (result >> 8);
            result = static_cast<uint16_t>((crcTable[i]) ^ (result << 8));
        });

    return (uint16_t)Reflect(result, 16);
}

uint32_t VS3::CodeFactory::Cryptography::Checksum::Crc16::Reflect(uint32_t data, uint8_t numberOfBits)
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

std::vector<uint16_t> VS3::CodeFactory::Cryptography::Checksum::Crc16::CreateCrcTable()
{
    std::vector<uint16_t> result(256);
    const uint16_t topbit = 1 << 15;

    // Compute the remainder of each possible dividend.
    for (uint32_t i = 0; i < 256; ++i)
    {
        // Start with the dividend followed by zeros.
        uint16_t value = (uint16_t)(i << 8);

        // Perform modulo-2 division, a bit at a time.
        for (uint8_t bit = 8; bit > 0; --bit)
        {
            // Try to divide the current data bit.
            if ((value & topbit) != 0)
                value = (uint16_t)((value << 1) ^ 0x8005);
            else
                value = (uint16_t)(value << 1);
        }

        // Store the result into the table.
        result[i] = value;
    }

    return result;
}

VS3::CodeFactory::Cryptography::Checksum::Crc16::Crc16()
{
    if (crcTable.empty())
    {
        std::unique_ptr<std::vector<uint16_t>> table = std::make_unique<std::vector<uint16_t>>(VS3::CodeFactory::Cryptography::Checksum::Crc16::CreateCrcTable());
        crcTable.assign(table.get()->begin(), table.get()->end());
    }
}
