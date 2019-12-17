#pragma once

#include "core/ustring.h"

namespace GSimd
{


// we are specifically only supporting certain platforms
// note that this can potentially be expanded for more x86, but needs testing
#if defined (WINDOWS_ENABLED) || defined (X11_ENABLED)
// X86
#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined (__i386) || defined (__i386__)
// All these will be used if detected. If you want a particular method compiled out, remove the corresponding define.
#define GSIMD_USE_SSE
#define GSIMD_USE_SSE2
#define GSIMD_USE_SSE3
#define GSIMD_USE_SSSE3
#define GSIMD_USE_SSE4_1
#define GSIMD_USE_SSE4_2
#define GSIMD_USE_SSE4_2
#define GSIMD_USE_AVX
#define GSIMD_USE_AVX512
#endif // x86
#endif // win / linux

// could be also iOS? might need detection code
#if defined (ANDROID_ENABLED)
// ARM
#if defined(__arm__)
#define GSIMD_USE_NEON
#endif
#endif // android


class Godot_CPU
{
public:
	Godot_CPU();

	enum eFlags
	{
		// SSE
		F_MMX = 1 << 0,
		F_SSE = 1 << 1,
		F_SSE2 = 1 << 2,
		F_SSE3 = 1 << 3,
		F_SSSE3 = 1 << 4,
		F_SSE4_1 = 1 << 5,
		F_SSE4_2 = 1 << 6,
		F_AVX = 1 << 7,
		F_AVX2= 1 << 8,
		F_AVX512 = 1 << 9,

		// Neon
		F_NEON = 1 << 16,
	};

	enum eMaxSSE
	{
		M_NONE = 0,
		M_MMX,
		M_SSE,
		M_SSE2,
		M_SSE3,
		M_SSSE3,
		M_SSE4_1,
		M_SSE4_2,
		M_AVX,
		M_AVX2,
		M_AVX512,
	};

	enum eMaxNeon
	{
		N_NONE = 0,
		N_NEON,
	};


	bool HasFlags(unsigned int f) {return (m_Flags & f) == f;}
	bool HasFlag(unsigned int f) {return (m_Flags & f) != 0;}

	String get_name() const {return m_szName;}

	eMaxSSE get_max_sse() const {return m_eMaxSSE;}
	eMaxNeon get_max_neon() const {return m_eMaxNeon;}

	String get_sse_caps_string(String spacer);

private:
	void Detect();
	void Detect_Max();
	uint64_t xgetbv(uint32_t xcr);


	unsigned int m_Flags;
	eMaxSSE m_eMaxSSE;
	eMaxNeon m_eMaxNeon;
	String m_szName;
};


extern Godot_CPU g_GodotCPU;

} // namespace
