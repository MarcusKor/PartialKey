#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_COMMON_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_COMMON_H

#include <VS3Stddef.h>
#include <iostream>
#include <string>

#if defined(__cplusplus)
extern "C" {
#endif

uint32_t ToUint32(size_t value) noexcept(false);
bool IsBigEndian();

#ifdef DEBUG
#define DEBUGPOINT	std::cout << __FILE__ << "," << __LINE__ << "," << __FUNCTION__ << std::endl;
#else
#define DEBUGPOINT
#endif

#if defined(__cplusplus)
}
#endif

std::string ToUpperInvariant(const std::string& str);
#endif	// VS3_CODEFACTORY_CRYPTOGRAPHY_COMMON_H