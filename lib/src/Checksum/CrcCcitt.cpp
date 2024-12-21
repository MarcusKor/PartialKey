#include <CrcCcitt .h>
#include <algorithm>
#pragma warning(disable: 5045)

std::vector<uint16_t> VS3::CodeFactory::Cryptography::Checksum::CrcCcitt::crcTable = VS3::CodeFactory::Cryptography::Checksum::CrcCcitt::CreateCrcTable();

uint16_t VS3::CodeFactory::Cryptography::Checksum::CrcCcitt::Compute(std::vector<uint8_t>* data)
{
    if (data == nullptr)
        throw std::invalid_argument("The argument data is null.");
    return Compute(*data);
}

uint16_t VS3::CodeFactory::Cryptography::Checksum::CrcCcitt::Compute(std::vector<uint8_t>& data)
{
    if (data.empty())
        throw std::invalid_argument("The argument data is null.");

    uint16_t value = 0xFFFF;

    // Divide the message by the polynomial, a byte at a time.
    std::for_each(data.cbegin(), data.cend(), [&](const uint8_t n)
        {
            uint32_t i = (uint8_t)(n ^ (value >> 8));
            value = (uint16_t)(crcTable[i] ^ (value << 8));
        });

    return value;
}

std::vector<uint16_t> VS3::CodeFactory::Cryptography::Checksum::CrcCcitt::CreateCrcTable()
{
    std::vector<uint16_t> table(256);
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
            {
                value = (uint16_t)((value << 1) ^ 0x1021);
            }
            else
            {
                value = (uint16_t)(value << 1);
            }
        }

        //Store the result into the table.
        table[i] = value;
    }

    return table;
}
