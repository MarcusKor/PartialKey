#include <Adler16 .h>

#pragma warning(disable: 5045)

uint16_t VS3::CodeFactory::Cryptography::Checksum::Adler16::Compute(std::vector<uint8_t>* data)
{
    if (data == nullptr)
        throw std::invalid_argument("The argument data is null.");
    return Compute(*data);
}

uint16_t VS3::CodeFactory::Cryptography::Checksum::Adler16::Compute(std::vector<uint8_t>& data)
{
	if (data.empty())
		throw std::invalid_argument("The argument data is null.");

    uint32_t a = 1, b = 0;
    uint32_t i = 0, len = ToUint32(data.size());

    while (len > 0)
    {
        uint32_t tlen = len < 5550 ? len : 5550;
        len -= tlen;

        do
        {
            a += data[i++];
            b += a;
        } while (--tlen > 0);

        a %= 251;
        b %= 251;
    }

    return (uint16_t)((b << 8) | a);
}
