#include <Fnv1A.h>
#include <algorithm>

uint32_t VS3::CodeFactory::Cryptography::Hash::Fnv1A::Compute(std::vector<uint8_t>* data)
{
	if (data == nullptr)
		throw std::invalid_argument("The argument data is null.");
	return Compute(*data);
}

uint32_t VS3::CodeFactory::Cryptography::Hash::Fnv1A::Compute(std::vector<uint8_t>& data)
{
	if (data.empty())
		throw std::invalid_argument("The argument data is null.");

	uint32_t result = 2166136261;

	std::for_each(data.cbegin(), data.cend(), [&](const uint8_t n)
		{
			result ^= n;
			result += (result << 1) + (result << 4) + (result << 7) + (result << 8) + (result << 24);
		});

	return result;
}
