#include <PartialKey.h>
#include <Adler16 .h>
#include <Crc16.h>
#include <Crc32.h>
#include <CrcCcitt .h>
#include <GeneralizedCrc.h>
#include <Fnv1A.h>
#include <Jenkins06.h>
#include <Jenkins96.h>
#include <OneAtATime.h>
#include <SuperFast.h>
#include <Base32.h>
#include <algorithm>

#pragma warning(disable: 5045)

using namespace VS3::CodeFactory::Cryptography;
using namespace VS3::CodeFactory::Cryptography::Checksum;
using namespace VS3::CodeFactory::Cryptography::Hash;

std::string PartialKey::Generate(uint32_t seed)
{
    uint32_t hashOffset = 0, len = ToUint32(m_baseKeys.size());
    std::vector<uint8_t> data((m_baseKeys.size() * 4) + 4);
    data[0] = static_cast<uint8_t>(seed & 0xFF);
    data[1] = static_cast<uint8_t>(seed >> 8);
    data[2] = static_cast<uint8_t>(seed >> 16);
    data[3] = static_cast<uint8_t>(seed >> 24);

    for (uint32_t i = 0; i < len; i++)
    {
        uint32_t digit = seed ^ m_baseKeys[i];
        std::vector<uint8_t> bytes(sizeof(uint32_t));
        std::memcpy(bytes.data(), &digit, sizeof(digit));
        uint32_t hash = m_hashFunctions[hashOffset++]->Compute(bytes);
        data[4 + (4 * static_cast<std::vector<uint8_t, std::allocator<uint8_t>>::size_type>(i))] = static_cast<uint8_t>(hash & 0xFF);
        data[5 + (4 * static_cast<std::vector<uint8_t, std::allocator<uint8_t>>::size_type>(i))] = static_cast<uint8_t>(hash >> 8);
        data[6 + (4 * static_cast<std::vector<uint8_t, std::allocator<uint8_t>>::size_type>(i))] = static_cast<uint8_t>(hash >> 16);
        data[7 + (4 * static_cast<std::vector<uint8_t, std::allocator<uint8_t>>::size_type>(i))] = static_cast<uint8_t>(hash >> 24);
        hashOffset %= m_hashFunctions.size();
    }

    uint16_t checksum = m_checksum->Compute(data);
    std::vector<uint8_t> key(data);
    key.push_back(static_cast<uint8_t>(checksum & 0xFF));
    key.push_back(static_cast<uint8_t>(checksum >> 8));
    std::string result = Base32::ToBase32(key);

    if (m_spacing > 0)
    {
        uint32_t count = (ToUint32(result.size()) / m_spacing);

        if (result.size() % m_spacing == 0)
            --count;

        for (uint32_t i = 0; i < count; i++)
            result = result.insert(m_spacing + (static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) * m_spacing + i), "-");
    }

    return result;
}

std::string PartialKey::Generate(std::string& seed)
{
    std::vector<uint8_t> bytes(seed.size());
    std::memcpy(bytes.data(), seed.data(), seed.size());
    std::unique_ptr<Hash::Fnv1A> pk(new Hash::Fnv1A());
    return Generate(pk->Compute(bytes));
}

std::map<uint32_t, std::string> PartialKey::Generate(uint32_t numberOfKeys, uint32_t randomSeed)
{
    std::map<uint32_t, std::string> result;
    srand(randomSeed);

    for (uint32_t i = 0; i < numberOfKeys; i++)
    {
        std::vector<uint32_t> bytes =
        {
            static_cast<uint32_t>(rand()),
            static_cast<uint32_t>(rand()),
            static_cast<uint32_t>(rand()),
            static_cast<uint32_t>(rand()),
        };
        uint32_t seed = *reinterpret_cast<uint32_t*>(bytes.data());

        while (result.find(seed) != result.end())
        {
            bytes[0] = static_cast<uint32_t>(rand()),
            bytes[1] = static_cast<uint32_t>(rand()),
            bytes[2] = static_cast<uint32_t>(rand()),
            bytes[3] = static_cast<uint32_t>(rand()),
            seed = *reinterpret_cast<uint32_t*>(bytes.data());
        }

        result.emplace(seed, Generate(seed));
    }

    return result;
}

