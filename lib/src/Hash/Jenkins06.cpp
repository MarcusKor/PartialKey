#include <Jenkins06.h>

#pragma warning(disable: 5045)

uint32_t VS3::CodeFactory::Cryptography::Hash::Jenkins06::Compute(std::vector<uint8_t>* data)
{
	if (data == nullptr)
		throw std::invalid_argument("The argument data is null.");
	return Compute(*data);
}

uint32_t VS3::CodeFactory::Cryptography::Hash::Jenkins06::Compute(std::vector<uint8_t>& data)
{
	if (data.empty())
		throw std::invalid_argument("The argument data is null.");

    // internal state
    uint32_t a, b, c;
    uint32_t i = 0, len = ToUint32(data.size());
    // Set up the internal state
    a = b = c = 0xdeadbeef + len + m_seed;

    // All but the last block: affect some 32 bits of (a,b,c)
    while (12 < len)
    {
        a += data[i++];
        a += static_cast<uint32_t>(data[i++]) << 8;
        a += static_cast<uint32_t>(data[i++]) << 16;
        a += static_cast<uint32_t>(data[i++]) << 24;
        b += data[i++];
        b += static_cast<uint32_t>(data[i++]) << 8;
        b += static_cast<uint32_t>(data[i++]) << 16;
        b += static_cast<uint32_t>(data[i++]) << 24;
        c += data[i++];
        c += static_cast<uint32_t>(data[i++]) << 8;
        c += static_cast<uint32_t>(data[i++]) << 16;
        c += static_cast<uint32_t>(data[i++]) << 24;
        Mix(a, b, c);
        len -= 12;
    }

    // Last block: affect all 32 bits of (c)
    // All the case statements fall through
    switch (len) 
    {
    case 12:
        c += ((uint32_t)data[i++]) << 24;
        [[fallthrough]];
    case 11:
        c += ((uint32_t)data[i++]) << 16;
        [[fallthrough]];
    case 10:
        c += ((uint32_t)data[i++]) << 8;
        [[fallthrough]];
    case 9:
        c += data[i++];
        [[fallthrough]];
    case 8:
        b += ((uint32_t)data[i++]) << 24;
        [[fallthrough]];
    case 7:
        b += ((uint32_t)data[i++]) << 16;
        [[fallthrough]];
    case 6:
        b += ((uint32_t)data[i++]) << 8;
        [[fallthrough]];
    case 5:
        b += data[i++];
        [[fallthrough]];
    case 4:
        a += ((uint32_t)data[i++]) << 24;
        [[fallthrough]];
    case 3:
        a += ((uint32_t)data[i++]) << 16;
        [[fallthrough]];
    case 2:
        a += ((uint32_t)data[i++]) << 8;
        [[fallthrough]];
    case 1:
        a += data[i];
        break;
    case 0:
        return c;
    }

    Final(a, b, c);
    return c;
}

VS3::CodeFactory::Cryptography::Hash::Jenkins06::Jenkins06(uint32_t seed)
	: m_seed(seed)
{
}

uint32_t VS3::CodeFactory::Cryptography::Hash::Jenkins06::Rot(uint32_t x, int32_t k)
{
	return ((x << k) | (x >> (32 - k)));
}

void VS3::CodeFactory::Cryptography::Hash::Jenkins06::Final(uint32_t& a, uint32_t& b, uint32_t& c)
{
    c ^= b;
    c -= Rot(b, 14);
    a ^= c;
    a -= Rot(c, 11);
    b ^= a;
    b -= Rot(a, 25);
    c ^= b;
    c -= Rot(b, 16);
    a ^= c;
    a -= Rot(c, 4);
    b ^= a;
    b -= Rot(a, 14);
    c ^= b;
    c -= Rot(b, 24);
}

void VS3::CodeFactory::Cryptography::Hash::Jenkins06::Mix(uint32_t& a, uint32_t& b, uint32_t& c)
{
    a -= c;
    a ^= Rot(c, 4);
    c += b;
    b -= a;
    b ^= Rot(a, 6);
    a += c;
    c -= b;
    c ^= Rot(b, 8);
    b += a;
    a -= c;
    a ^= Rot(c, 16);
    c += b;
    b -= a;
    b ^= Rot(a, 19);
    a += c;
    c -= b;
    c ^= Rot(b, 4);
    b += a;
}
