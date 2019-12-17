#include "simd_cpu.h"

// UNIX_ENABLED
// ANDROID_ENABLED
// OSX_ENABLED
// WINDOWS_ENABLED
// X11_ENABLED



#ifdef GSIMD_USE_SSE
#include <emmintrin.h>

#ifdef WINDOWS_ENABLED
#include <intrin.h>
#endif

#ifdef UNIX_ENABLED
#include <cpuid.h>
//#include <xsaveintrin.h>
//#include <immintrin.h>
#endif

#endif



#if defined GSIMD_USE_NEON
#define ARM_NEON_GCC_COMPATIBILITY 1
#include <arm_neon.h>
#include <sys/types.h>
#include <sys/sysctl.h>  //for sysctlbyname
#endif


namespace GSimd
{

// guaranteed to be zerod before any other constructors are run..
// see https://stackoverflow.com/questions/2091499/why-are-global-and-static-variables-initialized-to-their-default-values
// so if the flags are ever used before detect, a non SIMD path will be used for safety.
Godot_CPU g_GodotCPU;


Godot_CPU::Godot_CPU()
{
	m_Flags = 0;
	m_eMaxNeon = N_NONE;
	m_eMaxSSE = M_NONE;
	m_szName = "NoCPU";
	Detect();
	Detect_Max();

}

void Godot_CPU::Detect_Max()
{
	if (HasFlag(F_NEON))
		m_eMaxNeon = N_NEON;
	if (HasFlag(F_MMX))
		m_eMaxSSE = M_MMX;
	if (HasFlag(F_SSE))
		m_eMaxSSE = M_SSE;
	if (HasFlag(F_SSE2))
		m_eMaxSSE = M_SSE2;
	if (HasFlag(F_SSE3))
		m_eMaxSSE = M_SSE3;
	if (HasFlag(F_SSSE3))
		m_eMaxSSE = M_SSSE3;
	if (HasFlag(F_SSE4_1))
		m_eMaxSSE = M_SSE4_1;
	if (HasFlag(F_SSE4_2))
		m_eMaxSSE = M_SSE4_2;
	if (HasFlag(F_AVX))
		m_eMaxSSE = M_AVX;
	if (HasFlag(F_AVX2))
		m_eMaxSSE = M_AVX2;
	if (HasFlag(F_AVX512))
		m_eMaxSSE = M_AVX512;
}

String Godot_CPU::get_sse_caps_string(String spacer)
{
	String sz = "";

	if (HasFlag(F_NEON))
		sz += "NEON" + spacer;
	if (HasFlag(F_MMX))
		sz += "MMX" + spacer;
	if (HasFlag(F_SSE))
		sz += "SSE" + spacer;
	if (HasFlag(F_SSE2))
		sz += "SSE2" + spacer;
	if (HasFlag(F_SSE3))
		sz += "SSE3" + spacer;
	if (HasFlag(F_SSSE3))
		sz += "SSSE3" + spacer;
	if (HasFlag(F_SSE4_1))
		sz += "SSE4.1" + spacer;
	if (HasFlag(F_SSE4_2))
		sz += "SSE4.2" + spacer;
	if (HasFlag(F_AVX))
		sz += "AVX" + spacer;
	if (HasFlag(F_AVX2))
		sz += "AVX2" + spacer;
	if (HasFlag(F_AVX512))
		sz += "AVX512" + spacer;

	return sz;
}

void Godot_CPU::Detect()
{
	// ARM (untested)
#ifdef GSIMD_USE_NEON
	/* NEEDS TESTING
		{
			uint32_t hasFeature = 0;
			size_t featureSize = sizeof(hasFeature);
			int err = sysctlbyname("hw.optional.neon_hpfp", &hasFeature, &featureSize, NULL, 0);
			if (0 == err && hasFeature)
				m_Flags |= F_NEON;
		}
	*/
#endif  //GSIMD_USE_NEON

	// x86 / x86_64
#ifdef GSIMD_USE_SSE

	uint32_t cpuInfo[4];
	uint32_t cpuInfo1[4];
	uint32_t cpuInfo7[4];
	memset(cpuInfo, 0, sizeof (cpuInfo));
	memset(cpuInfo1, 0, sizeof (cpuInfo1));
	memset(cpuInfo7, 0, sizeof (cpuInfo7));

#if (_MSC_FULL_VER >= 160040219)
	__cpuid(cpuInfo, 0);
	__cpuid(cpuInfo1, 1);

	int num_ids = cpuInfo[0];
	if (num_ids >= 7)
	{
		__cpuid(cpuInfo7, 7);
	}
#else // msvc

#ifdef UNIX_ENABLED
	int res = __get_cpuid(0, &cpuInfo[0], &cpuInfo[1], &cpuInfo[2], &cpuInfo[3]);
	assert (res);
	res = __get_cpuid(1, &cpuInfo1[0], &cpuInfo1[1], &cpuInfo1[2], &cpuInfo1[3]);
	assert (res);


	int num_ids = cpuInfo[0];
	if (num_ids >= 7)
	{
		res = __get_cpuid(7, &cpuInfo7[0], &cpuInfo7[1], &cpuInfo7[2], &cpuInfo7[3]);
		assert (res);
	}

#else // unix

// Windows non visual studio? To do..
#pragma message ("Godot_CPU::Detect() Compiler does not support CPUID intrinsic")
#endif // not unix


#endif // not msvc

	// CPU name
	char szName[13];
	memset (szName, 0, sizeof (szName));
	memcpy (&szName[0], &cpuInfo[1], 4);
	memcpy (&szName[4], &cpuInfo[3], 4);
	memcpy (&szName[8], &cpuInfo[2], 4);

	// store CPU name
	m_szName = szName;



	// supports AVX? only detected on windows so far
//#ifdef WINDOWS_ENABLED
	// AVX
	bool bCpuAVX = cpuInfo1[2] & (1 << 28) || false;
	bool bOS_XSAVE = cpuInfo1[2] & (1 << 27) || false;

	if (bCpuAVX && bOS_XSAVE)
	{
        // Check if the OS will save the YMM registers
        //unsigned long long xcrFeatureMask = xgetbv(_XCR_XFEATURE_ENABLED_MASK);
        //bool bAVX = (xcrFeatureMask & 0x6) == 6;

		// https://chromium.googlesource.com/chromium/src/base/+/refs/heads/master/cpu.cc
		bool bAVX =
			(cpuInfo1[2] & 0x10000000) != 0 &&
			(cpuInfo1[2] & 0x04000000) != 0 && // xsave
			(cpuInfo1[2] & 0x08000000) != 0 && // osxsave
			(xgetbv(0) & 6) == 6; // xsave enabled by kernel

		if (bAVX)
		{
			// avx
			m_Flags |= F_AVX;

			// avx 2?
			if ((cpuInfo7[1] & 0x00000020) != 0)
				m_Flags |= F_AVX2;
		}


	}
//#endif

	if (cpuInfo1[2] & (1 << 20) || false)
		m_Flags |= F_SSE4_2;

	if (cpuInfo1[2] & (1 << 19) || false)
		m_Flags |= F_SSE4_1;

	if (cpuInfo1[2] & (1 << 9) || false)
		m_Flags |= F_SSSE3;

	if (cpuInfo1[2] & (1 << 0) || false)
		m_Flags |= F_SSE3;

	if (cpuInfo1[3] & (1 << 26) || false)
		m_Flags |= F_SSE2;

	if (cpuInfo1[3] & (1 << 25) || false)
		m_Flags |= F_SSE;

	if (cpuInfo1[3] & (1 << 23) || false)
		m_Flags |= F_MMX;


#endif // SSE

}


// xgetbv returns the value of an Intel Extended Control Register (XCR).
// Currently only XCR0 is defined by Intel so |xcr| should always be zero.
uint64_t Godot_CPU::xgetbv(uint32_t xcr)
{
#if defined(_MSC_VER)
  return _xgetbv(xcr);
#else
  uint32_t eax, edx;
  __asm__ volatile (
    "xgetbv" : "=a"(eax), "=d"(edx) : "c"(xcr));
  return (static_cast<uint64_t>(edx) << 32) | eax;
#endif  // defined(COMPILER_MSVC)
}


} // namespace
