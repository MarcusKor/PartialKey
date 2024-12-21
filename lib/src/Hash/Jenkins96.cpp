#include <Jenkins96.h>

#pragma warning(disable: 5045)

uint32_t VS3::CodeFactory::Cryptography::Hash::Jenkins96::Compute(std::vector<uint8_t>* data)
{
    if (data == nullptr)
        throw std::invalid_argument("The argument data is null.");
    return Compute(*data);
}

uint32_t VS3::CodeFactory::Cryptography::Hash::Jenkins96::Compute(std::vector<uint8_t>& data)
{
    if (data.empty())
        throw std::invalid_argument("The argument data is null.");

    uint32_t i = 0, len = ToUint32(data.size());
    m_a = m_b = 0x9e3779b9;
    m_c = 0;

    while (i + 12 <= len)
    {
        m_a += data[i++] |
            (static_cast<uint32_t>(data[i++]) << 8) |
            (static_cast<uint32_t>(data[i++]) << 16) |
            (static_cast<uint32_t>(data[i++]) << 24);
        m_b += data[i++] |
            (static_cast<uint32_t>(data[i++]) << 8) |
            (static_cast<uint32_t>(data[i++]) << 16) |
            (static_cast<uint32_t>(data[i++]) << 24);
        m_c += data[i++] |
            (static_cast<uint32_t>(data[i++]) << 8) |
            (static_cast<uint32_t>(data[i++]) << 16) |
            (static_cast<uint32_t>(data[i++]) << 24);
        Mix();
    }

    m_c += static_cast<uint32_t>(len);

    if (i < len)
        m_a += data[i++];

    if (i < len)
        m_a += static_cast<uint32_t>(data[i++]) << 8;

    if (i < len)
        m_a += static_cast<uint32_t>(data[i++]) << 16;

    if (i < len)
        m_a += static_cast<uint32_t>(data[i++]) << 24;

    if (i < len)
        m_b += data[i++];

    if (i < len)
        m_b += static_cast<uint32_t>(data[i++]) << 8;

    if (i < len)
        m_b += static_cast<uint32_t>(data[i++]) << 16;

    if (i < len)
        m_b += static_cast<uint32_t>(data[i++]) << 24;

    if (i < len)
        m_c += static_cast<uint32_t>(data[i++]) << 8;

    if (i < len)
        m_c += static_cast<uint32_t>(data[i++]) << 16;

    if (i < len)
        m_c += static_cast<uint32_t>(data[i]) << 24;

    Mix();
    return m_c;
}

VS3::CodeFactory::Cryptography::Hash::Jenkins96::Jenkins96()
    : m_a(0), m_b(0), m_c(0)
{
}

void VS3::CodeFactory::Cryptography::Hash::Jenkins96::Mix()
{
    m_a -= m_b;
    m_a -= m_c;
    m_a ^= (m_c >> 13);
    m_b -= m_c;
    m_b -= m_a;
    m_b ^= (m_a << 8);
    m_c -= m_a;
    m_c -= m_b;
    m_c ^= (m_b >> 13);
    m_a -= m_b;
    m_a -= m_c;
    m_a ^= (m_c >> 12);
    m_b -= m_c;
    m_b -= m_a;
    m_b ^= (m_a << 16);
    m_c -= m_a;
    m_c -= m_b;
    m_c ^= (m_b >> 5);
    m_a -= m_b;
    m_a -= m_c;
    m_a ^= (m_c >> 3);
    m_b -= m_c;
    m_b -= m_a;
    m_b ^= (m_a << 10);
    m_c -= m_a;
    m_c -= m_b;
    m_c ^= (m_b >> 15);
}
