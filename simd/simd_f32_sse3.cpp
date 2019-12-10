#include "simd_f32_sse3.h"
#include "simd_f32.h"
#include "simd_macros.h"

#ifdef GSIMD_USE_SSE3
#include <pmmintrin.h>
#endif

#ifdef GSIMD_USE_SSE3
namespace GSimd
{

void FastArray_4f32_SSE3::vec3_length(float * pfUnits, int nUnits)
{
	// https://nccastaff.bmth.ac.uk/jmacey/Lectures/SIMD/?home=/jmacey/AProg#/6/18
	float * pf = pfUnits;

	for (int n=0; n<nUnits; n++)
	{
		__m128 m = _mm_loadu_ps(pf);
		__m128 res = _mm_mul_ps(m, m);
		__m128 sum = _mm_hadd_ps(res, res);
		__m128 sum2 = _mm_hadd_ps(sum, sum);

		float length = _mm_cvtss_f32(_mm_sqrt_ss(sum2));
		pf[3] = length;
		pf += 4;
	}
}

void FastArray_4f32_SSE3::vec3_length_squared(float * pfUnits, int nUnits)
{
	float * pf = pfUnits;

	for (int n=0; n<nUnits; n++)
	{
		__m128 m = _mm_loadu_ps(pf);
		__m128 res = _mm_mul_ps(m, m);
		__m128 sum = _mm_hadd_ps(res, res);
		__m128 sum2 = _mm_hadd_ps(sum, sum);

		float slength = _mm_cvtss_f32(sum2);
		pf[3] = slength;
		pf += 4;
	}
}


} // namespace
#endif // GSIMD_USE_SSE3

#include "simd_macros_undef.h"
