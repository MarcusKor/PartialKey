#pragma once

#ifndef VS3_CODEFACTORY_CRYPTOGRAPHY_ARCHITECTURE_H
#define VS3_CODEFACTORY_CRYPTOGRAPHY_ARCHITECTURE_H

// Determine compiler
#if defined(_MSC_VER)
	// Defined by Visual Studio
	#define VS3_COMPILER_MSVC
#elif defined(__clang__)
	// Defined by Clang
	#define VS3_COMPILER_CLANG
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
	// Defined by Sun Studio (C compiler) Or Defined by Sun Studio (C++ compiler)
	#define VS3_COMPILER_SUN
#elif defined(__INTEL_COMPILER)
	// Defined by Intel
	#define VS3_COMPILER_INTEL
#elif defined(__GNUC__)
	// Defined by GCC and Clang
	#define VS3_COMPILER_GCC
#elif defined(__SNC__)
	// Defined by SNC
	#define VS3_COMPILER_SNC
#else
	#error Unsupported compiler.
#endif

// Determine platform
#if defined(_WIN32) || defined(_WIN64)
	// Defined for both 32-bit and 64-bit environments Or Defined for 64-bit environments
	#define VS3_PLATFORM_WINDOWS
#elif defined(__linux__)        // Defined by all Linux environments
	#define VS3_PLATFORM_LINUX
#elif defined(__SCE__)          // Defined by SCE SDK
  &&  defined(__arm__)          // Defined by compiler
	#define VS3_PLATFORM_VITA
#elif defined(__ORBIS__)        // Defined by SNC PS4 TC and SCE SDK
	#define VS3_PLATFORM_PS4
#elif defined(NN_PLATFORM_CTR)  // Defined by compiler
	#define VS3_PLATFORM_3DS
#elif defined(__NX)             // Defined by compiler
	#define VS3_PLATFORM_SWITCH
#elif defined(ANDROID)          // Defined by some compilers
  ||  defined(__ANDROID__)      // Defined by some compilers
	#define VS3_PLATFORM_ANDROID
#elif defined(_XBOX_ONE)        // Defined by XSDK
	#define VS3_PLATFORM_XBOXONE
#elif defined(__APPLE__)
	#include <TargetConditionals.h>
#if TARGET_OS_MAC               // Defined by TargetConditionals.h
	#define VS3_PLATFORM_MAC
#elif TARGET_OS_IOS             // Defined by TargetConditionals.h
	#define VS3_PLATFORM_IOS
#endif
	#error Unsupported platform.
#endif

// Determine architecture
#ifdef VS3_PLATFORM_WINDOWS
	#if defined(_M_IX86) || defined(_M_IX86_FP)
		#define VS3_ARCH_X86
	#elif defined(_M_X64) || defined(_M_AMD64) || defined(_WIN64)
		#define VS3_ARCH_X64
	#else
		#error Unsupported architecture.
	#endif
#else
	#if defined(__i386__) || defined(__i386) || defined(__x86__) || defined(__x86)
		// Defined by GCC, Clang and Sun Studio
		#define VS3_ARCH_X86
	#elif defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
		#define VS3_ARCH_X86_64
	#elif defined(__aarch64__)
		// Defined by GCC and Clang
		#define VS3_ARCH_ARM64
	#else
		#error Unsupported architecture.
	#endif
#endif

// Determine data model
#if defined(_ILP32)	|| defined(__ILP32__) || defined(VS3_PLATFORM_WINDOWS) || defined(VS3_PLATFORM_XBOXONE)
	// Defined by HP aCC and Sun Studio Or Defined by GCC and Clang Or Windows is always going to be ILP32 Or XboxOne is also Windows
	#define VS3_ILP32
#elif defined(_LP64) || defined(__LP64__)
	// Defined by HP aCC and Sun Studio Or Defined by GCC and Clang
	#define VS3_LP64
#else
	#error Unsupported data model.
#endif

// Type large enough to hold a pointer
#if defined(VS3_ILP32)
	#define VS3_ADDR long long
#else
	#define VS3_ADDR long
#endif

// Various compiler specific attributes handled here
#if defined(VS3_COMPILER_GCC) || defined(VS3_COMPILER_CLANG) || defined(VS3_COMPILER_SNC)
	#define VS3_ATTRIBUTE_ALIGN(a) __attribute__((__aligned__(a)))
	#define VS3_ATTRIBUTE_ALWAYS_INLINE __attribute__((__always_inline__)) inline
	#define VS3_RESTRICT restrict
#elif defined(VS3_COMPILER_MSVC) || defined(VS3_COMPILER_INTEL)
	#define VS3_ATTRIBUTE_ALIGN(a) __declspec(align(a))
	#define VS3_ATTRIBUTE_ALWAYS_INLINE __forceinline
	#define VS3_RESTRICT __restrict
#endif

#define VS3_ALIGNMENT 16
#define VS3_EXPORT
#define VS3_API
#define VS3_ASSERT(...)

#endif	// VS3_CODEFACTORY_CRYPTOGRAPHY_ARCHITECTURE_H