PartialKey::PartialKey(ChecksumMode checksumMode, HashMode hashMode, std::vector<uint32_t>& baseKeys, uint8_t spacing, uint32_t seedOfJenkins06)
    : m_spacing(spacing)
{
    std::copy(baseKeys.begin(), baseKeys.end(), std::back_inserter(m_baseKeys));

    switch (checksumMode)
    {
    case Adler16:
        m_checksum.reset(new Checksum::Adler16());
        break;
    case Crc16:
        m_checksum.reset(new Checksum::Crc16());
        break;
    case CrcCcitt:
        m_checksum.reset(new Checksum::CrcCcitt());
        break;
    }

    switch (hashMode)
    {
    case Fnv1A:
        {
            std::shared_ptr<Hash::IHash> h1(new Hash::Fnv1A());
            m_hashFunctions.push_back(h1);
        }
        break;
    case Jenkins06:
        {
            std::shared_ptr<Hash::IHash> h2(new Hash::Jenkins06(seedOfJenkins06));
            m_hashFunctions.push_back(h2);
        }
        break;
    case Jenkins96:
        {
            std::shared_ptr<Hash::IHash> h3(new Hash::Jenkins96());
            m_hashFunctions.push_back(h3);
        }
        break;
    case OneAtATime:
        {
            std::shared_ptr<Hash::IHash> h4(new Hash::OneAtATime());
            m_hashFunctions.push_back(h4);
        }
        break;
    case SuperFast:
        {
            std::shared_ptr<Hash::IHash> h5(new Hash::SuperFast());
            m_hashFunctions.push_back(h5);
        }
        break;
    case Crc32:
        {
            std::shared_ptr<Hash::IHash> h6(new Hash::Crc32());
            m_hashFunctions.push_back(h6);
        }
        break;
    case GeneralizedCrc:
        {
            std::shared_ptr<Hash::IHash> h7(new Hash::GeneralizedCrc());
            m_hashFunctions.push_back(h7);
        }
        break;
    }
}

bool VS3::CodeFactory::Cryptography::PartialKey::ValidateKey(ChecksumMode checksumMode, HashMode hashMode, std::string& key, int32_t subkeyIndex, uint32_t subkeyBase, uint32_t seedOfJenkins06)
{
    std::string emptyString;
    return ValidateKey(checksumMode, hashMode, key, subkeyIndex, subkeyBase, emptyString, seedOfJenkins06);
}

bool VS3::CodeFactory::Cryptography::PartialKey::ValidateKey(ChecksumMode checksumMode, HashMode hashMode, std::string& key, int32_t subkeyIndex, uint32_t subkeyBase, std::string& seedString, uint32_t seedOfJenkins06)
{
    std::vector<uint8_t> bytes = GetKeyBytes(key);
    uint32_t seed = *reinterpret_cast<uint32_t*>(bytes.data());
    return ValidateKey(checksumMode, hashMode, bytes, seed, subkeyIndex, subkeyBase, seedString, seedOfJenkins06);
}

bool VS3::CodeFactory::Cryptography::PartialKey::ValidateKey(ChecksumMode checksumMode, HashMode hashMode, std::vector<uint8_t>& key, uint32_t seed, int32_t subkeyIndex, uint32_t subkeyBase, std::string& seedString, uint32_t seedOfJenkins06)
{
    std::unique_ptr<Checksum::IChecksum16> checksum;
    std::unique_ptr<Hash::IHash> hash;

    switch (checksumMode)
    {
    case Adler16:
        checksum.reset(new Checksum::Adler16());
        break;
    case Crc16:
        checksum.reset(new Checksum::Crc16());
        break;
    case CrcCcitt:
        checksum.reset(new Checksum::CrcCcitt());
        break;
    default:
        throw std::invalid_argument("The argument checksumMode is not supported.");
    }

    switch (hashMode)
    {
    case Fnv1A:
        hash.reset(new Hash::Fnv1A());
        break;
    case Jenkins06:
        hash.reset(new Hash::Jenkins06(seedOfJenkins06));
        break;
    case Jenkins96:
        hash.reset(new Hash::Jenkins96());
        break;
    case OneAtATime:
        hash.reset(new Hash::OneAtATime());
        break;
    case SuperFast:
        hash.reset(new Hash::SuperFast());
        break;
    case Crc32:
        hash.reset(new Hash::Crc32());
        break;
    case GeneralizedCrc:
        hash.reset(new Hash::GeneralizedCrc());
        break;
    default:
        throw std::invalid_argument("The argument hashMode is not supported.");
    }
    
    if (!seedString.empty())
    {
        std::vector<uint8_t> buf(seedString.size());
        std::memcpy(buf.data(), seedString.data(), seedString.size());

        if (hash->Compute(buf) != seed)
            return false;
    }

    return ValidateKey(checksum.get(), hash.get(), key, seed, subkeyIndex, subkeyBase);
}

