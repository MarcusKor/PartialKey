#include <OneAtATime.h>

#pragma warning(disable: 5045)

uint32_t VS3::CodeFactory::Cryptography::Hash::OneAtATime::Compute(std::vector<uint8_t>* data)
{
	if (data == nullptr)
		throw std::invalid_argument("The argument data is null.");
	return Compute(*data);
}

uint32_t VS3::CodeFactory::Cryptography::Hash::OneAtATime::Compute(std::vector<uint8_t>& data)
{
	if (data.empty())
		throw std::invalid_argument("The argument data is null.");

    uint32_t hash = 0, len = ToUint32(data.size());

    for (uint32_t i = 0; i < len; i++)
    {
        hash += data[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}
