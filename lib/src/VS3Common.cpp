#include <VS3Common.h>
#include <algorithm>

uint32_t ToUint32(size_t value) noexcept(false)
{
    if (value > UINT_MAX)
        throw std::out_of_range("value is out of range.");
    return static_cast<uint32_t>(value);
}

bool IsBigEndian()
{
    uint16_t word = 0x0001;
    uint8_t* byte = reinterpret_cast<uint8_t*>(&word);
    return byte[0] == 0;
}

std::string ToUpperInvariant(const std::string& str)
{
    std::string result(str);
    std::transform(result.begin(), result.end(), result.begin(), std::toupper);
    return result;
}


