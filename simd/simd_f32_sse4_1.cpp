//	Copyright (c) 2019 Lawnjelly

//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:

//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.

//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.

#include "simd_f32_sse4_1.h"
#include "simd_f32.h"
#include "simd_macros.h"

#ifdef GSIMD_USE_SSE4_1
#include <smmintrin.h>
#endif

#ifdef GSIMD_USE_SSE4_1
namespace GSimd
{


void FastArray_4f32_SSE4_1::vec3_dot(float * pfUnits, const float * pfUnits2, int nUnits)
{
	for (int n=0; n<nUnits; n++)
	{
		__m128 m = _mm_loadu_ps(pfUnits);
		__m128 m2 = _mm_loadu_ps(pfUnits2);
		// https://www.felixcloutier.com/x86/dpps
		// try and use xyz only
		__m128 res = _mm_dp_ps(m, m2, 127); // 0xff
		//_mm_storeu_ps(pfUnits, res);

		// save result into 4th
		float d = _mm_cvtss_f32(res);
		pfUnits[3] = d;

		pfUnits += 4;
		pfUnits2 += 4;
	}
}


//void FastArray_4f32_SSE3::vec3_length(float * pfUnits, int nUnits)
//{
//	float * pf = pfUnits;

//	for (int n=0; n<nUnits; n++)
//	{
//		__m128 m = _mm_loadu_ps(pf);
//		__m128 res = _mm_mul_ps(m, m);
//		__m128 sum = _mm_hadd_ps(res, res);
//		__m128 sum2 = _mm_hadd_ps(sum, sum);

//		float length = _mm_cvtss_f32(_mm_sqrt_ss(sum2));
//		pf[3] = length;
//		pf += 4;
//	}
//}

//void FastArray_4f32_SSE3::vec3_length_squared(float * pfUnits, int nUnits)
//{
//	float * pf = pfUnits;

//	for (int n=0; n<nUnits; n++)
//	{
//		__m128 m = _mm_loadu_ps(pf);
//		__m128 res = _mm_mul_ps(m, m);
//		__m128 sum = _mm_hadd_ps(res, res);
//		__m128 sum2 = _mm_hadd_ps(sum, sum);

//		float slength = _mm_cvtss_f32(sum2);
//		pf[3] = slength;
//		pf += 4;
//	}
//}


} // namespace
#endif // GSIMD_USE_SSE4_1

#include "simd_macros_undef.h"