bool VS3::CodeFactory::Cryptography::PartialKey::ValidateKey(Checksum::IChecksum16* checksum, Hash::IHash* hash, std::vector<uint8_t>& key, uint32_t seed, int32_t subkeyIndex, uint32_t subkeyBase)
{
    if (!ValidateChecksum(std::move(checksum), key))
        return false;

    uint32_t offset = static_cast<uint32_t>(subkeyIndex * 4 + 4);
    std::vector<uint8_t> bytes(sizeof(uint32_t));

    if (subkeyIndex < 0 || static_cast<unsigned long long>(offset) + 4 > key.size() - 2)
        throw std::out_of_range("The sub key index is out of bounds.");

    uint32_t subkey = *reinterpret_cast<uint32_t*>(key.data() + offset);
    uint32_t digit = seed ^ subkeyBase;
    std::memcpy(bytes.data(), &digit, sizeof(digit));
    auto expected = std::move(hash)->Compute(bytes);
    return expected == subkey;
}

bool VS3::CodeFactory::Cryptography::PartialKey::ValidateChecksum(Checksum::IChecksum16* checksum, std::vector<uint8_t>& key)
{
    std::vector<uint8_t> keyBytes;
    uint16_t sum = *reinterpret_cast<uint16_t*> (key.data() + key.size() - 2);
    std::copy(key.begin(), key.end() - 2, std::back_inserter(keyBytes));
    return sum == checksum->Compute(keyBytes);
}

uint32_t VS3::CodeFactory::Cryptography::PartialKey::GetSerialNumberFromKey(std::string& key)
{
    std::vector<uint8_t> bytes = GetKeyBytes(key);
    return *reinterpret_cast<uint32_t*>(bytes.data());
}

uint32_t VS3::CodeFactory::Cryptography::PartialKey::GetSerialNumberFromSeed(std::string& seed, HashMode hashMode, uint32_t seedOfJenkins06)
{
    std::unique_ptr<Hash::IHash> hash;

    switch (hashMode)
    {
    case Fnv1A:
        hash.reset(new Hash::Fnv1A());
        break;
    case Jenkins06:
        hash.reset(new Hash::Jenkins06(seedOfJenkins06));
        break;
    case Jenkins96:
        hash.reset(new Hash::Jenkins96());
        break;
    case OneAtATime:
        hash.reset(new Hash::OneAtATime());
        break;
    case SuperFast:
        hash.reset(new Hash::SuperFast());
        break;
    case Crc32:
        hash.reset(new Hash::Crc32());
        break;
    case GeneralizedCrc:
        hash.reset(new Hash::GeneralizedCrc());
        break;
    default:
        throw std::invalid_argument("The argument hashMode is not supported.");
    }

    std::vector<uint8_t> buf(seed.size());
    std::memcpy(buf.data(), seed.data(), seed.size());

    return hash->Compute(buf);
}

std::vector<uint8_t> VS3::CodeFactory::Cryptography::PartialKey::GetKeyBytes(std::string& key)
{
    key = ToUpperInvariant(key);
    size_t pos = key.find('-');

    while (static_cast<int32_t>(pos) > -1)
    {
        key = key.erase(pos, 1);
        pos = key.find('-');
    }

    return Base32::FromBase32(key);
}

PartialKey::PartialKey(Checksum::IChecksum16* checksum, Hash::IHash* hash, std::vector<uint32_t>& baseKeys)
	: PartialKey(checksum, std::vector<Hash::IHash*>{hash}, baseKeys)
{
}

PartialKey::PartialKey(Checksum::IChecksum16* checksum, std::vector<Hash::IHash*> hashFunctions, std::vector<uint32_t>& baseKeys)
    : PartialKey(checksum, &hashFunctions, &baseKeys)
{
}

PartialKey::PartialKey(Checksum::IChecksum16* checksum, std::vector<Hash::IHash*>* hashFunctions, std::vector<uint32_t>* baseKeys)
    :m_spacing(0)
{
    if (checksum == nullptr)
        throw std::invalid_argument("The argument checksum is nullptr.");
    else if (hashFunctions == nullptr)
        throw std::invalid_argument("The argument hashFunctions is nullptr.");
    else if (baseKeys == nullptr)
        throw std::invalid_argument("The argument baseKeys is nullptr.");

    std::copy(baseKeys->begin(), baseKeys->end(), std::back_inserter(m_baseKeys));
    m_checksum.reset(std::move(checksum));
    std::for_each(hashFunctions->begin(), hashFunctions->end(), [&](Hash::IHash* f)
        {
            std::shared_ptr<Hash::IHash> v(std::move(f));
            m_hashFunctions.push_back(v);
        });
}
