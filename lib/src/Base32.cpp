#include <Base32.h>
#include <sstream>

#pragma warning(disable: 5045)

static const std::string map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

std::string VS3::CodeFactory::Cryptography::Base32::ToBase32(std::vector<uint8_t> data)
{
	std::ostringstream result;

	try
	{
		uint32_t len = ToUint32(data.size()) - 1;		

		if (len > 0)
		{
			for (uint32_t i = 0, j = 0; i <= len; i++)
			{
				uint8_t b = 0x0;

				if (i != len)
					b = static_cast<uint8_t>(data[i + 1]);

				switch (j)
				{
					case 0:
						{
							result.put(map[static_cast<uint8_t>(data[i] >> 3)]);
							result.put(map[static_cast<uint8_t>(((data[i] << 2) & 0x1F) | (b >> 6))]);
							j = 2;
						}
						break;
					case 1:
						{
							result.put(map[static_cast<uint8_t>((data[i] >> 2) & 0x1F)]);
							result.put(map[static_cast<uint8_t>(((data[i] << 3) & 0x1F) | (b >> 5))]);
							j = 3;
						}
						break;
					case 2:
						{
							result.put(map[static_cast<uint8_t>((data[i] >> 1) & 0x1F)]);
							result.put(map[static_cast<uint8_t>(((data[i] << 4) & 0x1F) | (b >> 4))]);
							j = 4;
						}
						break;
					case 3:
						{
							result.put(map[static_cast<uint8_t>(data[i] & 0x1F)]);
							j = 0;
						}
						break;
					case 4:
						{
							result.put(map[static_cast<uint8_t>(((data[i] << 1) & 0x1F) | (b >> 7))]);
							j = 1;
						}
						break;
					default:
						throw std::runtime_error("Incorrect offset.");
						break;
				}
			}
		}
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	return result.str();
}

std::vector<uint8_t> VS3::CodeFactory::Cryptography::Base32::FromBase32(std::string& data)
{
	uint32_t len = ToUint32(data.size()) * 5 / 8;
	uint8_t ch = 0x0;
	std::vector<uint8_t> result(len);

	for (uint32_t i = 0, j = 0, k = 0; i < len; i++)
	{
		switch (k)
		{
			case 0:
				{
					ch = static_cast<uint8_t>(map.find(data[j++]));
					result.at(i) = static_cast<uint8_t>(ch << 3);
					ch = static_cast<uint8_t>(map.find(data[j++]));
					result.at(i) |= static_cast<uint8_t>(ch >> 2);
					k = 3;
				}
				break;
			case 1:
				{
					result.at(i) = static_cast<uint8_t>(ch << 4);
					ch = static_cast<uint8_t>(map.find(data[j++]));
					result.at(i) |= static_cast<uint8_t>(ch >> 1);
					k = 4;
				}
				break;
			case 2:
				{
					result.at(i) = static_cast<uint8_t>(ch << 5);
					ch = static_cast<uint8_t>(map.find(data[j++]));
					result.at(i) |= ch;
					k = 0;
				}
				break;
			case 3:
				{
					result.at(i) = static_cast<uint8_t>(ch << 6);
					ch = static_cast<uint8_t>(map.find(data[j++]));
					result.at(i) |= static_cast<uint8_t>(ch << 1);
					ch = static_cast<uint8_t>(map.find(data[j++]));
					result.at(i) |= static_cast<uint8_t>(ch >> 4);
					result.at(i) |= static_cast<uint8_t>(ch >> 4);
					k = 1;
				}
				break;
			case 4:
				{
					result.at(i) = static_cast<uint8_t>(ch << 7);
					ch = static_cast<uint8_t>(map.find(data[j++]));
					result.at(i) |= static_cast<uint8_t>(ch << 2);
					ch = static_cast<uint8_t>(map.find(data[j++]));
					result.at(i) |= static_cast<uint8_t>(ch >> 3);
					k = 2;
				}
				break;
			default:
				throw std::runtime_error("Incorrect offset.");
				break;
		}
	}

	return result;
}

